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
struct TYPE_3__ {struct TYPE_3__* prev; int /*<<< orphan*/  szPath; } ;
typedef  int /*<<< orphan*/  LPTSTR ;
typedef  TYPE_1__* LPDIRENTRY ;
typedef  int /*<<< orphan*/  INT ;

/* Variables and functions */
 int /*<<< orphan*/  ConOutPuts (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ConOutResPuts (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STRING_DIRSTACK_HELP3 ; 
 int /*<<< orphan*/  STRING_DIRSTACK_HELP4 ; 
 int /*<<< orphan*/  _T (char*) ; 
 int /*<<< orphan*/  _tcsncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* lpStackBottom ; 
 scalar_t__ nErrorLevel ; 

INT CommandDirs (LPTSTR rest)
{
    LPDIRENTRY lpDir;

    if (!_tcsncmp(rest, _T("/?"), 2))
    {
        ConOutResPuts(STRING_DIRSTACK_HELP3);
        return 0;
    }

    nErrorLevel = 0;

    lpDir = lpStackBottom;

    if (lpDir == NULL)
    {
        ConOutResPuts(STRING_DIRSTACK_HELP4);
        return 0;
    }

    while (lpDir != NULL)
    {
        ConOutPuts(lpDir->szPath);
        lpDir = lpDir->prev;
    }

    return 0;
}