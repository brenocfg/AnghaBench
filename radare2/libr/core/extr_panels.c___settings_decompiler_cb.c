#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  config; TYPE_1__* panels; TYPE_2__* panels_root; } ;
struct TYPE_11__ {int depth; TYPE_3__** history; } ;
struct TYPE_10__ {size_t selectedIndex; char* name; struct TYPE_10__** sub; } ;
struct TYPE_9__ {int /*<<< orphan*/ * cur_pdc_cache; int /*<<< orphan*/  pdc_caches; } ;
struct TYPE_8__ {TYPE_4__* panels_menu; } ;
typedef  int /*<<< orphan*/  Sdb ;
typedef  TYPE_2__ RPanelsRoot ;
typedef  TYPE_3__ RPanelsMenuItem ;
typedef  TYPE_4__ RPanelsMenu ;
typedef  TYPE_5__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  PANEL_MODE_DEFAULT ; 
 int /*<<< orphan*/  __set_mode (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __set_refresh_all (TYPE_5__*,int,int) ; 
 char* r_config_get (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  r_config_set (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/ * sdb_new0 () ; 
 int /*<<< orphan*/ * sdb_ptr_get (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdb_ptr_set (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (char const*,char const*) ; 

int __settings_decompiler_cb(void *user) {
	RCore *core = (RCore *)user;
	RPanelsRoot *root = core->panels_root;
	RPanelsMenu *menu = core->panels->panels_menu;
	RPanelsMenuItem *parent = menu->history[menu->depth - 1];
	RPanelsMenuItem *child = parent->sub[parent->selectedIndex];
	const char *pdc_next = child->name;
	const char *pdc_now = r_config_get (core->config, "cmd.pdc");
	if (!strcmp (pdc_next, pdc_now)) {
		return 0;
	}
	r_config_set (core->config, "cmd.pdc", pdc_next);
	root->cur_pdc_cache = sdb_ptr_get (root->pdc_caches, pdc_next, 0);
	if (!root->cur_pdc_cache) {
		Sdb *sdb = sdb_new0 ();
		sdb_ptr_set (root->pdc_caches, pdc_next, sdb, 0);
		root->cur_pdc_cache = sdb;
	}
	__set_refresh_all (core, false, false);
	__set_mode (core, PANEL_MODE_DEFAULT);
	return 0;
}