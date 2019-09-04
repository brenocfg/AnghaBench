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
struct TYPE_3__ {int /*<<< orphan*/  const* Desc; int /*<<< orphan*/  const* Command; } ;
typedef  int /*<<< orphan*/  TCHAR ;
typedef  TYPE_1__ HandlerItem ;

/* Variables and functions */
 int /*<<< orphan*/  _T (char*) ; 
 int /*<<< orphan*/  _ftprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,...) ; 
 int /*<<< orphan*/  stderr ; 

void PrintDefaultUsage(const TCHAR * Command,
                       const TCHAR * SubCommand,
                       HandlerItem * HandlersList,
                       int HandlerListCount)
{
    int i;

    /* If we were given a command, print it's not supported */
    if (SubCommand != NULL)
    {
        _ftprintf(stderr, _T("Unhandled%scommand: %s\n"), Command, SubCommand);
    }

    /* And dump any available command */
    _ftprintf(stderr, _T("---- Handled%scommands ----\n\n"), Command);
    for (i = 0; i < HandlerListCount; ++i)
    {
        _ftprintf(stderr, _T("%s\t%s\n"), HandlersList[i].Command, HandlersList[i].Desc);
    }
}