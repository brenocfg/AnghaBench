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
struct TYPE_6__ {int tab; int /*<<< orphan*/  tabs; } ;
struct TYPE_7__ {TYPE_1__ visual; } ;
typedef  int /*<<< orphan*/  RListFree ;
typedef  int /*<<< orphan*/  RCoreVisualTab ;
typedef  TYPE_2__ RCore ;

/* Variables and functions */
 scalar_t__ r_core_visual_tab_free ; 
 int /*<<< orphan*/ * r_core_visual_tab_new (TYPE_2__*) ; 
 int /*<<< orphan*/  r_list_append (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_list_newf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  visual_tabset (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static RCoreVisualTab *visual_newtab (RCore *core) {
	if (!core->visual.tabs) {
		core->visual.tabs = r_list_newf ((RListFree)r_core_visual_tab_free);
		if (!core->visual.tabs) {
			return NULL;
		}
		core->visual.tab = -1;
		visual_newtab (core);
	}
	core->visual.tab++;
	RCoreVisualTab *tab = r_core_visual_tab_new (core);
	if (tab) {
		r_list_append (core->visual.tabs, tab);
		visual_tabset (core, tab);
	}
	return tab;
}