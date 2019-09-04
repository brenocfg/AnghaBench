#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__* panelsMenu; scalar_t__ curnode; } ;
struct TYPE_8__ {TYPE_3__* panels; } ;
struct TYPE_7__ {int depth; } ;
typedef  TYPE_2__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  PANEL_MODE_DEFAULT ; 
 int /*<<< orphan*/  createDefaultPanels (TYPE_2__*) ; 
 int /*<<< orphan*/  loadSavedPanelsLayout (TYPE_2__*) ; 
 int /*<<< orphan*/  panels_layout (TYPE_3__*) ; 
 int /*<<< orphan*/  setMode (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int loadLayoutSavedCb(void *user) {
	RCore *core = (RCore *)user;
	if (!loadSavedPanelsLayout (core)) {
		createDefaultPanels (core);
		panels_layout (core->panels);
	}
	core->panels->curnode = 0;
	core->panels->panelsMenu->depth = 1;
	setMode (core->panels, PANEL_MODE_DEFAULT);
	return 0;
}