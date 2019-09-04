#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  config; TYPE_1__* panels; } ;
struct TYPE_8__ {int /*<<< orphan*/ * can; } ;
typedef  TYPE_1__ RPanels ;
typedef  TYPE_2__ RCore ;

/* Variables and functions */
 scalar_t__ checkFunc (TYPE_2__*) ; 
 int /*<<< orphan*/ * createNewCanvas (TYPE_2__*,int,int) ; 
 int r_config_get_i (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  r_config_set_i (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  r_cons_canvas_free (int /*<<< orphan*/ *) ; 
 int r_cons_get_size (int*) ; 
 int /*<<< orphan*/  r_core_visual_graph (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  setRefreshAll (TYPE_1__*,int) ; 

__attribute__((used)) static void callVisualGraph(RCore *core) {
	if (checkFunc (core)) {
		RPanels *panels = core->panels;

		r_cons_canvas_free (panels->can);
		panels->can = NULL;

		int ocolor = r_config_get_i (core->config, "scr.color");

		r_core_visual_graph (core, NULL, NULL, true);
		r_config_set_i (core->config, "scr.color", ocolor);

		int h, w = r_cons_get_size (&h);
		panels->can = createNewCanvas (core, w, h);
		setRefreshAll (panels, false);
	}
}