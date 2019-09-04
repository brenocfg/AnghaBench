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

/* Variables and functions */
 int /*<<< orphan*/  True ; 
 int /*<<< orphan*/  curMenuName ; 
 char* fixup (char*) ; 
 int /*<<< orphan*/  strcat (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  updatePriority (int /*<<< orphan*/ ) ; 

void
workshop_submenu_begin(
	char		*label)
{
#ifdef WSDEBUG_TRACE
    if (ws_debug  && ws_dlevel & WS_TRACE
	    && strncmp(curMenuName, "ToolBar", 7) != 0)
	wstrace("workshop_submenu_begin(%s)\n", label);
#endif

    strcat(curMenuName, ".");
    strcat(curMenuName, fixup(label));

    updatePriority(True);
}