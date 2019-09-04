#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ulEventIdentifier ;
typedef  int /*<<< orphan*/  ulEventCategory ;
typedef  int /*<<< orphan*/  szSystem ;
typedef  int /*<<< orphan*/  szPassword ;
typedef  int /*<<< orphan*/  szLogName ;
typedef  int /*<<< orphan*/  szEventType ;
typedef  int /*<<< orphan*/  szEventSource ;
typedef  int /*<<< orphan*/  szDomainUser ;
typedef  int /*<<< orphan*/  szDescription ;
typedef  int /*<<< orphan*/  bDisplayHelp ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  scalar_t__ ULONG ;
struct TYPE_12__ {char* OptionStr; } ;
struct TYPE_10__ {int /*<<< orphan*/  Sid; } ;
struct TYPE_11__ {TYPE_1__ User; } ;
typedef  char* PWSTR ;
typedef  TYPE_2__* PTOKEN_USER ;
typedef  TYPE_3__ OPTION ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  char* BOOL ;

/* Variables and functions */
 char* APPLICATION_NAME ; 
 int /*<<< orphan*/  ARRAYSIZE (TYPE_3__*) ; 
 int /*<<< orphan*/  CheckLogOrSourceExistence (char*,char*,char*,char*) ; 
 int /*<<< orphan*/  CloseEventLog (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ConInitStdStreams () ; 
 int /*<<< orphan*/  ConPuts (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ConResPrintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ConResPuts (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeregisterEventSource (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DoParse (int,int /*<<< orphan*/ **,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (int /*<<< orphan*/ )) ; 
 scalar_t__ EVENTLOG_ERROR_TYPE ; 
 scalar_t__ EVENTLOG_INFORMATION_TYPE ; 
 scalar_t__ EVENTLOG_SUCCESS ; 
 scalar_t__ EVENTLOG_WARNING_TYPE ; 
 scalar_t__ EVENT_ID_MAX ; 
 scalar_t__ EVENT_ID_MIN ; 
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 char* FALSE ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 scalar_t__ GetUserToken (TYPE_2__**) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  IDS_BADSYNTAX_7 ; 
 int /*<<< orphan*/  IDS_HELP ; 
 int /*<<< orphan*/  IDS_SUCCESS_1 ; 
 int /*<<< orphan*/  IDS_SUCCESS_2 ; 
 int /*<<< orphan*/  IDS_SUCCESS_3 ; 
 int /*<<< orphan*/  IDS_SWITCH_UNIMPLEMENTED ; 
 int /*<<< orphan*/  IDS_USAGE ; 
 int /*<<< orphan*/  InvalidSyntax ; 
 TYPE_3__ NEW_OPT (char*,int /*<<< orphan*/ ,int,int,int,...) ; 
 TYPE_3__ NEW_OPT_EX (char*,int /*<<< orphan*/ ,int,char*,int,int,char**) ; 
 int OPTION_ALLOWED_LIST ; 
 int OPTION_EXCLUSIVE ; 
 int OPTION_MANDATORY ; 
 int OPTION_NOT_EMPTY ; 
 int OPTION_TRIM_SPACE ; 
 int /*<<< orphan*/  OpenEventLogW (char*,char*) ; 
 int /*<<< orphan*/  PrintError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PrintParserError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RegisterEventSourceW (char*,char*) ; 
 char* ReportEventW (int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  StdErr ; 
 int /*<<< orphan*/  StdOut ; 
 int /*<<< orphan*/  TYPE_None ; 
 int /*<<< orphan*/  TYPE_Str ; 
 int /*<<< orphan*/  TYPE_U32 ; 
 scalar_t__ _wcsicmp (char*,char*) ; 

int wmain(int argc, WCHAR* argv[])
{
    BOOL Success = FALSE;
    HANDLE hEventLog;
    PTOKEN_USER pUserToken;

    /* Default option values */
    BOOL  bDisplayHelp  = FALSE;
    PWSTR szSystem      = NULL;
    PWSTR szDomainUser  = NULL;
    PWSTR szPassword    = NULL;
    PWSTR szLogName     = NULL;
    PWSTR szEventSource = NULL;
    PWSTR szEventType   = NULL;
    PWSTR szDescription = NULL;
    ULONG ulEventType   = EVENTLOG_INFORMATION_TYPE;
    ULONG ulEventCategory   = 0;
    ULONG ulEventIdentifier = 0;

    OPTION Options[] =
    {
        /* Help */
        NEW_OPT(L"?", TYPE_None, // ~= TYPE_Bool,
                OPTION_EXCLUSIVE,
                1,
                sizeof(bDisplayHelp), &bDisplayHelp),

        /* System */
        NEW_OPT(L"S", TYPE_Str,
                OPTION_NOT_EMPTY | OPTION_TRIM_SPACE,
                1,
                sizeof(szSystem), &szSystem),

        /* Domain & User */
        NEW_OPT(L"U", TYPE_Str,
                OPTION_NOT_EMPTY | OPTION_TRIM_SPACE,
                1,
                sizeof(szDomainUser), &szDomainUser),

        /* Password */
        NEW_OPT(L"P", TYPE_Str,
                0,
                1,
                sizeof(szPassword), &szPassword),

        /* Log name */
        NEW_OPT(L"L", TYPE_Str,
                OPTION_NOT_EMPTY | OPTION_TRIM_SPACE,
                1,
                sizeof(szLogName), &szLogName),

        /* Event source */
        NEW_OPT(L"SO", TYPE_Str,
                OPTION_NOT_EMPTY | OPTION_TRIM_SPACE,
                1,
                sizeof(szEventSource), &szEventSource),

        /* Event type */
        NEW_OPT_EX(L"T", TYPE_Str,
                   OPTION_MANDATORY | OPTION_NOT_EMPTY | OPTION_TRIM_SPACE | OPTION_ALLOWED_LIST,
                   L"SUCCESS|ERROR|WARNING|INFORMATION",
                   1,
                   sizeof(szEventType), &szEventType),

        /* Event category (ReactOS additional option) */
        NEW_OPT(L"C", TYPE_U32,
                0,
                1,
                sizeof(ulEventCategory), &ulEventCategory),

        /* Event ID */
        NEW_OPT(L"ID", TYPE_U32,
                OPTION_MANDATORY,
                1,
                sizeof(ulEventIdentifier), &ulEventIdentifier),

        /* Event description */
        NEW_OPT(L"D", TYPE_Str,
                OPTION_MANDATORY,
                1,
                sizeof(szDescription), &szDescription),
    };
#define OPT_SYSTEM  (Options[1])
#define OPT_USER    (Options[2])
#define OPT_PASSWD  (Options[3])
#define OPT_EVTID   (Options[8])

    /* Initialize the Console Standard Streams */
    ConInitStdStreams();

    /* Parse command line for options */
    if (!DoParse(argc, argv, Options, ARRAYSIZE(Options), PrintParserError))
        return EXIT_FAILURE;

    /* Finalize options validity checks */

    if (bDisplayHelp)
    {
        if (argc > 2)
        {
            /* Invalid syntax */
            PrintParserError(InvalidSyntax);
            return EXIT_FAILURE;
        }

        ConResPuts(StdOut, IDS_HELP);
        return EXIT_SUCCESS;
    }

    if (szSystem || szDomainUser || szPassword)
    {
        // TODO: Implement!
        if (szSystem)
            ConResPrintf(StdOut, IDS_SWITCH_UNIMPLEMENTED, OPT_SYSTEM.OptionStr);
        if (szDomainUser)
            ConResPrintf(StdOut, IDS_SWITCH_UNIMPLEMENTED, OPT_USER.OptionStr);
        if (szPassword)
            ConResPrintf(StdOut, IDS_SWITCH_UNIMPLEMENTED, OPT_PASSWD.OptionStr);
        return EXIT_FAILURE;
    }

    if (ulEventIdentifier < EVENT_ID_MIN || ulEventIdentifier > EVENT_ID_MAX)
    {
        /* Invalid event identifier */
        ConResPrintf(StdErr, IDS_BADSYNTAX_7, OPT_EVTID.OptionStr, EVENT_ID_MIN, EVENT_ID_MAX);
        ConResPuts(StdErr, IDS_USAGE);
        return EXIT_FAILURE;
    }

    /*
     * Set the event type. Note that we forbid the user
     * to use security auditing types.
     */
    if (_wcsicmp(szEventType, L"SUCCESS") == 0)
        ulEventType = EVENTLOG_SUCCESS;
    else
    if (_wcsicmp(szEventType, L"ERROR") == 0)
        ulEventType = EVENTLOG_ERROR_TYPE;
    else
    if (_wcsicmp(szEventType, L"WARNING") == 0)
        ulEventType = EVENTLOG_WARNING_TYPE;
    else
    if (_wcsicmp(szEventType, L"INFORMATION") == 0)
        ulEventType = EVENTLOG_INFORMATION_TYPE;
    else
    {
        /* Use a default event type */
        ulEventType = EVENTLOG_SUCCESS;
    }

    /*
     * If we have a source, do not care about the log (as long as we will be
     * able to find the source later).
     * But if we do not have a source, then two cases:
     * - either we have a log name so that we will use OpenEventLog (and use
     *   default log's source), unless this is the Application log in which case
     *   we use the default source;
     * - or we do not have a log name so that we use default log and source names.
     */
    if (!szEventSource)
    {
        if (!szLogName)
            szLogName = L"Application";

        if (_wcsicmp(szLogName, L"Application") == 0)
            szEventSource = APPLICATION_NAME;
    }

    // FIXME: Check whether szLogName == L"Security" !!

    /*
     * The event APIs OpenEventLog and RegisterEventSource fall back to using
     * the 'Application' log when the specified log name or event source do not
     * exist on the system.
     * To prevent that and be able to error the user that the specified log name
     * or event source do not exist, we need to manually perform the existence
     * checks by ourselves.
     *
     * Check whether either the specified event log OR event source exist on
     * the system. If the event log does not exist, return an error. Otherwise
     * check whether a specified source already exists (everywhere). If found
     * in a different log, return an error. If not found, create the source
     * in the specified event log.
     *
     * NOTE: By default we forbid the usage of application (non-custom) sources.
     * An optional switch can be added to EventCreate to allow such sources
     * to be used.
     */
    if (!CheckLogOrSourceExistence(szSystem, szLogName, szEventSource, FALSE))
    {
        PrintError(GetLastError());
        return EXIT_FAILURE;
    }

    /* Open the event log, by source or by log name */
    if (szEventSource) // && *szEventSource
        hEventLog = RegisterEventSourceW(szSystem, szEventSource);
    else
        hEventLog = OpenEventLogW(szSystem, szLogName);

    if (!hEventLog)
    {
        PrintError(GetLastError());
        return EXIT_FAILURE;
    }

    /* Retrieve the current user token and report the event */
    if (GetUserToken(&pUserToken))
    {
        Success = ReportEventW(hEventLog,
                               ulEventType,
                               ulEventCategory,
                               ulEventIdentifier,
                               pUserToken->User.Sid,
                               1,   // One string
                               0,   // No raw data
                               (LPCWSTR*)&szDescription,
                               NULL // No raw data
                               );
        if (!Success)
        {
            PrintError(GetLastError());
            ConPuts(StdErr, L"Failed to report event!\n");
        }
        else
        {
            /* Show success */
            ConPuts(StdOut, L"\n");
            if (!szEventSource)
                ConResPrintf(StdOut, IDS_SUCCESS_1, szEventType, szLogName);
            else if (!szLogName)
                ConResPrintf(StdOut, IDS_SUCCESS_2, szEventType, szEventSource);
            else
                ConResPrintf(StdOut, IDS_SUCCESS_3, szEventType, szLogName, szEventSource);
        }

        HeapFree(GetProcessHeap(), 0, pUserToken);
    }
    else
    {
        PrintError(GetLastError());
        ConPuts(StdErr, L"GetUserToken() failed!\n");
    }

    /* Close the event log */
    if (szEventSource && *szEventSource)
        DeregisterEventSource(hEventLog);
    else
        CloseEventLog(hEventLog);

    return (Success ? EXIT_SUCCESS : EXIT_FAILURE);
}