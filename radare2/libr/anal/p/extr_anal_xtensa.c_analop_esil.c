#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_1__ ;

/* Type definitions */
typedef  int xtensa_opcode ;
typedef  int /*<<< orphan*/  xtensa_isa ;
typedef  int /*<<< orphan*/  xtensa_insnbuf ;
typedef  int /*<<< orphan*/  xtensa_format ;
struct TYPE_27__ {int /*<<< orphan*/  esil; } ;
typedef  TYPE_1__ RAnalOp ;

/* Variables and functions */
 int /*<<< orphan*/  esil_abs_neg (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  esil_add_imm (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  esil_add_sub (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  esil_bitwise_op (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  esil_branch_check_bit (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  esil_branch_check_bit_imm (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  esil_branch_check_mask (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  esil_branch_compare (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  esil_branch_compare_imm (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  esil_branch_compare_single (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  esil_call (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  esil_callx (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  esil_extract_unsigned (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  esil_load_imm (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  esil_load_relative (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  esil_move (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  esil_move_conditional (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  esil_move_imm (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  esil_set_shift_amount (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  esil_set_shift_amount_imm (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  esil_shift_logic_imm (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  esil_shift_logic_sar (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  esil_store_imm (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  r_strbuf_setf (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  xtensa_check_stack_op (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static void analop_esil (xtensa_isa isa, xtensa_opcode opcode, xtensa_format format,
						 size_t i, xtensa_insnbuf slot_buffer, RAnalOp *op) {
	switch (opcode) {
	case 26: /* add.n */
	case 41: /* add */
	case 43: /* addx2 */
	case 44: /* addx4 */
	case 45: /* addx8 */
	case 42: /* sub */
	case 46: /* subx2 */
	case 47: /* subx4 */
	case 48: /* subx8 */
		esil_add_sub (isa, opcode, format, i, slot_buffer, op);
		break;
	case 32: /* mov.n */
		esil_move (isa, opcode, format, i, slot_buffer, op);
		break;
	case 90: /* movi */
	case 33: /* movi.n */
		esil_move_imm (isa, opcode, format, i, slot_buffer, op);
		break;
	case 0:  /* excw */
	case 34: /* nop.n */
		r_strbuf_setf (&op->esil, "");
		break;
	// TODO: s32cli (s32c1i) is conditional (CAS)
	// should it be handled here?
	case 453: /* s32c1i */
	case 36:  /* s32i.n */
	case 100: /* s32i */
	case 99:  /* s16i */
	case 101: /* s8i */
		esil_store_imm (isa, opcode, format, i, slot_buffer, op);
		break;
	case 27: /* addi.n */
	case 39: /* addi */
		xtensa_check_stack_op (isa, opcode, format, i, slot_buffer, op);
		esil_add_imm (isa, opcode, format, i, slot_buffer, op);
		break;
	case 98: /* ret */
	case 35: /* ret.n */
		r_strbuf_setf (&op->esil, "a0,pc,=");
		break;
	case 82: /* l16ui */
	case 83: /* l16si */
	case 84: /* l32i */
	case 31: /* l32i.n */
	case 86: /* l8ui */
		esil_load_imm (isa, opcode, format, i, slot_buffer, op);
		break;
	// TODO: s32r
	// l32r is different because it is relative to LITBASE
	// which also may or may not be present
	case 85: /* l32r */
		esil_load_relative (isa, opcode, format, i, slot_buffer, op);
		break;
	case 40: /* addmi */
		break;
	case 49: /* and */
	case 50: /* or */
	case 51: /* xor */
		esil_bitwise_op (isa, opcode, format, i, slot_buffer, op);
		break;
	case 52: /* beqi */
	case 53: /* bnei */
	case 54: /* bgei */
	case 55: /* blti */
	case 58: /* bgeui */
	case 59: /* bltui */
		esil_branch_compare_imm (isa, opcode, format, i, slot_buffer, op);
		break;
	case 56: /* bbci */
	case 57: /* bbsi */
		esil_branch_check_bit_imm (isa, opcode, format, i, slot_buffer, op);
		break;
	case 60: /* beq */
	case 61: /* bne */
	case 62: /* bge */
	case 63: /* blt */
	case 64: /* bgeu */
	case 65: /* bltu */
		esil_branch_compare (isa, opcode, format, i, slot_buffer, op);
		break;
	case 66: /* bany */
	case 67: /* bnone */
	case 68: /* ball */
	case 69: /* bnall */
		esil_branch_check_mask (isa, opcode, format, i, slot_buffer, op);
		break;
	case 70: /* bbc */
	case 71: /* bbs */
		esil_branch_check_bit (isa, opcode, format, i, slot_buffer, op);
		break;
	case 72: /* beqz */
	case 73: /* bnez */
	case 28: /* beqz.n */
	case 29: /* bnez.n */
	case 74: /* bgez */
	case 75: /* bltz */
		esil_branch_compare_single (isa, opcode, format, i, slot_buffer, op);
		break;
	case 78: /* extui */
		esil_extract_unsigned (isa, opcode, format, i, slot_buffer, op);
		break;
	case 79: /* ill */
		r_strbuf_setf (&op->esil, "");
		break;
	// TODO: windowed calls?
	case 7: /* call4 */
		break;
	case 76: /* call0 */
	case 80: /* j */
		esil_call (isa, opcode, format, i, slot_buffer, op);
		break;
	case 81: /* jx */
	case 77: /* callx0 */
		esil_callx (isa, opcode, format, i, slot_buffer, op);
		break;
	case 91: /* moveqz */
	case 92: /* movnez */
	case 93: /* movltz */
	case 94: /* movgez */
		esil_move_conditional (isa, opcode, format, i, slot_buffer, op);
		break;
	case 96: /* abs */
	case 95: /* neg */
		esil_abs_neg (isa, opcode, format, i, slot_buffer, op);
		break;
	case 102: /* ssr */
	case 103: /* ssl */
		esil_set_shift_amount (isa, opcode, format, i, slot_buffer, op);
		break;
	case 111: /* slli */
	case 113: /* srli */
		esil_shift_logic_imm (isa, opcode, format, i, slot_buffer, op);
		break;
	case 106: /* ssai */
		esil_set_shift_amount_imm (isa, opcode, format, i, slot_buffer, op);
		break;
	case 107: /* sll */
	case 109: /* srl */
		esil_shift_logic_sar (isa, opcode, format, i, slot_buffer, op);
		break;
	}
}