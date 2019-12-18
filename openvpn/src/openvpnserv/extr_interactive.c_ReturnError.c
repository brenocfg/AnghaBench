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
typedef  int /*<<< orphan*/  va_list ;
typedef  int /*<<< orphan*/  VOID ;
typedef  char* LPWSTR ;
typedef  char* LPVOID ;
typedef  int /*<<< orphan*/  LPHANDLE ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  scalar_t__ DWORD_PTR ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_OPENVPN_STARTUP ; 
 int FORMAT_MESSAGE_ALLOCATE_BUFFER ; 
 int FORMAT_MESSAGE_ARGUMENT_ARRAY ; 
 int FORMAT_MESSAGE_FROM_STRING ; 
 int FORMAT_MESSAGE_FROM_SYSTEM ; 
 int FORMAT_MESSAGE_IGNORE_INSERTS ; 
 scalar_t__ FormatMessageW (int,char*,scalar_t__,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LocalFree (char*) ; 
 int /*<<< orphan*/  MSG_FLAGS_ERROR ; 
 int /*<<< orphan*/  MsgToEventLog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  WritePipeAsync (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int wcslen (char*) ; 

__attribute__((used)) static VOID
ReturnError(HANDLE pipe, DWORD error, LPCWSTR func, DWORD count, LPHANDLE events)
{
    DWORD result_len;
    LPWSTR result = L"0xffffffff\nFormatMessage failed\nCould not return result";
    DWORD_PTR args[] = {
        (DWORD_PTR) error,
        (DWORD_PTR) func,
        (DWORD_PTR) ""
    };

    if (error != ERROR_OPENVPN_STARTUP)
    {
        FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM
                       |FORMAT_MESSAGE_ALLOCATE_BUFFER
                       |FORMAT_MESSAGE_IGNORE_INSERTS,
                       0, error, 0, (LPWSTR) &args[2], 0, NULL);
    }

    result_len = FormatMessageW(FORMAT_MESSAGE_FROM_STRING
                                |FORMAT_MESSAGE_ALLOCATE_BUFFER
                                |FORMAT_MESSAGE_ARGUMENT_ARRAY,
                                L"0x%1!08x!\n%2!s!\n%3!s!", 0, 0,
                                (LPWSTR) &result, 0, (va_list *) args);

    WritePipeAsync(pipe, result, (DWORD)(wcslen(result) * 2), count, events);
#ifdef UNICODE
    MsgToEventLog(MSG_FLAGS_ERROR, result);
#else
    MsgToEventLog(MSG_FLAGS_ERROR, "%S", result);
#endif

    if (error != ERROR_OPENVPN_STARTUP)
    {
        LocalFree((LPVOID) args[2]);
    }
    if (result_len)
    {
        LocalFree(result);
    }
}