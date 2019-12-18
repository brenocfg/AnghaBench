#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* panels; } ;
struct TYPE_5__ {scalar_t__ mode; scalar_t__ prevMode; } ;
typedef  TYPE_1__ RPanels ;
typedef  TYPE_2__ RCore ;

/* Variables and functions */
 scalar_t__ PANEL_MODE_DEFAULT ; 
 scalar_t__ PANEL_MODE_WINDOW ; 
 int /*<<< orphan*/  __set_mode (TYPE_2__*,scalar_t__) ; 

void __toggle_window_mode(RCore *core) {
	RPanels *panels = core->panels;
	if (panels->mode != PANEL_MODE_WINDOW) {
		panels->prevMode = panels->mode;
		__set_mode (core, PANEL_MODE_WINDOW);
	} else {
		__set_mode (core, panels->prevMode);
		panels->prevMode = PANEL_MODE_DEFAULT;
	}
}