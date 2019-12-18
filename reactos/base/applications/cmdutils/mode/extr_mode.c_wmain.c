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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int SIZE_T ;
typedef  int* PWSTR ;
typedef  int* PCWSTR ;
typedef  int INT ;

/* Variables and functions */
 int /*<<< orphan*/  ConInitStdStreams () ; 
 int /*<<< orphan*/  ConPuts (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ConResPrintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ConResPuts (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EnumerateDevices () ; 
 int* FindPortNum (int*,int*) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  IDS_ERROR_INVALID_PARAMETER ; 
 int /*<<< orphan*/  IDS_USAGE ; 
 int SetConsoleCPState (int*) ; 
 int SetConsoleState (int*) ; 
 int SetConsoleStateOld (int*) ; 
 int SetSerialState (int,int*) ; 
 int ShowConsoleCPStatus () ; 
 int ShowConsoleStatus () ; 
 int ShowParallelStatus (int) ; 
 int ShowSerialStatus (int) ; 
 int /*<<< orphan*/  StdErr ; 
 int /*<<< orphan*/  StdOut ; 
 scalar_t__ _wcsnicmp (int*,char*,int) ; 
 int /*<<< orphan*/  wcscpy (int*,int /*<<< orphan*/ *) ; 
 scalar_t__ wcslen (int /*<<< orphan*/ *) ; 
 scalar_t__ wcsstr (int*,char*) ; 

int wmain(int argc, WCHAR* argv[])
{
    int ret = 0;
    int arg;
    SIZE_T ArgStrSize;
    PCWSTR ArgStr, argStr;

    INT nPortNum;

    /* Initialize the Console Standard Streams */
    ConInitStdStreams();

    /*
     * MODE.COM has a very peculiar way of parsing its arguments,
     * as they can be even not separated by any space. This extreme
     * behaviour certainly is present for backwards compatibility
     * with the oldest versions of the utility present on MS-DOS.
     *
     * For example, such a command:
     *   "MODE.COM COM1baud=9600parity=ndata=8stop=1xon=onto=on"
     * will be correctly understood as:
     *   "MODE.COM COM1 baud=9600 parity=n data=8 stop=1 xon=on to=on"
     *
     * Note also that the "/STATUS" switch is actually really "/STA".
     *
     * However we will not use GetCommandLine() because we do not want
     * to deal with the prepended application path and try to find
     * where the arguments start. Our approach here will consist in
     * flattening the arguments vector.
     */
    ArgStrSize = 0;

    /* Compute the space needed for the new string, and allocate it */
    for (arg = 1; arg < argc; arg++)
    {
        ArgStrSize += wcslen(argv[arg]) + 1; // 1 for space
    }
    ArgStr = HeapAlloc(GetProcessHeap(), 0, (ArgStrSize + 1) * sizeof(WCHAR));
    if (ArgStr == NULL)
    {
        ConPuts(StdErr, L"ERROR: Not enough memory\n");
        return 1;
    }

    /* Copy the contents and NULL-terminate the string */
    argStr = ArgStr;
    for (arg = 1; arg < argc; arg++)
    {
        wcscpy((PWSTR)argStr, argv[arg]);
        argStr += wcslen(argv[arg]);
        *(PWSTR)argStr++ = L' ';
    }
    *(PWSTR)argStr = L'\0';

    /* Parse the command line */
    argStr = ArgStr;

    while (*argStr == L' ') argStr++;
    if (!*argStr) goto show_status;

    if (wcsstr(argStr, L"/?") || wcsstr(argStr, L"-?"))
    {
        ConResPuts(StdOut, IDS_USAGE);
        goto Quit;
    }
    else if (_wcsnicmp(argStr, L"/STA", 4) == 0)
    {
        /* Skip this parameter */
        while (*argStr != L' ') argStr++;
        /* Skip any delimiter */
        while (*argStr == L' ') argStr++;

        /* The presence of any other parameter is invalid */
        if (*argStr)
            goto invalid_parameter;

        goto show_status;
    }
    else if (_wcsnicmp(argStr, L"LPT", 3) == 0)
    {
        argStr = FindPortNum(argStr+3, &nPortNum);
        if (!argStr || nPortNum == -1)
            goto invalid_parameter;

        if (*argStr == L':') argStr++;
        while (*argStr == L' ') argStr++;

        if (!*argStr || _wcsnicmp(argStr, L"/STA", 4) == 0)
            ret = ShowParallelStatus(nPortNum);
        else
            ConPuts(StdErr, L"ERROR: LPT port redirection is not implemented!\n");
        // TODO: Implement setting LPT port redirection using SetParallelState().
        goto Quit;
    }
    else if (_wcsnicmp(argStr, L"COM", 3) == 0)
    {
        argStr = FindPortNum(argStr+3, &nPortNum);
        if (!argStr || nPortNum == -1)
            goto invalid_parameter;

        if (*argStr == L':') argStr++;
        while (*argStr == L' ') argStr++;

        if (!*argStr || _wcsnicmp(argStr, L"/STA", 4) == 0)
            ret = ShowSerialStatus(nPortNum);
        else
            ret = SetSerialState(nPortNum, argStr);
        goto Quit;
    }
    else if (_wcsnicmp(argStr, L"CON", 3) == 0)
    {
        argStr += 3;

        if (*argStr == L':') argStr++;
        while (*argStr == L' ') argStr++;

        if (!*argStr || _wcsnicmp(argStr, L"/STA", 4) == 0)
        {
            ret = ShowConsoleStatus();
        }
        else if ( (_wcsnicmp(argStr, L"CP", 2) == 0 && (argStr += 2)) ||
                  (_wcsnicmp(argStr, L"CODEPAGE", 8) == 0 && (argStr += 8)) )
        {
            while (*argStr == L' ') argStr++;

            if (!*argStr || _wcsnicmp(argStr, L"/STA", 4) == 0)
                ret = ShowConsoleCPStatus();
            else
                ret = SetConsoleCPState(argStr);
        }
        else
        {
            ret = SetConsoleState(argStr);
        }
        goto Quit;
    }
    // else if (wcschr(argStr, L','))
    else
    {
        /* Old syntax: MODE [COLS],[LINES] */
        ret = SetConsoleStateOld(argStr);
        goto Quit;
    }

show_status:
    EnumerateDevices();
    goto Quit;

invalid_parameter:
    ConResPrintf(StdErr, IDS_ERROR_INVALID_PARAMETER, ArgStr);
    goto Quit;

Quit:
    /* Free the string and quit */
    HeapFree(GetProcessHeap(), 0, (PWSTR)ArgStr);
    return ret;
}