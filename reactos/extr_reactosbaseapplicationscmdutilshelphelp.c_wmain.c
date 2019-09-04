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
typedef  int /*<<< orphan*/  CmdLine ;

/* Variables and functions */
 int CMDLINE_LENGTH ; 
 int /*<<< orphan*/  ConInitStdStreams () ; 
 int /*<<< orphan*/  ConResPrintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ConResPuts (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDS_HELP1 ; 
 int /*<<< orphan*/  IDS_HELP2 ; 
 int /*<<< orphan*/  IDS_NO_ENTRY ; 
 int /*<<< orphan*/  IDS_USAGE ; 
 int /*<<< orphan*/  IsInternalCommand (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  StdOut ; 
 int /*<<< orphan*/  StringCbPrintfW (int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _flushall () ; 
 int _wsystem (int /*<<< orphan*/ *) ; 
 scalar_t__ wcscmp (int /*<<< orphan*/ *,char*) ; 

int wmain(int argc, WCHAR* argv[])
{
    WCHAR CmdLine[CMDLINE_LENGTH];

    /* Initialize the Console Standard Streams */
    ConInitStdStreams();

    /*
     * If the user hasn't asked for specific help,
     * then print out the list of available commands.
     */
    if (argc <= 1)
    {
        ConResPuts(StdOut, IDS_HELP1);
        ConResPuts(StdOut, IDS_HELP2);
        return 0;
    }

    /*
     * Bad usage (too much options) or we use the /? switch.
     * Display help for the HELP command.
     */
    if ((argc > 2) || (wcscmp(argv[1], L"/?") == 0))
    {
        ConResPuts(StdOut, IDS_USAGE);
        return 0;
    }

    /*
     * If the command is not an internal one,
     * display an information message and exit.
     */
    if (!IsInternalCommand(argv[1]))
    {
        ConResPrintf(StdOut, IDS_NO_ENTRY, argv[1]);
        return 0;
    }

    /*
     * Run "<command> /?" in the current command processor.
     */
    StringCbPrintfW(CmdLine, sizeof(CmdLine), L"%ls /?", argv[1]);

    _flushall();
    return _wsystem(CmdLine);
}