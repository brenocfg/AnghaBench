#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct format_args {int /*<<< orphan*/  last; scalar_t__ list; } ;
typedef  char WCHAR ;
typedef  char ULONG_PTR ;
typedef  char* LPWSTR ;
typedef  char* LPCWSTR ;
typedef  int DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ACP ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 char* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int,char*,int) ; 
 char get_arg (int,int,struct format_args*) ; 
 scalar_t__ isdigitW (char) ; 
 int max (int,int) ; 
 int snprintfW (char*,int,char*,char) ; 
 int /*<<< orphan*/  sprintfW (char*,char const*,char) ; 
 int /*<<< orphan*/  strcpyW (char*,char const*) ; 
 int strlenW (char const*) ; 

__attribute__((used)) static LPCWSTR format_insert( BOOL unicode_caller, int insert, LPCWSTR format,
                              DWORD flags, struct format_args *args,
                              LPWSTR *result )
{
    static const WCHAR fmt_u[] = {'%','u',0};
    WCHAR *wstring = NULL, *p, fmt[256];
    ULONG_PTR arg;
    int size;

    if (*format != '!')  /* simple string */
    {
        arg = get_arg( insert, flags, args );
        if (unicode_caller || !arg)
        {
            static const WCHAR nullW[] = {'(','n','u','l','l',')',0};
            const WCHAR *str = (const WCHAR *)arg;

            if (!str) str = nullW;
            *result = HeapAlloc( GetProcessHeap(), 0, (strlenW(str) + 1) * sizeof(WCHAR) );
            strcpyW( *result, str );
        }
        else
        {
            const char *str = (const char *)arg;
            DWORD length = MultiByteToWideChar( CP_ACP, 0, str, -1, NULL, 0 );
            *result = HeapAlloc( GetProcessHeap(), 0, length * sizeof(WCHAR) );
            MultiByteToWideChar( CP_ACP, 0, str, -1, *result, length );
        }
        return format;
    }

    format++;
    p = fmt;
    *p++ = '%';

    while (*format == '0' ||
           *format == '+' ||
           *format == '-' ||
           *format == ' ' ||
           *format == '*' ||
           *format == '#')
    {
        if (*format == '*')
        {
            p += sprintfW( p, fmt_u, get_arg( insert, flags, args ));
            insert = -1;
            format++;
        }
        else *p++ = *format++;
    }
    while (isdigitW(*format)) *p++ = *format++;

    if (*format == '.')
    {
        *p++ = *format++;
        if (*format == '*')
        {
            p += sprintfW( p, fmt_u, get_arg( insert, flags, args ));
            insert = -1;
            format++;
        }
        else
            while (isdigitW(*format)) *p++ = *format++;
    }

    /* replicate MS bug: drop an argument when using va_list with width/precision */
    if (insert == -1 && args->list) args->last--;
    arg = get_arg( insert, flags, args );

    /* check for ascii string format */
    if ((format[0] == 'h' && format[1] == 's') ||
        (format[0] == 'h' && format[1] == 'S') ||
        (unicode_caller && format[0] == 'S') ||
        (!unicode_caller && format[0] == 's'))
    {
        DWORD len = MultiByteToWideChar( CP_ACP, 0, (char *)arg, -1, NULL, 0 );
        wstring = HeapAlloc( GetProcessHeap(), 0, len * sizeof(WCHAR) );
        MultiByteToWideChar( CP_ACP, 0, (char *)arg, -1, wstring, len );
        arg = (ULONG_PTR)wstring;
        *p++ = 's';
    }
    /* check for ascii character format */
    else if ((format[0] == 'h' && format[1] == 'c') ||
             (format[0] == 'h' && format[1] == 'C') ||
             (unicode_caller && format[0] == 'C') ||
             (!unicode_caller && format[0] == 'c'))
    {
        char ch = arg;
        wstring = HeapAlloc( GetProcessHeap(), 0, 2 * sizeof(WCHAR) );
        MultiByteToWideChar( CP_ACP, 0, &ch, 1, wstring, 1 );
        wstring[1] = 0;
        arg = (ULONG_PTR)wstring;
        *p++ = 's';
    }
    /* check for wide string format */
    else if ((format[0] == 'l' && format[1] == 's') ||
             (format[0] == 'l' && format[1] == 'S') ||
             (format[0] == 'w' && format[1] == 's') ||
             (!unicode_caller && format[0] == 'S'))
    {
        *p++ = 's';
    }
    /* check for wide character format */
    else if ((format[0] == 'l' && format[1] == 'c') ||
             (format[0] == 'l' && format[1] == 'C') ||
             (format[0] == 'w' && format[1] == 'c') ||
             (!unicode_caller && format[0] == 'C'))
    {
        *p++ = 'c';
    }
    /* FIXME: handle I64 etc. */
    else while (*format && *format != '!') *p++ = *format++;

    *p = 0;
    size = 256;
    for (;;)
    {
        WCHAR *ret = HeapAlloc( GetProcessHeap(), 0, size * sizeof(WCHAR) );
        int needed = snprintfW( ret, size, fmt, arg );
        if (needed == -1 || needed >= size)
        {
            HeapFree( GetProcessHeap(), 0, ret );
            size = max( needed + 1, size * 2 );
        }
        else
        {
            *result = ret;
            break;
        }
    }

    while (*format && *format != '!') format++;
    if (*format == '!') format++;

    HeapFree( GetProcessHeap(), 0, wstring );
    return format;
}