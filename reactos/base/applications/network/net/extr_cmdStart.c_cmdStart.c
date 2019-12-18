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
typedef  int INT ;

/* Variables and functions */
 int /*<<< orphan*/  ConPuts (int /*<<< orphan*/ ,char*) ; 
 int EnumerateRunningServices () ; 
 int /*<<< orphan*/  MSG_START_HELP ; 
 int /*<<< orphan*/  MSG_START_SYNTAX ; 
 int /*<<< orphan*/  PrintMessageString (int) ; 
 int /*<<< orphan*/  PrintNetMessage (int /*<<< orphan*/ ) ; 
 int StartOneService (int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  StdOut ; 
 scalar_t__ _wcsicmp (int /*<<< orphan*/ *,char*) ; 

INT
cmdStart(INT argc, WCHAR **argv)
{
    INT i;

    if (argc == 2)
    {
        return EnumerateRunningServices();
    }

    for (i = 2; i < argc; i++)
    {
        if (_wcsicmp(argv[i], L"/help") == 0)
        {
            PrintMessageString(4381);
            ConPuts(StdOut, L"\n");
            PrintNetMessage(MSG_START_SYNTAX);
            PrintNetMessage(MSG_START_HELP);
            return 1;
        }
    }

    return StartOneService(argc, argv);
}