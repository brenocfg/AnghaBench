#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int stackFd; int /*<<< orphan*/  _tabsbuf; int /*<<< orphan*/  sl; int /*<<< orphan*/  osl; int /*<<< orphan*/  opstr; int /*<<< orphan*/  prev_line_col; int /*<<< orphan*/  refline2; int /*<<< orphan*/  refline; int /*<<< orphan*/  line_col; int /*<<< orphan*/  line; int /*<<< orphan*/  comment; int /*<<< orphan*/  ssa; int /*<<< orphan*/  hint; int /*<<< orphan*/  analop; int /*<<< orphan*/  asmop; TYPE_1__* core; scalar_t__ show_emu_stack; } ;
struct TYPE_7__ {int /*<<< orphan*/  io; } ;
typedef  TYPE_2__ RDisasmState ;

/* Variables and functions */
 int /*<<< orphan*/  R_FREE (TYPE_2__*) ; 
 int /*<<< orphan*/  ds_print_esil_anal_fini (TYPE_2__*) ; 
 int /*<<< orphan*/  ds_reflines_fini (TYPE_2__*) ; 
 int /*<<< orphan*/  eprintf (char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_anal_hint_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_anal_op_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_asm_op_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_io_fd_close (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sdb_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ds_free(RDisasmState *ds) {
	if (!ds) {
		return;
	}
	if (ds->show_emu_stack) {
		// TODO: destroy fake stack in here
		eprintf ("Free fake stack\n");
		if (ds->stackFd != -1) {
			r_io_fd_close (ds->core->io, ds->stackFd);
		}
	}
	r_asm_op_fini (&ds->asmop);
	r_anal_op_fini (&ds->analop);
	r_anal_hint_free (ds->hint);
	ds_print_esil_anal_fini (ds);
	ds_reflines_fini (ds);
	ds_print_esil_anal_fini (ds);
	sdb_free (ds->ssa);
	free (ds->comment);
	free (ds->line);
	free (ds->line_col);
	free (ds->refline);
	free (ds->refline2);
	free (ds->prev_line_col);
	free (ds->opstr);
	free (ds->osl);
	free (ds->sl);
	free (ds->_tabsbuf);
	R_FREE (ds);
}