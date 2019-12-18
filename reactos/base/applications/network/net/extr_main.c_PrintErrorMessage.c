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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  VOID ;
typedef  int /*<<< orphan*/ * PWSTR ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  char* DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ConPrintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 char* ERROR_SUCCESS ; 
 int FORMAT_MESSAGE_ALLOCATE_BUFFER ; 
 int FORMAT_MESSAGE_ARGUMENT_ARRAY ; 
 int FORMAT_MESSAGE_FROM_HMODULE ; 
 int FORMAT_MESSAGE_FROM_SYSTEM ; 
 int FORMAT_MESSAGE_IGNORE_INSERTS ; 
 int /*<<< orphan*/  FormatMessageW (int,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  LANG_USER_DEFAULT ; 
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ *) ; 
 char* MAX_LANMAN_MESSAGE_ID ; 
 char* MIN_LANMAN_MESSAGE_ID ; 
 int /*<<< orphan*/  StdErr ; 
 int /*<<< orphan*/  hModuleNetMsg ; 
 int /*<<< orphan*/  swprintf (int /*<<< orphan*/ *,char*,char*) ; 

VOID
PrintErrorMessage(
    DWORD dwError)
{
    WCHAR szErrorBuffer[16];
    PWSTR pBuffer;
    PWSTR pErrorInserts[2] = {NULL, NULL};

    if (dwError >= MIN_LANMAN_MESSAGE_ID && dwError <= MAX_LANMAN_MESSAGE_ID)
    {
        FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_HMODULE |
                       FORMAT_MESSAGE_IGNORE_INSERTS,
                       hModuleNetMsg,
                       dwError,
                       LANG_USER_DEFAULT,
                       (LPWSTR)&pBuffer,
                       0,
                       NULL);
        if (pBuffer)
        {
            ConPrintf(StdErr, L"%s\n", pBuffer);
            LocalFree(pBuffer);
            pBuffer = NULL;
        }
    }
    else
    {
        FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM |
                       FORMAT_MESSAGE_IGNORE_INSERTS,
                       NULL,
                       dwError,
                       LANG_USER_DEFAULT,
                       (LPWSTR)&pBuffer,
                       0,
                       NULL);
        if (pBuffer)
        {
            ConPrintf(StdErr, L"%s\n", pBuffer);
            LocalFree(pBuffer);
            pBuffer = NULL;
        }
    }

    if (dwError != ERROR_SUCCESS)
    {
        /* Format insert for the 3514 message */
        swprintf(szErrorBuffer, L"%lu", dwError);
        pErrorInserts[0] = szErrorBuffer;

        /* Format and print the 3514 message */
        FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_HMODULE |
                       FORMAT_MESSAGE_ARGUMENT_ARRAY,
                       hModuleNetMsg,
                       3514,
                       LANG_USER_DEFAULT,
                       (LPWSTR)&pBuffer,
                       0,
                       (va_list *)pErrorInserts);
        if (pBuffer)
        {
            ConPrintf(StdErr, L"%s\n", pBuffer);
            LocalFree(pBuffer);
            pBuffer = NULL;
        }
    }
}