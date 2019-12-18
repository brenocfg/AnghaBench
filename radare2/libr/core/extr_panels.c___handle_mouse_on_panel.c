#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ut64 ;
struct TYPE_19__ {int /*<<< orphan*/  num; int /*<<< orphan*/  config; int /*<<< orphan*/ * panels; } ;
struct TYPE_18__ {TYPE_2__* view; } ;
struct TYPE_16__ {int x; } ;
struct TYPE_17__ {TYPE_1__ pos; } ;
typedef  int /*<<< orphan*/  RPanels ;
typedef  TYPE_3__ RPanel ;
typedef  TYPE_4__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  PANEL_CMD_DISASSEMBLY ; 
 int /*<<< orphan*/  PANEL_CMD_FUNCTION ; 
 scalar_t__ __check_if_addr (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ __check_panel_type (TYPE_3__*,int /*<<< orphan*/ ) ; 
 TYPE_3__* __get_panel (int /*<<< orphan*/ *,int const) ; 
 int __get_panel_idx_in_pos (TYPE_4__*,int,int) ; 
 int /*<<< orphan*/  __seek_all (TYPE_4__*,scalar_t__) ; 
 int /*<<< orphan*/  __set_addr_by_type (TYPE_4__*,int /*<<< orphan*/ ,scalar_t__ const) ; 
 int /*<<< orphan*/  __set_curnode (TYPE_4__*,int const) ; 
 int /*<<< orphan*/  __set_refresh_all (TYPE_4__*,int,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* get_word_from_canvas (TYPE_4__*,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  r_config_set (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  r_cons_get_size (int*) ; 
 int /*<<< orphan*/  r_core_seek (TYPE_4__*,scalar_t__ const,int) ; 
 void* r_num_math (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static bool __handle_mouse_on_panel(RCore *core, RPanel *panel, int x, int y, int *key) {
	RPanels *panels = core->panels;
	int h;
	(void)r_cons_get_size (&h);
	const int idx = __get_panel_idx_in_pos (core, x, y);
	char *word = get_word_from_canvas (core, panels, x, y);
	if (idx == -1) {
		return false;
	}
	__set_curnode (core, idx);
	__set_refresh_all (core, true, true);
	RPanel *ppos = __get_panel(panels, idx);
	if (word) {
		if (__check_panel_type (panel, PANEL_CMD_FUNCTION) &&
				__check_if_addr (word, strlen (word))) {
			const ut64 addr = r_num_math (core->num, word);
			r_core_seek (core, addr, 1);
			__set_addr_by_type (core, PANEL_CMD_DISASSEMBLY, addr);
		}
		r_config_set (core->config, "scr.highlight", word);
#if 1
// TODO implement sync
		{
			ut64 addr = r_num_math (core->num, word);
			if (addr > 0) {
		//		__set_panel_addr (core, cur, addr);
				__seek_all (core, addr);
			}
		}
#endif
		free (word);
	}
	if (x >= ppos->view->pos.x && x < ppos->view->pos.x + 4) {
		*key = 'c';
		return false;
	}
	return true;
}