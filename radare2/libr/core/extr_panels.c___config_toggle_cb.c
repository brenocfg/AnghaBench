#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int /*<<< orphan*/  config; TYPE_1__* panels; } ;
struct TYPE_17__ {TYPE_3__* view; TYPE_2__* model; } ;
struct TYPE_16__ {int depth; int /*<<< orphan*/  n_refresh; TYPE_6__** refreshPanels; TYPE_4__** history; } ;
struct TYPE_15__ {size_t selectedIndex; int /*<<< orphan*/  name; TYPE_6__* p; struct TYPE_15__** sub; } ;
struct TYPE_14__ {int refresh; } ;
struct TYPE_13__ {int /*<<< orphan*/  title; } ;
struct TYPE_12__ {TYPE_5__* panels_menu; } ;
typedef  int /*<<< orphan*/  RStrBuf ;
typedef  TYPE_4__ RPanelsMenuItem ;
typedef  TYPE_5__ RPanelsMenu ;
typedef  TYPE_6__ RPanel ;
typedef  TYPE_7__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  __draw_menu (TYPE_7__*,TYPE_4__*) ; 
 int /*<<< orphan*/  __init_menu_disasm_asm_settings_layout ; 
 int /*<<< orphan*/  __init_menu_screen_settings_layout ; 
 int /*<<< orphan*/  __set_refresh_all (TYPE_7__*,int,int) ; 
 int /*<<< orphan*/  __update_menu (TYPE_7__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_config_toggle (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_str_split (int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  r_strbuf_drain (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_strbuf_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_strbuf_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * r_strbuf_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

int __config_toggle_cb(void *user) {
	RCore *core = (RCore *)user;
	RPanelsMenu *menu = core->panels->panels_menu;
	RPanelsMenuItem *parent = menu->history[menu->depth - 1];
	RPanelsMenuItem *child = parent->sub[parent->selectedIndex];
	RStrBuf *tmp = r_strbuf_new (child->name);
	(void)r_str_split (r_strbuf_get (tmp), ':');
	r_config_toggle (core->config, r_strbuf_get (tmp));
	r_strbuf_free (tmp);
	__set_refresh_all (core, false, false);
	free (parent->p->model->title);
	parent->p->model->title = r_strbuf_drain (__draw_menu (core, parent));
	int i;
	for (i = 1; i < menu->depth; i++) {
		RPanel *p = menu->history[i]->p;
		p->view->refresh = true;
		menu->refreshPanels[menu->n_refresh++] = p;
	}
	if (!strcmp (parent->name, "asm")) {
		__update_menu(core, "Settings.Disassembly.asm", __init_menu_disasm_asm_settings_layout);
	}
	if (!strcmp (parent->name, "Screen")) {
		__update_menu(core, "Settings.Screen", __init_menu_screen_settings_layout);
	}
	return 0;
}