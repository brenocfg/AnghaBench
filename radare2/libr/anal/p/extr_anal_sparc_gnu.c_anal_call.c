#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int ut64 ;
typedef  int /*<<< orphan*/  ut32 ;
typedef  int st64 ;
struct TYPE_3__ {int jump; int fail; int /*<<< orphan*/  dst; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ RAnalOp ;

/* Variables and functions */
 int /*<<< orphan*/  R_ANAL_OP_TYPE_CALL ; 
 int get_immed_sgnext (int /*<<< orphan*/  const,int) ; 
 int /*<<< orphan*/  value_fill_addr_pc_disp (int const,int const) ; 

__attribute__((used)) static void anal_call(RAnalOp *op, const ut32 insn, const ut64 addr) {
	const st64 disp = (get_immed_sgnext(insn, 29) * 4);
	op->type = R_ANAL_OP_TYPE_CALL;
	op->dst = value_fill_addr_pc_disp(addr, disp);
	op->jump = addr + disp;
	op->fail = addr + 4;
}