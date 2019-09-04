#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* panels; } ;
struct TYPE_6__ {scalar_t__ layout; int /*<<< orphan*/  db; scalar_t__ n_panels; scalar_t__ curnode; } ;
typedef  TYPE_1__ RPanels ;
typedef  int /*<<< orphan*/  RPanel ;
typedef  TYPE_2__ RCore ;

/* Variables and functions */
 scalar_t__ PANEL_LAYOUT_DEFAULT_DYNAMIC ; 
 int /*<<< orphan*/  buildPanelParam (TYPE_2__*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * getPanel (TYPE_1__*,scalar_t__) ; 
 char** panels_dynamic ; 
 char** panels_static ; 
 int /*<<< orphan*/  sdb_get (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void createDefaultPanels(RCore *core) {
	RPanels *panels = core->panels;
	panels->curnode = 0;
	panels->n_panels = 0;

	int i = 0;
	if (panels->layout == PANEL_LAYOUT_DEFAULT_DYNAMIC) {
		while (panels_dynamic[i]) {
			RPanel *p = getPanel (panels, panels->n_panels);
			if (!p) {
				return;
			}
			const char *s = panels_dynamic[i++];
			buildPanelParam (core, p, s, sdb_get (panels->db, s, 0), 0);
		}
	} else {
		while (panels_static[i]) {
			RPanel *p = getPanel (panels, panels->n_panels);
			if (!p) {
				return;
			}
			const char *s = panels_static[i++];
			buildPanelParam (core, p, s, sdb_get (panels->db, s, 0), 0);
		}
	}
}