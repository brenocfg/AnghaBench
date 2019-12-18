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
typedef  int /*<<< orphan*/  ut8 ;
typedef  void* ut64 ;
typedef  int ut32 ;
typedef  int ut16 ;
struct winedbg_arm_insn {int jmp; int fail; } ;
struct TYPE_3__ {int jump; int fail; int ptr; int val; int size; void* type; scalar_t__ delay; } ;
typedef  TYPE_1__ RAnalOp ;
typedef  int /*<<< orphan*/  RAnal ;

/* Variables and functions */
 int B0010 ; 
 int B0011 ; 
 int B0100 ; 
 int B0101 ; 
 int B0111 ; 
 int B1000 ; 
 int B1011 ; 
 int B1100 ; 
 int B1101 ; 
 int B1110 ; 
 int B1111 ; 
 int B4 (int,int,int,int) ; 
 void* R_ANAL_OP_TYPE_CALL ; 
 void* R_ANAL_OP_TYPE_CJMP ; 
 void* R_ANAL_OP_TYPE_CMP ; 
 void* R_ANAL_OP_TYPE_JMP ; 
 void* R_ANAL_OP_TYPE_LOAD ; 
 void* R_ANAL_OP_TYPE_NOP ; 
 void* R_ANAL_OP_TYPE_STORE ; 
 void* R_ANAL_OP_TYPE_SWI ; 
 void* R_ANAL_OP_TYPE_TRAP ; 
 void* R_ANAL_OP_TYPE_UCALL ; 
 void* R_ANAL_OP_TYPE_UJMP ; 
 int arm_disasm_one_insn (struct winedbg_arm_insn*) ; 
 int /*<<< orphan*/  arm_free (struct winedbg_arm_insn*) ; 
 struct winedbg_arm_insn* arm_new () ; 
 int /*<<< orphan*/  arm_set_input_buffer (struct winedbg_arm_insn*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  arm_set_pc (struct winedbg_arm_insn*,void*) ; 
 int /*<<< orphan*/  arm_set_thumb (struct winedbg_arm_insn*,int) ; 

__attribute__((used)) static int op_thumb(RAnal *anal, RAnalOp *op, ut64 addr, const ut8 *data, int len) {
	int op_code;
	ut16 *_ins = (ut16 *) data;
	ut16 ins = *_ins;
	ut32 *_ins32 = (ut32 *) data;
	ut32 ins32 = *_ins32;

	struct winedbg_arm_insn *arminsn = arm_new ();
	arm_set_thumb (arminsn, true);
	arm_set_input_buffer (arminsn, data);
	arm_set_pc (arminsn, addr);
	op->jump = op->fail = -1;
	op->ptr = op->val = -1;
	op->delay = 0;
	op->size = arm_disasm_one_insn (arminsn);
	op->jump = arminsn->jmp;
	op->fail = arminsn->fail;
	arm_free (arminsn);

	// TODO: handle 32bit instructions (branches are not correctly decoded //

	/* CMP */
	if (((ins & B4 (B1110, 0, 0, 0)) == B4 (B0010, 0, 0, 0))
	    && (1 == (ins & B4 (1, B1000, 0, 0)) >> 11)) { // dp3
		op->type = R_ANAL_OP_TYPE_CMP;
		return op->size;
	}
	if ((ins & B4 (B1111, B1100, 0, 0)) == B4 (B0100, 0, 0, 0)) {
		op_code = (ins & B4 (0, B0011, B1100, 0)) >> 6;
		if (op_code == 8 || op_code == 10) {  // dp5
			op->type = R_ANAL_OP_TYPE_CMP;
			return op->size;
		}
	}
	if ((ins & B4 (B1111, B1100, 0, 0)) == B4 (B0100, B0100, 0, 0)) {
		op_code = (ins & B4 (0, B0011, 0, 0)) >> 8;  // dp8
		if (op_code == 1) {
			op->type = R_ANAL_OP_TYPE_CMP;
			return op->size;
		}
	}
	if (ins == 0xbf) {
		// TODO: add support for more NOP instructions
		op->type = R_ANAL_OP_TYPE_NOP;
	} else if (((op_code = ((ins & B4 (B1111, B1000, 0, 0)) >> 11)) >= 12 &&
	            op_code <= 17)) {
		if (op_code % 2) {
			op->type = R_ANAL_OP_TYPE_LOAD;
		} else {
			op->type = R_ANAL_OP_TYPE_STORE;
		}
	} else if ((ins & B4 (B1111, 0, 0, 0)) == B4 (B0101, 0, 0, 0)) {
		op_code = (ins & B4 (0, B1110, 0, 0)) >> 9;
		if (op_code % 2) {
			op->type = R_ANAL_OP_TYPE_LOAD;
		} else {
			op->type = R_ANAL_OP_TYPE_STORE;
		}
	} else if ((ins & B4 (B1111, 0, 0, 0)) == B4 (B1101, 0, 0, 0)) {
		// BNE..
		int delta = (ins & B4 (0, 0, B1111, B1111));
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = addr + 4 + (delta << 1);
		op->fail = addr + 4;
	} else if ((ins & B4 (B1111, B1000, 0, 0)) == B4 (B1110, 0, 0, 0)) {
		// B
		int delta = (ins & B4 (0, 0, B1111, B1111));
		op->type = R_ANAL_OP_TYPE_JMP;
		op->jump = addr + 4 + (delta << 1);
		op->fail = addr + 4;
	} else if ((ins & B4 (B1111, B1111, B1000, 0)) ==
	           B4 (B0100, B0111, B1000, 0)) {
		// BLX
		op->type = R_ANAL_OP_TYPE_UCALL;
		op->fail = addr + 4;
	} else if ((ins & B4 (B1111, B1111, B1000, 0)) ==
	           B4 (B0100, B0111, 0, 0)) {
		// BX
		op->type = R_ANAL_OP_TYPE_UJMP;
		op->fail = addr + 4;
	} else if ((ins & B4 (B1111, B1000, 0, 0)) == B4 (B1111, 0, 0, 0)) {
		// BL The long branch with link, it's in 2 instructions:
		// prefix: 11110[offset]
		// suffix: 11111[offset] (11101[offset] for blx)
		ut16 nextins = (ins32 & 0xFFFF0000) >> 16;
		ut32 high = (ins & B4 (0, B0111, B1111, B1111)) << 12;
		if (ins & B4 (0, B0100, 0, 0)) {
			high |= B4 (B1111, B1000, 0, 0) << 16;
		}
		int delta = high + ((nextins & B4 (0, B0111, B1111, B1111)) * 2);
		op->jump = (int) (addr + 4 + (delta));
		op->type = R_ANAL_OP_TYPE_CALL;
		op->fail = addr + 4;
	} else if ((ins & B4 (B1111, B1111, 0, 0)) == B4 (B1011, B1110, 0, 0)) {
		op->type = R_ANAL_OP_TYPE_TRAP;
		op->val = (ut64) (ins >> 8);
	} else if ((ins & B4 (B1111, B1111, 0, 0)) == B4 (B1101, B1111, 0, 0)) {
		op->type = R_ANAL_OP_TYPE_SWI;
		op->val = (ut64) (ins >> 8);
	}
	return op->size;
}