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
typedef  int /*<<< orphan*/  __ms_va_list ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int FORMAT_MESSAGE_ALLOCATE_BUFFER ; 
 int FORMAT_MESSAGE_FROM_STRING ; 
 scalar_t__ FormatMessageW (int,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ *) ; 
 scalar_t__ NO_ERROR ; 
 int /*<<< orphan*/  SetLastError (scalar_t__) ; 
 int /*<<< orphan*/  WINE_FIXME (char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  output_writeconsole (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  wine_dbgstr_w (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void output_formatstring(const WCHAR *fmt, __ms_va_list va_args)
{
    WCHAR *str;
    DWORD len;

    SetLastError(NO_ERROR);
    len = FormatMessageW(FORMAT_MESSAGE_FROM_STRING|FORMAT_MESSAGE_ALLOCATE_BUFFER,
                         fmt, 0, 0, (WCHAR *)&str, 0, &va_args);
    if (len == 0 && GetLastError() != NO_ERROR)
    {
        WINE_FIXME("Could not format string: le=%u, fmt=%s\n", GetLastError(), wine_dbgstr_w(fmt));
        return;
    }
    output_writeconsole(str, len);
    LocalFree(str);
}