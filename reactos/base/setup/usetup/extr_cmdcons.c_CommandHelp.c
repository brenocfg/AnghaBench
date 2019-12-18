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
struct TYPE_3__ {int /*<<< orphan*/  (* help ) () ;int /*<<< orphan*/ * name; } ;
typedef  int /*<<< orphan*/  PCONSOLE_STATE ;
typedef  int /*<<< orphan*/ * LPSTR ;
typedef  TYPE_1__* LPCOMMAND ;
typedef  int /*<<< orphan*/  INT ;

/* Variables and functions */
 int /*<<< orphan*/  CONSOLE_ConOutPrintf (char*) ; 
 TYPE_1__* Commands ; 
 int /*<<< orphan*/  DPRINT1 (char*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HelpHelp () ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  stricmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ strlen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 () ; 

__attribute__((used)) static
INT
CommandHelp(
    PCONSOLE_STATE State,
    LPSTR param)
{
    LPCOMMAND cmdptr;

    DPRINT1("param: %p %u '%s'\n", param, strlen(param), param);

    if (!strcmp(param, "/?"))
    {
        HelpHelp();
        return 0;
    }

    if (param != NULL && strlen(param) > 0)
    {
        for (cmdptr = Commands; cmdptr->name != NULL; cmdptr++)
        {
            if (!stricmp(param, cmdptr->name))
            {
                if (cmdptr->help != NULL)
                {
                    cmdptr->help();
                    return 0;
                }
            }
        }
    }

    CONSOLE_ConOutPrintf("CLS\n");
    CONSOLE_ConOutPrintf("DUMPSECTOR\n");
    CONSOLE_ConOutPrintf("EXIT\n");
    CONSOLE_ConOutPrintf("HELP\n");
    CONSOLE_ConOutPrintf("\n");

    return 0;
}