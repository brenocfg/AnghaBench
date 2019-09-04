#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* name; int /*<<< orphan*/  (* func ) (int,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_1__* PCOMMAND ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_1__* cmds ; 
 int /*<<< orphan*/  help_cmdlist () ; 
 int /*<<< orphan*/  stub1 (int,int /*<<< orphan*/ *) ; 
 scalar_t__ wcsicmp (int /*<<< orphan*/ ,char*) ; 

BOOL
InterpretCmd(int argc, LPWSTR *argv)
{
    PCOMMAND cmdptr;

    /* If no args provided */
    if (argc < 1)
        return TRUE;

    /* First, determine if the user wants to exit
       or to use a comment */
    if(wcsicmp(argv[0], L"exit") == 0)
        return FALSE;

    if(wcsicmp(argv[0], L"rem") == 0)
        return TRUE;

    /* Scan internal command table */
    for (cmdptr = cmds; cmdptr->name; cmdptr++)
    {
        if (wcsicmp(argv[0], cmdptr->name) == 0)
            return cmdptr->func(argc, argv);
    }

    help_cmdlist();

    return TRUE;
}