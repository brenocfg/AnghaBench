#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_14__ ;

/* Type definitions */
struct TYPE_15__ {int type; } ;
struct TYPE_16__ {size_t op; int pseudoInstruction; int /*<<< orphan*/  value; void* immediate; void* csr; void* dest_reg; void* src0_reg; void* src1_reg; TYPE_14__ op_decode; } ;
typedef  TYPE_1__ RAsmLm32Instruction ;

/* Variables and functions */
 int /*<<< orphan*/  RAsmLm32Imm16SignBitPos ; 
 int /*<<< orphan*/  RAsmLm32Imm26SignBitPos ; 
 TYPE_14__* RAsmLm32OpcodeList ; 
 size_t RAsmLm32OpcodeNumber ; 
#define  csr_reg 139 
 void* extract_imm16 (int /*<<< orphan*/ ) ; 
 void* extract_imm26 (int /*<<< orphan*/ ) ; 
 void* extract_imm5 (int /*<<< orphan*/ ) ; 
 size_t extract_opcode (int /*<<< orphan*/ ) ; 
 void* extract_reg_u (int /*<<< orphan*/ ) ; 
 void* extract_reg_v (int /*<<< orphan*/ ) ; 
 void* extract_reg_w (int /*<<< orphan*/ ) ; 
#define  imm26 138 
 int /*<<< orphan*/  is_invalid_imm5_instr (TYPE_1__*) ; 
 int /*<<< orphan*/  is_invalid_one_reg_instr (TYPE_1__*) ; 
 int /*<<< orphan*/  is_invalid_two_reg_instr (TYPE_1__*) ; 
 int /*<<< orphan*/  is_invalid_wcsr_instr (TYPE_1__*) ; 
 scalar_t__ is_pseudo_instr_mv (TYPE_1__*) ; 
 scalar_t__ is_pseudo_instr_mvhi (TYPE_1__*) ; 
 scalar_t__ is_pseudo_instr_mvi (TYPE_1__*) ; 
 scalar_t__ is_pseudo_instr_nop (TYPE_1__*) ; 
 scalar_t__ is_pseudo_instr_not (TYPE_1__*) ; 
 scalar_t__ is_pseudo_instr_raise (TYPE_1__*) ; 
 scalar_t__ is_pseudo_instr_ret (TYPE_1__*) ; 
#define  one_reg 137 
#define  raise_instr 136 
#define  reg_csr 135 
#define  reg_imm16_shift2_signextend 134 
#define  reg_imm16_signextend 133 
#define  reg_imm16_zeroextend 132 
#define  reg_imm5 131 
#define  reserved 130 
 void* shift_and_signextend (int,int /*<<< orphan*/ ,void*) ; 
#define  three_regs 129 
#define  two_regs 128 

__attribute__((used)) static int r_asm_lm32_decode(RAsmLm32Instruction *instr) {
	instr->op = extract_opcode (instr->value);
	if (instr->op >= RAsmLm32OpcodeNumber) {
		return -1;
	}
	instr->op_decode = RAsmLm32OpcodeList[instr->op];

	switch (instr->op_decode.type) {
	case reg_imm16_signextend:
		instr->dest_reg = extract_reg_v (instr->value);
		instr->src0_reg = extract_reg_u (instr->value);
		instr->immediate = shift_and_signextend (0, RAsmLm32Imm16SignBitPos,
				extract_imm16 (instr->value));
		break;
	case reg_imm16_shift2_signextend:
		instr->dest_reg = extract_reg_v (instr->value);
		instr->src0_reg = extract_reg_u (instr->value);
		instr->immediate = shift_and_signextend (2, RAsmLm32Imm16SignBitPos,
				extract_imm16 (instr->value));
		break;
	case reg_imm16_zeroextend:
		instr->dest_reg = extract_reg_v (instr->value);
		instr->src0_reg = extract_reg_u (instr->value);
		instr->immediate = extract_imm16 (instr->value);
		break;
	case reg_imm5:
		if (is_invalid_imm5_instr (instr)) {
			return -1;
		}
		instr->dest_reg = extract_reg_v (instr->value);
		instr->src0_reg = extract_reg_u (instr->value);
		instr->immediate = extract_imm5 (instr->value);
		break;
	case raise_instr:
		if (is_invalid_imm5_instr (instr)) {
			return -1;
		}
		//might be less bits used, but this shouldn't hurt
		//invalid parameters are caught in print_pseudo_instruction anyway
		instr->immediate = extract_imm5 (instr->value);
		break;
	case one_reg:
		if (is_invalid_one_reg_instr (instr)) {
			return -1;
		}
		instr->src0_reg = extract_reg_u (instr->value);
		break;
	case two_regs:
		if (is_invalid_two_reg_instr (instr)) {
			return -1;
		}
		instr->dest_reg = extract_reg_w (instr->value);
		instr->src0_reg = extract_reg_u (instr->value);
		break;
	case three_regs:
		instr->dest_reg = extract_reg_w (instr->value);
		instr->src0_reg = extract_reg_v (instr->value);
		instr->src1_reg = extract_reg_u (instr->value);
		break;
	case reg_csr: //wcsr
		if (is_invalid_wcsr_instr (instr)) {
			return -1;
		}
		instr->src0_reg = extract_reg_v (instr->value);
		instr->csr = extract_reg_u (instr->value);
		break;
	case csr_reg: //rcsr
		//bitmask is the same as the two register one
		if (is_invalid_two_reg_instr (instr)) {
			return -1;
		}
		instr->dest_reg = extract_reg_w (instr->value);
		instr->csr = extract_reg_u (instr->value);
		break;
	case imm26:
		instr->immediate = shift_and_signextend (2, RAsmLm32Imm26SignBitPos,
				extract_imm26 (instr->value));
		break;
	case reserved:
	default:
		return -1;
	}

	//see if the instruction corresponds to a pseudo-instruction
	instr->pseudoInstruction = is_pseudo_instr_ret (instr) || is_pseudo_instr_mv (instr) ||
			is_pseudo_instr_mvhi (instr) || is_pseudo_instr_not (instr) || is_pseudo_instr_mvi (instr) ||
			is_pseudo_instr_nop (instr) || is_pseudo_instr_raise (instr);

	return 0;
}