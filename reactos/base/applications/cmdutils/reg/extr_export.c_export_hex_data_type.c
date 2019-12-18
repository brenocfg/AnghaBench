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
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ REG_BINARY ; 
 int /*<<< orphan*/  heap_free (char*) ; 
 char* heap_xalloc (int) ; 
 size_t lstrlenW (char const*) ; 
 size_t sprintfW (char*,char const*,scalar_t__) ; 
 int /*<<< orphan*/  write_file (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static size_t export_hex_data_type(HANDLE hFile, DWORD type)
{
    static const WCHAR hex[] = {'h','e','x',':',0};
    static const WCHAR hexp_fmt[] = {'h','e','x','(','%','x',')',':',0};
    size_t line_len;

    if (type == REG_BINARY)
    {
        line_len = lstrlenW(hex);
        write_file(hFile, hex);
    }
    else
    {
        WCHAR *buf = heap_xalloc(15 * sizeof(WCHAR));
        line_len = sprintfW(buf, hexp_fmt, type);
        write_file(hFile, buf);
        heap_free(buf);
    }

    return line_len;
}