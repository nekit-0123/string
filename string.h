#include <iostream>
#include <stdarg.h>
#include <cassert>

namespace s
{
class string
{
public:
	explicit string(const std::string& _data )  throw ()
		: TMyString(_data)
	{}
	explicit string(const char* _data ) throw ()
		: TMyString(_data)
	{}
	~string() throw ()
	{
		clearBuf();
	}	
	
	std::string get() const
	{
		return TMyString;
	}
	
	std::string Format(const char *pcFormat, ...)
       	{ 
		if (pcFormat)
		{
			va_list argList;
			va_start(argList, pcFormat);
       			TMyString = _format(pcFormat, argList);
			va_end(argList);
			clearBuf();
		}
		
		return TMyString;
       	}
	
	std::string AppendFormat(const char *pcFormat, ...)
       	{ 
		if (pcFormat)
		{
			va_list argList;
			va_start(argList, pcFormat);
			TMyString += _format(pcFormat, argList);
			va_end(argList);
			clearBuf();
		}

		return TMyString;
       	}
	
	std::string MakeUpper()
       	{
		if (!TMyString.empty())
		{
       			setlocale(LC_ALL, ""); 
			_strupr_s(const_cast<char*>(TMyString.c_str()), TMyString.size()+1);
		}
		return TMyString;
       	}
       
       	std::string MakeLower()
       	{
		if (!TMyString.empty())
		{
       			setlocale(LC_ALL, "");        	
			_strlwr_s(const_cast<char*>(TMyString.c_str()), TMyString.size()+1);
		}
		return TMyString;
       	}
       
       	std::string MakeReverse()
       	{
		if (!TMyString.empty())
		{
       			setlocale(LC_ALL, "");       	
			_strrev(const_cast<char*>(TMyString.c_str()));
		}
		return TMyString;
       	}
private:
	char* _format(const char *pcFormat, va_list argList)
	{
		long len = _vscprintf( pcFormat, argList ) + 1;
		buf = new (std::nothrow) char[ len * sizeof(char) ];
		if(buf == NULL) 
			return "";
		else 
		{
			vsprintf_s( buf, len, pcFormat, argList );
			return buf;
		}
	}	
	
	void clearBuf()
	{
		delete[] buf;
		buf = nullptr;
	}
	std::string TMyString;
	char* buf;
};
}

