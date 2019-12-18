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
typedef  int /*<<< orphan*/  PCONSOLE_STATE ;
typedef  int /*<<< orphan*/  LPSTR ;
typedef  int /*<<< orphan*/  INT ;

/* Variables and functions */
 int /*<<< orphan*/  CONSOLE_ClearScreen () ; 
 int /*<<< orphan*/  CONSOLE_SetCursorXY (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HelpCls () ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static
INT
CommandCls(
    PCONSOLE_STATE State,
    LPSTR param)
{
    if (!strcmp(param, "/?"))
    {
        HelpCls();
        return 0;
    }

    CONSOLE_ClearScreen();
    CONSOLE_SetCursorXY(0, 0);

    return 0;
}