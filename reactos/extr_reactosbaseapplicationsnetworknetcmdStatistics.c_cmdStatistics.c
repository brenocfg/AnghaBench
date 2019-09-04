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
typedef  size_t INT ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ConPuts (int /*<<< orphan*/ ,char*) ; 
 size_t DisplayServerStatistics () ; 
 size_t DisplayWorkstationStatistics () ; 
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  MSG_STATISTICS_HELP ; 
 int /*<<< orphan*/  MSG_STATISTICS_SYNTAX ; 
 int /*<<< orphan*/  PrintErrorMessage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PrintMessageString (int) ; 
 int /*<<< orphan*/  PrintNetMessage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StdOut ; 
 scalar_t__ TRUE ; 
 scalar_t__ _wcsicmp (int /*<<< orphan*/ *,char*) ; 

INT
cmdStatistics(
    INT argc,
    WCHAR **argv)
{
    INT i, result = 0;
    BOOL bServer = FALSE;
    BOOL bWorkstation = FALSE;

    for (i = 2; i < argc; i++)
    {
        if (_wcsicmp(argv[i], L"server") == 0)
        {
            if (bWorkstation == FALSE)
                bServer = TRUE;
            continue;
        }

        if (_wcsicmp(argv[i], L"workstation") == 0)
        {
            if (bServer == FALSE)
                bWorkstation = TRUE;
            continue;
        }

        if (_wcsicmp(argv[i], L"help") == 0)
        {
            /* Print short syntax help */
            PrintMessageString(4381);
            ConPuts(StdOut, L"\n");
            PrintNetMessage(MSG_STATISTICS_SYNTAX);
            return 0;
        }

        if (_wcsicmp(argv[i], L"/help") == 0)
        {
            /* Print full help text*/
            PrintMessageString(4381);
            ConPuts(StdOut, L"\n");
            PrintNetMessage(MSG_STATISTICS_SYNTAX);
            PrintNetMessage(MSG_STATISTICS_HELP);
            return 0;
        }
    }

    if (bServer)
    {
        result = DisplayServerStatistics();
    }
    else if (bWorkstation)
    {
        result = DisplayWorkstationStatistics();
    }
    else
    {
        PrintMessageString(4379);
        ConPuts(StdOut, L"\n");
        ConPuts(StdOut, L"   Server\n");
        ConPuts(StdOut, L"   Workstation\n");
        ConPuts(StdOut, L"\n");
    }

    if (result == 0)
        PrintErrorMessage(ERROR_SUCCESS);

    return result;
}