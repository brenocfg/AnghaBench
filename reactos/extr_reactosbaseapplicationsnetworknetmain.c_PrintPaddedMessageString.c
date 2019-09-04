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
typedef  int /*<<< orphan*/  VOID ;
typedef  int /*<<< orphan*/ * PWSTR ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  scalar_t__ INT ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ConPuts (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int FORMAT_MESSAGE_ALLOCATE_BUFFER ; 
 int FORMAT_MESSAGE_FROM_HMODULE ; 
 int FORMAT_MESSAGE_IGNORE_INSERTS ; 
 scalar_t__ FormatMessageW (int,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LANG_USER_DEFAULT ; 
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PrintPadding (int,scalar_t__) ; 
 int /*<<< orphan*/  StdOut ; 
 int /*<<< orphan*/  hModuleNetMsg ; 

VOID
PrintPaddedMessageString(
    DWORD dwMessage,
    INT nPaddedLength)
{
    PWSTR pBuffer;
    DWORD dwLength;

    dwLength = FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_HMODULE |
                              FORMAT_MESSAGE_IGNORE_INSERTS,
                              hModuleNetMsg,
                              dwMessage,
                              LANG_USER_DEFAULT,
                              (LPWSTR)&pBuffer,
                              0,
                              NULL);
    if (pBuffer)
    {
        ConPuts(StdOut, pBuffer);
        LocalFree(pBuffer);
        pBuffer = NULL;
    }

    if (dwLength < (DWORD)nPaddedLength)
        PrintPadding(L' ', (DWORD)nPaddedLength - dwLength);
}