#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut64 ;
struct TYPE_10__ {int /*<<< orphan*/ * reg; } ;
struct TYPE_9__ {scalar_t__ debug; } ;
struct TYPE_8__ {int /*<<< orphan*/  print; int /*<<< orphan*/  offset; TYPE_4__* io; TYPE_5__* dbg; TYPE_1__* anal; } ;
struct TYPE_7__ {int /*<<< orphan*/ * reg; } ;
typedef  int /*<<< orphan*/  RReg ;
typedef  TYPE_2__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  r_core_seek (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  r_debug_reg_get (TYPE_5__*,char const*) ; 
 int /*<<< orphan*/  r_io_sundo_push (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_print_get_cursor (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void seek_to_register(RCore *core, const char *input, bool is_silent) {
	ut64 off;
	if (core->io->debug) {
		off = r_debug_reg_get (core->dbg, input);
		if (!is_silent) {
			r_io_sundo_push (core->io, core->offset, r_print_get_cursor (core->print));
		}
		r_core_seek (core, off, 1);
	} else {
		RReg *orig = core->dbg->reg;
		core->dbg->reg = core->anal->reg;
		off = r_debug_reg_get (core->dbg, input);
		core->dbg->reg = orig;
		if (!is_silent) {
			r_io_sundo_push (core->io, core->offset, r_print_get_cursor (core->print));
		}
		r_core_seek (core, off, 1);
	}
}