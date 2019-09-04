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
struct TYPE_3__ {int /*<<< orphan*/  help; scalar_t__ name; } ;
typedef  TYPE_1__* PCOMMAND ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  int INT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ConResPuts (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StdOut ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ _wcsicmp (int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_1__* cmds ; 
 int /*<<< orphan*/  help_cmdlist () ; 

BOOL help_main(INT argc, LPWSTR *argv)
{
    PCOMMAND cmdptr;

    if (argc == 1)
    {
        help_cmdlist();
        return TRUE;
    }

    /* Scan internal command table */
    for (cmdptr = cmds; cmdptr->name; cmdptr++)
    {
        if (_wcsicmp(argv[1], cmdptr->name) == 0)
        {
            ConResPuts(StdOut, cmdptr->help);
            return TRUE;
        }
    }

    help_cmdlist();

    return TRUE;
}