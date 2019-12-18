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
struct TYPE_5__ {int /*<<< orphan*/ * tabs; int /*<<< orphan*/  tab; } ;
struct TYPE_6__ {TYPE_1__ visual; } ;
typedef  int /*<<< orphan*/  RCoreVisualTab ;
typedef  TYPE_2__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  r_list_delete_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_list_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * r_list_get_n (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int r_list_length (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  visual_tabset (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void visual_closetab (RCore *core) {
	if (!core->visual.tabs) {
		return;
	}
	RCoreVisualTab *tab = r_list_get_n (core->visual.tabs, core->visual.tab);
	if (tab) {
		r_list_delete_data (core->visual.tabs, tab);
		const int tabsCount = r_list_length (core->visual.tabs);
		if (tabsCount > 0) {
			if (core->visual.tab > 0) {
				core->visual.tab--;
			}
			RCoreVisualTab *tab = r_list_get_n (core->visual.tabs, core->visual.tab);
			if (tab) {
				visual_tabset(core, tab);
			}
		} else {
			r_list_free (core->visual.tabs);
			core->visual.tabs = NULL;
		}
	}
}