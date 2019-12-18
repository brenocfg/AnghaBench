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
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  HANDLE ;

/* Variables and functions */
 char* escape_string (char*,size_t,size_t*) ; 
 int /*<<< orphan*/  heap_free (char*) ; 
 char* heap_xalloc (size_t) ; 
 size_t lstrlenW (char const*) ; 
 size_t sprintfW (char*,char const*,char*) ; 
 int /*<<< orphan*/  write_file (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static size_t export_value_name(HANDLE hFile, WCHAR *name, size_t len)
{
    static const WCHAR quoted_fmt[] = {'"','%','s','"','=',0};
    static const WCHAR default_name[] = {'@','=',0};
    size_t line_len;

    if (name && *name)
    {
        WCHAR *str = escape_string(name, len, &line_len);
        WCHAR *buf = heap_xalloc((line_len + 4) * sizeof(WCHAR));
        line_len = sprintfW(buf, quoted_fmt, str);
        write_file(hFile, buf);
        heap_free(buf);
        heap_free(str);
    }
    else
    {
        line_len = lstrlenW(default_name);
        write_file(hFile, default_name);
    }

    return line_len;
}