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
struct TYPE_3__ {int /*<<< orphan*/  bExit; } ;
typedef  TYPE_1__* PCONSOLE_STATE ;
typedef  int /*<<< orphan*/  LPSTR ;
typedef  int /*<<< orphan*/  INT ;

/* Variables and functions */
 int /*<<< orphan*/  HelpExit () ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static
INT
CommandExit(
    PCONSOLE_STATE State,
    LPSTR param)
{
    if (!strcmp(param, "/?"))
    {
        HelpExit();
        return 0;
    }

    State->bExit = TRUE;

    return 0;
}