#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_1__* panelsMenu; } ;
struct TYPE_10__ {TYPE_3__* panels; } ;
struct TYPE_9__ {int depth; } ;
typedef  TYPE_2__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  PANEL_MODE_DEFAULT ; 
 int /*<<< orphan*/  createDefaultPanels (TYPE_2__*) ; 
 int /*<<< orphan*/  initPanels (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  panels_layout (TYPE_3__*) ; 
 int /*<<< orphan*/  setMode (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setRefreshAll (TYPE_3__*,int) ; 

__attribute__((used)) static int loadLayoutDefaultCb(void *user) {
	RCore *core = (RCore *)user;
	initPanels (core, core->panels);
	createDefaultPanels (core);
	panels_layout (core->panels);
	setRefreshAll (core->panels, false);
	core->panels->panelsMenu->depth = 1;
	setMode (core->panels, PANEL_MODE_DEFAULT);
	return 0;
}