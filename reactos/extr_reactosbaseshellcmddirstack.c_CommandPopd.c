#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  szPath; } ;
typedef  int /*<<< orphan*/  LPTSTR ;
typedef  int INT ;

/* Variables and functions */
 int /*<<< orphan*/  ConOutResPuts (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PopDirectory () ; 
 int /*<<< orphan*/  STRING_DIRSTACK_HELP2 ; 
 int /*<<< orphan*/  _T (char*) ; 
 scalar_t__ _tchdir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _tcsncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* lpStackTop ; 
 scalar_t__ nStackDepth ; 

INT CommandPopd (LPTSTR rest)
{
    INT ret = 0;
    if (!_tcsncmp(rest, _T("/?"), 2))
    {
        ConOutResPuts(STRING_DIRSTACK_HELP2);
        return 0;
    }

    if (nStackDepth == 0)
        return 1;

    ret = _tchdir(lpStackTop->szPath) != 0;
    PopDirectory ();

    return ret;
}