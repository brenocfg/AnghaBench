#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut64 ;
struct TYPE_14__ {int /*<<< orphan*/  offset; } ;
struct TYPE_13__ {TYPE_1__* model; } ;
struct TYPE_12__ {char* cmd; int /*<<< orphan*/  rotate; int /*<<< orphan*/  addr; int /*<<< orphan*/  cache; } ;
typedef  TYPE_2__ RPanel ;
typedef  TYPE_3__ RCore ;

/* Variables and functions */
 size_t COUNT (char**) ; 
 size_t R_ABS (int /*<<< orphan*/ ) ; 
 char* __find_cmd_str_cache (TYPE_3__*,TYPE_2__*) ; 
 char* __handle_cmd_str_cache (TYPE_3__*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  __update_panel_contents (TYPE_3__*,TYPE_2__*,char*) ; 
 char** hexdump_rotate ; 
 int /*<<< orphan*/  r_core_block_read (TYPE_3__*) ; 
 int /*<<< orphan*/  r_core_seek (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 char* r_str_append (char*,char const*) ; 
 char* r_str_newf (char*,char*) ; 
 int r_str_split (char*,char) ; 
 char* r_str_word_get0 (char*,int) ; 

void __print_hexdump_cb(void *user, void *p) {
	RCore *core = (RCore *)user;
	RPanel *panel = (RPanel *)p;
	char *cmdstr = __find_cmd_str_cache (core, panel);
	if (!cmdstr) {
		ut64 o_offset = core->offset;
		if (!panel->model->cache) {
			core->offset = panel->model->addr;
			r_core_seek (core, core->offset, 1);
			r_core_block_read (core);
		}
		char *base = hexdump_rotate[R_ABS(panel->model->rotate) % COUNT (hexdump_rotate)];
		char *cmd = r_str_newf ("%s ", base);
		int n = r_str_split (panel->model->cmd, ' ');
		int i;
		for (i = 0; i < n; i++) {
			const char *s = r_str_word_get0 (panel->model->cmd, i);
			if (!i) {
				continue;
			}
			cmd = r_str_append (cmd, s);
		}
		panel->model->cmd = cmd;
		cmdstr = __handle_cmd_str_cache (core, panel, false);
		core->offset = o_offset;
	}
	__update_panel_contents (core, panel, cmdstr);
}