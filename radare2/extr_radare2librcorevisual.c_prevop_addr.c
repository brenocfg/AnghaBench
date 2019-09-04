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
typedef  int /*<<< orphan*/  ut8 ;
typedef  scalar_t__ ut64 ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_8__ {int size; } ;
struct TYPE_7__ {int /*<<< orphan*/  anal; int /*<<< orphan*/  io; int /*<<< orphan*/  config; } ;
typedef  TYPE_1__ RCore ;
typedef  TYPE_2__ RAnalOp ;
typedef  int /*<<< orphan*/  RAnalBlock ;

/* Variables and functions */
 int OPDELTA ; 
 int /*<<< orphan*/  R_ANAL_ARCHINFO_MAX_OP_SIZE ; 
 int /*<<< orphan*/  R_ANAL_ARCHINFO_MIN_OP_SIZE ; 
 int /*<<< orphan*/  R_ANAL_OP_MASK_BASIC ; 
 int R_MIDFLAGS_REALIGN ; 
 scalar_t__ UT64_MAX ; 
 int r_anal_archinfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * r_anal_bb_from_offset (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ r_anal_bb_opaddr_at (int /*<<< orphan*/ *,scalar_t__) ; 
 int r_anal_op (int /*<<< orphan*/ ,TYPE_2__*,scalar_t__,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_anal_op_fini (TYPE_2__*) ; 
 int r_config_get_i (int /*<<< orphan*/ ,char*) ; 
 int r_core_flag_in_middle (TYPE_1__*,scalar_t__,int,int*) ; 
 int /*<<< orphan*/  r_io_read_at (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static ut64 prevop_addr(RCore *core, ut64 addr) {
	ut8 buf[OPDELTA * 2];
	ut64 target, base;
	RAnalBlock *bb;
	RAnalOp op;
	int len, ret, i;
	int minop = r_anal_archinfo (core->anal, R_ANAL_ARCHINFO_MIN_OP_SIZE);
	int maxop = r_anal_archinfo (core->anal, R_ANAL_ARCHINFO_MAX_OP_SIZE);

	if (minop == maxop) {
		if (minop == -1) {
			return addr - 4;
		}
		return addr - minop;
	}

	// let's see if we can use anal info to get the previous instruction
	// TODO: look in the current basicblock, then in the current function
	// and search in all functions only as a last chance, to try to speed
	// up the process.
	bb = r_anal_bb_from_offset (core->anal, addr - minop);
	if (bb) {
		ut64 res = r_anal_bb_opaddr_at (bb, addr - minop);
		if (res != UT64_MAX) {
			return res;
		}
	}
	// if we anal info didn't help then fallback to the dumb solution.
	int midflags = r_config_get_i (core->config, "asm.flags.middle");
	target = addr;
	base = target > OPDELTA ? target - OPDELTA : 0;
	r_io_read_at (core->io, base, buf, sizeof (buf));
	for (i = 0; i < sizeof (buf); i++) {
		ret = r_anal_op (core->anal, &op, base + i,
			buf + i, sizeof (buf) - i, R_ANAL_OP_MASK_BASIC);
		if (ret) {
			len = op.size;
			if (len < 1) {
				len = 1;
			}
			r_anal_op_fini (&op); // XXX
			if (midflags >= R_MIDFLAGS_REALIGN) {
				int skip_bytes = r_core_flag_in_middle (core, base + i, len, &midflags);
				if (skip_bytes && base + i + skip_bytes < target) {
					i += skip_bytes - 1;
					continue;
				}
			}
		} else {
			len = 1;
		}
		if (target <= base + i + len) {
			return base + i;
		}
		i += len - 1;
	}
	return target > 4 ? target - 4 : 0;
}