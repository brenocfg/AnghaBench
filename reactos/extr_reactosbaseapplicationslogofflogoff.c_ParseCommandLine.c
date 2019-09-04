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
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ConResPuts (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IDS_ILLEGAL_PARAM ; 
 int /*<<< orphan*/  StdErr ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  bVerbose ; 

BOOL ParseCommandLine(int argc, WCHAR *argv[])
{
    int i;

    // FIXME: Add handling of command-line arguments to select
    // the session number and name, and also name of remote machine.
    // Example: logoff.exe 4 /SERVER:Master
    // should logoff session number 4 on remote machine called Master.

    for (i = 1; i < argc; i++)
    {
        switch (argv[i][0])
        {
        case L'-':
        case L'/':
            // -v (verbose)
            if (argv[i][1] == L'v')
            {
                bVerbose = TRUE;
                break;
            }
            // -? (usage)
            else if (argv[i][1] == L'?')
            {
                /* Will display the Usage */
                return FALSE;
            }
        /* Fall through */
        default:
            /* Invalid parameter detected */
            ConResPuts(StdErr, IDS_ILLEGAL_PARAM);
            return FALSE;
        }
    }

    return TRUE;
}