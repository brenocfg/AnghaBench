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
typedef  int /*<<< orphan*/  INT ;

/* Variables and functions */
 int /*<<< orphan*/  ConClearScreen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ConOutResPaging (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STRING_CLS_HELP ; 
 int /*<<< orphan*/  StdOutScreen ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _T (char*) ; 
 int /*<<< orphan*/  _tcsncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

INT cmd_cls(LPTSTR param)
{
    if (!_tcsncmp(param, _T("/?"), 2))
    {
        ConOutResPaging(TRUE, STRING_CLS_HELP);
        return 0;
    }

    ConClearScreen(&StdOutScreen);
    return 0;
}