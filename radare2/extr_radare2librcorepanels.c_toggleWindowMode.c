#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ mode; scalar_t__ prevMode; } ;
typedef  TYPE_1__ RPanels ;

/* Variables and functions */
 scalar_t__ PANEL_MODE_DEFAULT ; 
 scalar_t__ PANEL_MODE_WINDOW ; 
 int /*<<< orphan*/  setMode (TYPE_1__*,scalar_t__) ; 

__attribute__((used)) static void toggleWindowMode(RPanels *panels) {
	if (panels->mode != PANEL_MODE_WINDOW) {
		panels->prevMode = panels->mode;
		setMode (panels, PANEL_MODE_WINDOW);
	} else {
		setMode (panels, panels->prevMode);
		panels->prevMode = PANEL_MODE_DEFAULT;
	}
}