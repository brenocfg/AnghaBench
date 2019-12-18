#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  csh ;
typedef  int /*<<< orphan*/  cs_insn ;
struct TYPE_7__ {int /*<<< orphan*/  index; int /*<<< orphan*/  base; } ;
struct TYPE_8__ {int type; TYPE_1__ mem; int /*<<< orphan*/  reg; } ;
typedef  TYPE_2__ cs_arm64_op ;
struct TYPE_9__ {char* name; } ;
typedef  TYPE_3__ RRegItem ;

/* Variables and functions */
#define  ARM64_OP_MEM 129 
#define  ARM64_OP_REG 128 
 TYPE_2__ INSOP64 (int) ; 
 scalar_t__ cs_reg_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_valid64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int parse_reg64_name(RRegItem *reg_base, RRegItem *reg_delta, csh handle, cs_insn *insn, int reg_num) {
	cs_arm64_op armop = INSOP64 (reg_num);
	switch (armop.type) {
	case ARM64_OP_REG:
		reg_base->name = (char *)cs_reg_name (handle, armop.reg);
		break;
	case ARM64_OP_MEM:
		if (is_valid64 (armop.mem.base) && is_valid64 (armop.mem.index)) {
			reg_base->name = (char *)cs_reg_name (handle, armop.mem.base);
			reg_delta->name = (char *)cs_reg_name (handle, armop.mem.index);
		} else if (is_valid64 (armop.mem.base)) {
			reg_base->name = (char *)cs_reg_name (handle, armop.mem.base);
		} else if (is_valid64 (armop.mem.index)) {
			reg_base->name = (char *)cs_reg_name (handle, armop.mem.index);
		}
		break;
	default:
		break;
	}
	return 0;
}