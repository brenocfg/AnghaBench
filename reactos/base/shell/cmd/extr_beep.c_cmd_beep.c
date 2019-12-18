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
typedef  int /*<<< orphan*/  LPTSTR ;
typedef  int INT ;

/* Variables and functions */
 int /*<<< orphan*/  ConOutResPaging (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ConRingBell (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ConStreamGetOSHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STRING_BEEP_HELP ; 
 int /*<<< orphan*/  StdOut ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _T (char*) ; 
 scalar_t__ _tcsncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * bc ; 

INT cmd_beep(LPTSTR param)
{
    if (_tcsncmp(param, _T("/?"), 2) == 0)
    {
        ConOutResPaging(TRUE, STRING_BEEP_HELP);
        return 0;
    }

#if 0
    /* check if run in batch mode */
    if (bc == NULL)
        return 1;
#endif

    ConRingBell(ConStreamGetOSHandle(StdOut));
    return 0;
}