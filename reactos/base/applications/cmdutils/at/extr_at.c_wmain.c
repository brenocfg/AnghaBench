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
typedef  int WCHAR ;
typedef  scalar_t__ ULONG ;
typedef  scalar_t__ UCHAR ;
typedef  int* PWSTR ;
typedef  int INT ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int AddJob (int*,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int*) ; 
 int /*<<< orphan*/  ConInitStdStreams () ; 
 int /*<<< orphan*/  ConResPuts (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int DeleteJob (int*,scalar_t__,scalar_t__) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  FreeDaysOfWeekArray () ; 
 scalar_t__ GetCurrentDayOfMonth () ; 
 int /*<<< orphan*/  IDS_USAGE ; 
 int /*<<< orphan*/  InitDaysOfWeekArray () ; 
 scalar_t__ ParseDaysOfMonth (int*,scalar_t__*) ; 
 scalar_t__ ParseDaysOfWeek (int*,scalar_t__*) ; 
 scalar_t__ ParseId (int*,scalar_t__*) ; 
 scalar_t__ ParseTime (int*,scalar_t__*,scalar_t__*) ; 
 int PrintAllJobs (int*) ; 
 int PrintJobDetails (int*,scalar_t__) ; 
 int /*<<< orphan*/  StdOut ; 
 scalar_t__ TRUE ; 
 scalar_t__ _wcsicmp (int*,char*) ; 
 scalar_t__ _wcsnicmp (int*,char*,int) ; 

int wmain(int argc, WCHAR **argv)
{
    PWSTR pszComputerName = NULL;
    PWSTR pszCommand = NULL;
    ULONG ulJobId = (ULONG)-1;
    ULONG ulJobHour = (ULONG)-1;
    ULONG ulJobMinute = (ULONG)-1;
    BOOL bDeleteJob = FALSE, bForceDelete = FALSE;
    BOOL bInteractiveJob = FALSE, bPeriodicJob = FALSE;
    BOOL bPrintUsage = FALSE;
    ULONG ulDaysOfMonth = 0;
    UCHAR ucDaysOfWeek = 0;
    INT nResult = 0;
    INT i, minIdx;

    /* Initialize the Console Standard Streams */
    ConInitStdStreams();

    if (!InitDaysOfWeekArray())
        return 1;

    /* Parse the computer name */
    i = 1;
    minIdx = 1;
    if (i < argc &&
        argv[i][0] == L'\\' &&
        argv[i][1] == L'\\')
    {
        pszComputerName = argv[i];
        i++;
        minIdx++;
    }

    /* Parse the time or job id */
    if (i < argc && argv[i][0] != L'/')
    {
        if (ParseTime(argv[i], &ulJobHour, &ulJobMinute))
        {
            i++;
            minIdx++;
        }
        else if (ParseId(argv[i], &ulJobId))
        {
            i++;
            minIdx++;
        }
    }

    /* Parse the options */
    for (; i < argc; i++)
    {
        if (argv[i][0] == L'/')
        {
            if (_wcsicmp(argv[i], L"/?") == 0)
            {
                bPrintUsage = TRUE;
                goto done;
            }
            else if (_wcsicmp(argv[i], L"/delete") == 0)
            {
                bDeleteJob = TRUE;
            }
            else if (_wcsicmp(argv[i], L"/yes") == 0)
            {
                bForceDelete = TRUE;
            }
            else if (_wcsicmp(argv[i], L"/interactive") == 0)
            {
                bInteractiveJob = TRUE;
            }
            else if (_wcsnicmp(argv[i], L"/every:", 7) == 0)
            {
                bPeriodicJob = TRUE;
                if (ParseDaysOfMonth(&(argv[i][7]), &ulDaysOfMonth) == FALSE)
                {
                    if (ParseDaysOfWeek(&(argv[i][7]), &ucDaysOfWeek) == FALSE)
                    {
                        ulDaysOfMonth = GetCurrentDayOfMonth();
                    }
                }
            }
            else if (_wcsnicmp(argv[i], L"/next:", 6) == 0)
            {
                bPeriodicJob = FALSE;
                if (ParseDaysOfMonth(&(argv[i][6]), &ulDaysOfMonth) == FALSE)
                {
                    if (ParseDaysOfWeek(&(argv[i][6]), &ucDaysOfWeek) == FALSE)
                    {
                        ulDaysOfMonth = GetCurrentDayOfMonth();
                    }
                }
            }
            else
            {
                bPrintUsage = TRUE;
                nResult = 1;
                goto done;
            }
        }
    }

    /* Parse the command */
    if (argc > minIdx && argv[argc - 1][0] != L'/')
    {
        pszCommand = argv[argc - 1];
    }

    if (bDeleteJob == TRUE)
    {
        /* Check for invalid options or arguments */
        if (bInteractiveJob == TRUE ||
            ulJobHour != (ULONG)-1 ||
            ulJobMinute != (ULONG)-1 ||
            ulDaysOfMonth != 0 ||
            ucDaysOfWeek != 0 ||
            pszCommand != NULL)
        {
            bPrintUsage = TRUE;
            nResult = 1;
            goto done;
        }

        nResult = DeleteJob(pszComputerName,
                            ulJobId,
                            bForceDelete);
    }
    else
    {
        if (ulJobHour != (ULONG)-1 && ulJobMinute != (ULONG)-1)
        {
            /* Check for invalid options or arguments */
            if (bForceDelete == TRUE ||
                pszCommand == NULL)
            {
                bPrintUsage = TRUE;
                nResult = 1;
                goto done;
            }

            nResult = AddJob(pszComputerName,
                             ulJobHour,
                             ulJobMinute,
                             ulDaysOfMonth,
                             ucDaysOfWeek,
                             bInteractiveJob,
                             bPeriodicJob,
                             pszCommand);
        }
        else
        {
            /* Check for invalid options or arguments */
            if (bForceDelete == TRUE ||
                bInteractiveJob == TRUE ||
                ulDaysOfMonth != 0 ||
                ucDaysOfWeek != 0 ||
                pszCommand != NULL)
            {
                bPrintUsage = TRUE;
                nResult = 1;
                goto done;
            }

            if (ulJobId == (ULONG)-1)
            {
                nResult = PrintAllJobs(pszComputerName);
            }
            else
            {
                nResult = PrintJobDetails(pszComputerName,
                                          ulJobId);
            }
        }
    }

done:
    FreeDaysOfWeekArray();

    if (bPrintUsage == TRUE)
        ConResPuts(StdOut, IDS_USAGE);

    return nResult;
}