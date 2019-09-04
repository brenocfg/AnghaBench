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
typedef  char* PWSTR ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  scalar_t__ LONG ;
typedef  int INT ;

/* Variables and functions */
 int /*<<< orphan*/  ConPrintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  ConPuts (int /*<<< orphan*/ ,char*) ; 
 int FORMAT_MESSAGE_ALLOCATE_BUFFER ; 
 int FORMAT_MESSAGE_ARGUMENT_ARRAY ; 
 int FORMAT_MESSAGE_FROM_HMODULE ; 
 int FORMAT_MESSAGE_FROM_SYSTEM ; 
 int /*<<< orphan*/  FormatMessageW (int,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LANG_USER_DEFAULT ; 
 int /*<<< orphan*/  LocalFree (char*) ; 
 scalar_t__ MAX_LANMAN_MESSAGE_ID ; 
 scalar_t__ MIN_LANMAN_MESSAGE_ID ; 
 int /*<<< orphan*/  MSG_HELPMSG_HELP ; 
 int /*<<< orphan*/  MSG_HELPMSG_SYNTAX ; 
 int /*<<< orphan*/  PrintErrorMessage (int) ; 
 int /*<<< orphan*/  PrintMessageString (int) ; 
 int /*<<< orphan*/  PrintNetMessage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StdOut ; 
 scalar_t__ _wcsicmp (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * hModuleNetMsg ; 
 scalar_t__ wcstol (int /*<<< orphan*/ *,char**,int) ; 

INT cmdHelpMsg(INT argc, WCHAR **argv)
{
    INT i;
    LONG errNum;
    PWSTR endptr;
    PWSTR pBuffer;
    PWSTR pInserts[10] = {L"***", L"***", L"***", L"***",
                          L"***", L"***", L"***", L"***",
                          L"***", NULL};

    if (argc < 3)
    {
        PrintMessageString(4381);
        ConPuts(StdOut, L"\n");
        PrintNetMessage(MSG_HELPMSG_SYNTAX);
        return 1;
    }

    for (i = 2; i < argc; i++)
    {
        if (_wcsicmp(argv[i], L"/help") == 0)
        {
            PrintMessageString(4381);
            ConPuts(StdOut, L"\n");
            PrintNetMessage(MSG_HELPMSG_SYNTAX);
            PrintNetMessage(MSG_HELPMSG_HELP);
            return 1;
        }
    }

    errNum = wcstol(argv[2], &endptr, 10);
    if (*endptr != 0)
    {
        PrintMessageString(4381);
        ConPuts(StdOut, L"\n");
        PrintNetMessage(MSG_HELPMSG_SYNTAX);
        return 1;
    }

    if (errNum >= MIN_LANMAN_MESSAGE_ID && errNum <= MAX_LANMAN_MESSAGE_ID)
    {
        FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_HMODULE |
                       FORMAT_MESSAGE_ARGUMENT_ARRAY,
                       hModuleNetMsg,
                       errNum,
                       LANG_USER_DEFAULT,
                       (LPWSTR)&pBuffer,
                       0,
                       (va_list *)pInserts);
        if (pBuffer)
        {
            ConPrintf(StdOut, L"\n%s\n", pBuffer);
            LocalFree(pBuffer);
        }
        else
        {
            PrintErrorMessage(3871);
        }
    }
    else
    {
        /* Retrieve the message string without appending extra newlines */
        FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM |
                       FORMAT_MESSAGE_ARGUMENT_ARRAY,
                       NULL,
                       errNum,
                       LANG_USER_DEFAULT,
                       (LPWSTR)&pBuffer,
                       0,
                       (va_list *)pInserts);
        if (pBuffer)
        {
            ConPrintf(StdOut, L"\n%s\n", pBuffer);
            LocalFree(pBuffer);
        }
        else
        {
            PrintErrorMessage(3871);
        }
    }

    return 0;
}