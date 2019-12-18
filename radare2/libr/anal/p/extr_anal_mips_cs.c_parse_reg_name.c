#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  csh ;
typedef  int /*<<< orphan*/  cs_insn ;
struct TYPE_5__ {int /*<<< orphan*/  base; } ;
struct TYPE_7__ {int type; TYPE_1__ mem; int /*<<< orphan*/  reg; } ;
struct TYPE_6__ {char* name; } ;
typedef  TYPE_2__ RRegItem ;

/* Variables and functions */
#define  MIPS_OP_MEM 129 
#define  MIPS_OP_REG 128 
 int /*<<< orphan*/  MIPS_REG_INVALID ; 
 TYPE_4__ OPERAND (int) ; 
 scalar_t__ cs_reg_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int parse_reg_name(RRegItem *reg, csh handle, cs_insn *insn, int reg_num) {
	if (!reg) {
		return -1;
	}
	switch (OPERAND (reg_num).type) {
	case MIPS_OP_REG:
		reg->name = (char *)cs_reg_name (handle, OPERAND (reg_num).reg);
		break;
	case MIPS_OP_MEM:
		if (OPERAND (reg_num).mem.base != MIPS_REG_INVALID) {
			reg->name = (char *)cs_reg_name (handle, OPERAND (reg_num).mem.base);
		}
	default:
		break;
	}
	return 0;
}