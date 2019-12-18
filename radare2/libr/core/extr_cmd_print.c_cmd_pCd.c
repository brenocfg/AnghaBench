#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut64 ;
struct TYPE_13__ {double color; } ;
struct TYPE_12__ {int blocksize; int /*<<< orphan*/  config; int /*<<< orphan*/  offset; int /*<<< orphan*/  num; } ;
typedef  TYPE_1__ RCore ;
typedef  TYPE_2__ RConsCanvas ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  r_config_get (int /*<<< orphan*/ ,char*) ; 
 double r_config_get_i (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  r_config_set (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  r_cons_canvas_free (TYPE_2__*) ; 
 int /*<<< orphan*/  r_cons_canvas_gotoxy (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 TYPE_2__* r_cons_canvas_new (int,int) ; 
 int /*<<< orphan*/  r_cons_canvas_print (TYPE_2__*) ; 
 int /*<<< orphan*/  r_cons_canvas_write (TYPE_2__*,char*) ; 
 int r_cons_get_size (int*) ; 
 int /*<<< orphan*/  r_cons_pop () ; 
 int /*<<< orphan*/  r_cons_push () ; 
 int /*<<< orphan*/  r_core_block_size (TYPE_1__*,int) ; 
 char* r_core_cmd_str (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  r_core_seek (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int r_num_math (int /*<<< orphan*/ ,char const*) ; 
 char* r_str_newf (char*,int,int) ; 
 char* strdup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cmd_pCd(RCore *core, const char *input) {
	int h, w = r_cons_get_size (&h);
	int colwidth = r_config_get_i (core->config, "hex.cols") * 2.5;
	if (colwidth < 1) {
		colwidth = 16;
	}
	int i, columns = w / colwidth;
	int rows = h - 2;
	int obsz = core->blocksize;
	int user_rows = r_num_math (core->num, input);
	bool asm_minicols = r_config_get_i (core->config, "asm.minicols");
	char *o_ao = strdup (r_config_get (core->config, "asm.offset"));
	char *o_ab = strdup (r_config_get (core->config, "asm.bytes"));
	if (asm_minicols) {
		r_config_set (core->config, "asm.offset", "false");
// r_config_set (core->config, "asm.bytes", "false");
	}
	r_config_set (core->config, "asm.bytes", "false");
	if (user_rows > 0) {
		rows = user_rows + 1;
	}
	r_cons_push ();
	RConsCanvas *c = r_cons_canvas_new (w, rows);
	ut64 osek = core->offset;
	c->color = r_config_get_i (core->config, "scr.color");
	r_core_block_size (core, rows * 32);
	for (i = 0; i < columns; i++) {
		(void) r_cons_canvas_gotoxy (c, i * (w / columns), 0);
		char *cmd = r_str_newf ("pid %d @i:%d", rows, rows * i);
		char *dis = r_core_cmd_str (core, cmd);
		r_cons_canvas_write (c, dis);
		free (cmd);
		free (dis);
	}
	r_core_block_size (core, obsz);
	r_core_seek (core, osek, 1);

	r_cons_pop ();
	r_cons_canvas_print (c);
	r_cons_canvas_free (c);
	if (asm_minicols) {
		r_config_set (core->config, "asm.offset", o_ao);
		r_config_set (core->config, "asm.bytes", o_ab);
	}
	r_config_set (core->config, "asm.bytes", o_ab);
	free (o_ao);
	free (o_ab);
}