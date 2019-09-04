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

/* Variables and functions */
 int /*<<< orphan*/  ConInitStdStreams () ; 
 int /*<<< orphan*/  ConPuts (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ConResPuts (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DisplayError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EWX_LOGOFF ; 
 int /*<<< orphan*/  ExitWindowsEx (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  IDS_LOGOFF_LOCAL ; 
 int /*<<< orphan*/  IDS_LOGOFF_REMOTE ; 
 int /*<<< orphan*/  IDS_USAGE ; 
 int /*<<< orphan*/  ParseCommandLine (int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  StdErr ; 
 int /*<<< orphan*/  StdOut ; 
 scalar_t__ bVerbose ; 
 scalar_t__ szRemoteServerName ; 

int wmain(int argc, WCHAR *argv[])
{
    /* Initialize the Console Standard Streams */
    ConInitStdStreams();

    /* Parse command line */
    if (!ParseCommandLine(argc, argv))
    {
        ConResPuts(StdOut, IDS_USAGE);
        return 1;
    }

    /* Should we log off session on remote server? */
    if (szRemoteServerName)
    {
        if (bVerbose)
            ConResPuts(StdOut, IDS_LOGOFF_REMOTE);

        // FIXME: Add Remote Procedure Call to logoff user on a remote machine
        ConPuts(StdErr, L"Remote Procedure Call in logoff.exe has not been implemented");
    }
    /* Perform logoff of current session on local machine instead */
    else
    {
        if (bVerbose)
        {
            /* Get resource string and print it */
            ConResPuts(StdOut, IDS_LOGOFF_LOCAL);
        }

        /* Actual logoff */
        if (!ExitWindowsEx(EWX_LOGOFF, 0))
        {
            DisplayError(GetLastError());
            return 1;
        }
    }

    return 0;
}