#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ mode; scalar_t__ prevMode; scalar_t__ fun; } ;
typedef  TYPE_1__ RPanels ;
typedef  int /*<<< orphan*/  RPanel ;

/* Variables and functions */
 scalar_t__ PANEL_FUN_SAKURA ; 
 scalar_t__ PANEL_FUN_SNOW ; 
 scalar_t__ PANEL_MODE_DEFAULT ; 
 scalar_t__ PANEL_MODE_ZOOM ; 
 int /*<<< orphan*/ * getCurPanel (TYPE_1__*) ; 
 int /*<<< orphan*/  maximizePanelSize (TYPE_1__*) ; 
 int /*<<< orphan*/  resetSnow (TYPE_1__*) ; 
 int /*<<< orphan*/  restorePanelPos (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  savePanelPos (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setMode (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  setRefreshAll (TYPE_1__*,int) ; 

__attribute__((used)) static void toggleZoomMode(RPanels *panels) {
	RPanel *cur = getCurPanel (panels);
	if (panels->mode != PANEL_MODE_ZOOM) {
		panels->prevMode = panels->mode;
		setMode (panels, PANEL_MODE_ZOOM);
		savePanelPos (cur);
		maximizePanelSize (panels);
	} else {
		setMode (panels, panels->prevMode);
		panels->prevMode = PANEL_MODE_DEFAULT;
		restorePanelPos (cur);
		setRefreshAll (panels, false);
		if (panels->fun == PANEL_FUN_SNOW || panels->fun == PANEL_FUN_SAKURA) {
			resetSnow (panels);
		}
	}
}