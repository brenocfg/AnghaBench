#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int type; } ;
struct TYPE_5__ {int /*<<< orphan*/  csr_reg_str; int /*<<< orphan*/  csr; int /*<<< orphan*/  dest_reg_str; int /*<<< orphan*/  dest_reg; int /*<<< orphan*/  src0_reg_str; int /*<<< orphan*/  src0_reg; int /*<<< orphan*/  src1_reg_str; int /*<<< orphan*/  src1_reg; TYPE_1__ op_decode; } ;
typedef  TYPE_2__ RAsmLm32Instruction ;

/* Variables and functions */
 int /*<<< orphan*/  csr_number_to_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  csr_reg 138 
#define  imm26 137 
#define  one_reg 136 
#define  raise_instr 135 
#define  reg_csr 134 
#define  reg_imm16_shift2_signextend 133 
#define  reg_imm16_signextend 132 
#define  reg_imm16_zeroextend 131 
#define  reg_imm5 130 
 int /*<<< orphan*/  reg_number_to_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  three_regs 129 
#define  two_regs 128 

__attribute__((used)) static int write_reg_names_to_struct(RAsmLm32Instruction *instr) {
	switch (instr->op_decode.type) {
	case reg_imm16_signextend:
	case reg_imm16_shift2_signextend:
	case reg_imm16_zeroextend:
	case reg_imm5:
	case two_regs:
		if (reg_number_to_string (instr->dest_reg, instr->dest_reg_str)) {
			return -1;
		}
		if (reg_number_to_string (instr->src0_reg, instr->src0_reg_str)) {
			return -1;
		}
		break;
	case one_reg:
		if (reg_number_to_string (instr->src0_reg, instr->src0_reg_str)) {
			return -1;
		}
		break;
	case three_regs:
		if (reg_number_to_string (instr->dest_reg, instr->dest_reg_str)) {
			return -1;
		}
		if (reg_number_to_string (instr->src0_reg, instr->src0_reg_str)) {
			return -1;
		}
		if (reg_number_to_string (instr->src1_reg, instr->src1_reg_str)) {
			return -1;
		}
		break;
	case reg_csr:
		if (reg_number_to_string (instr->src0_reg, instr->src0_reg_str)) {
			return -1;
		}
		if (csr_number_to_string (instr->csr, instr->csr_reg_str)) {
			return -1;
		}
		break;
	case csr_reg:
		if (reg_number_to_string (instr->dest_reg, instr->dest_reg_str)) {
			return -1;
		}
		if (csr_number_to_string (instr->csr, instr->csr_reg_str)) {
			return -1;
		}
		break;
	case raise_instr:
	case imm26:
		break;
	default:
		return -1;
	}
	return 0;
}