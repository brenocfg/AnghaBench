#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int ut8 ;
typedef  int /*<<< orphan*/  ut64 ;
typedef  size_t ut32 ;
struct winedbg_arm_insn {int dummy; } ;
struct TYPE_9__ {int bits; scalar_t__ big_endian; } ;
struct TYPE_8__ {int jump; int fail; int ptr; int val; int size; int refptr; void* type; void* stackop; int /*<<< orphan*/  cond; int /*<<< orphan*/  addr; } ;
typedef  TYPE_1__ RAnalOp ;
typedef  TYPE_2__ RAnal ;

/* Variables and functions */
 size_t ARM_DTX_LOAD ; 
 scalar_t__ IS_BRANCH (size_t) ; 
 scalar_t__ IS_BRANCHL (size_t) ; 
 scalar_t__ IS_CONDAL (size_t) ; 
 scalar_t__ IS_EXITPOINT (size_t) ; 
 scalar_t__ IS_LOAD (size_t) ; 
 void* R_ANAL_OP_TYPE_ADD ; 
 void* R_ANAL_OP_TYPE_CALL ; 
 void* R_ANAL_OP_TYPE_CJMP ; 
 void* R_ANAL_OP_TYPE_JMP ; 
 void* R_ANAL_OP_TYPE_LOAD ; 
 void* R_ANAL_OP_TYPE_MOV ; 
 void* R_ANAL_OP_TYPE_NOP ; 
 void* R_ANAL_OP_TYPE_RET ; 
 void* R_ANAL_OP_TYPE_SUB ; 
 void* R_ANAL_OP_TYPE_SWI ; 
 void* R_ANAL_OP_TYPE_UJMP ; 
 void* R_ANAL_OP_TYPE_UNK ; 
 void* R_ANAL_STACK_GET ; 
 void* R_ANAL_STACK_INC ; 
 int UT64_MAX ; 
 int /*<<< orphan*/  arm_free (struct winedbg_arm_insn*) ; 
 struct winedbg_arm_insn* arm_new () ; 
 int /*<<< orphan*/  arm_set_input_buffer (struct winedbg_arm_insn*,int const*) ; 
 int /*<<< orphan*/  arm_set_pc (struct winedbg_arm_insn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arm_set_thumb (struct winedbg_arm_insn*,int) ; 
 size_t disarm_branch_offset (int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,char,int) ; 
 int /*<<< orphan*/  op_cond (int const*) ; 
 int op_thumb (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ ,int const*,int) ; 

__attribute__((used)) static int arm_op32(RAnal *anal, RAnalOp *op, ut64 addr, const ut8 *data, int len) {
	const ut8 *b = (ut8 *) data;
	ut8 ndata[4];
	ut32 branch_dst_addr, i = 0;
	ut32 *code = (ut32 *) data;
	struct winedbg_arm_insn *arminsn;

	if (!data) {
		return 0;
	}
	memset (op, '\0', sizeof (RAnalOp));
	arminsn = arm_new ();
	arm_set_thumb (arminsn, false);
	arm_set_input_buffer (arminsn, data);
	arm_set_pc (arminsn, addr);
	op->jump = op->fail = -1;
	op->ptr = op->val = -1;
	op->addr = addr;
	op->type = R_ANAL_OP_TYPE_UNK;

	if (anal->big_endian) {
		b = data = ndata;
		ndata[0] = data[3];
		ndata[1] = data[2];
		ndata[2] = data[1];
		ndata[3] = data[0];
	}
	if (anal->bits == 16) {
		arm_free (arminsn);
		return op_thumb (anal, op, addr, data, len);
	}
	op->size = 4;
	op->cond = op_cond (data);
	if (b[2] == 0x8f && b[3] == 0xe2) {
		op->type = R_ANAL_OP_TYPE_ADD;
#define ROR(x, y) ((int) ((x) >> (y)) | (((x) << (32 - (y)))))
		op->ptr = addr + ROR (b[0], (b[1] & 0xf) << 1) + 8;
	} else if (b[2] >= 0x9c && b[2] <= 0x9f) {  // load instruction
		char ch = b[3] & 0xf;
		switch (ch) {
		case 5:
			if ((b[3] & 0xf) == 5) {
				op->ptr = 8 + addr + b[0] + ((b[1] & 0xf) << 8);
				// XXX: if set it breaks the visual disasm wtf
				// op->refptr = true;
			}
		case 4:
		case 6:
		case 7:
		case 8:
		case 9: op->type = R_ANAL_OP_TYPE_LOAD; break;
		}
	} else // 0x000037b8  00:0000   0             800000ef  svc 0x00000080
	if (b[2] == 0xa0 && b[3] == 0xe1) {
		int n = (b[0] << 16) + b[1];
		op->type = R_ANAL_OP_TYPE_MOV;
		switch (n) {
		case 0:
		case 0x0110: case 0x0220: case 0x0330: case 0x0440:
		case 0x0550: case 0x0660: case 0x0770: case 0x0880:
		case 0x0990: case 0x0aa0: case 0x0bb0: case 0x0cc0:
			op->type = R_ANAL_OP_TYPE_NOP;
			break;
		}
	} else if (b[3] == 0xef) {
		op->type = R_ANAL_OP_TYPE_SWI;
		op->val = (b[0] | (b[1] << 8) | (b[2] << 2));
	} else if ((b[3] & 0xf) == 5) {  // [reg,0xa4]
#if 0
		0x00000000      a4a09fa4 ldrge sl, [pc], 0xa4
		0x00000000      a4a09fa5 ldrge sl, [pc, 0xa4]
		0x00000000      a4a09fa6 ldrge sl, [pc], r4, lsr 1
		0x00000000      a4a09fa7 ldrge sl, [pc, r4, lsr 1]
		0x00000000      a4a09fe8 ldm pc, {
			r2, r5, r7, sp, pc
		}; < UNPREDICT
#endif
		if ((b[1] & 0xf0) == 0xf0) {
			// ldr pc, [pc, #1] ;
			// op->type = R_ANAL_OP_TYPE_UJMP;
			op->type = R_ANAL_OP_TYPE_RET; // FAKE FOR FUN
			// op->stackop = R_ANAL_STACK_SET;
			op->jump = 1234;
			// op->ptr = 4+addr+b[0]; // sure? :)
			// op->ptrptr = true;
		}
		// eprintf("0x%08x\n", code[i] & ARM_DTX_LOAD);
		// 0x0001B4D8,           1eff2fe1        bx    lr
	} else if (b[3] == 0xe2 && b[2] == 0x8d && b[1] == 0xd0) {
		// ADD SP, SP, ...
		op->type = R_ANAL_OP_TYPE_ADD;
		op->stackop = R_ANAL_STACK_INC;
		op->val = -b[0];
	} else if (b[3] == 0xe2 && b[2] == 0x4d && b[1] == 0xd0) {
		// SUB SP, SP, ..
		op->type = R_ANAL_OP_TYPE_SUB;
		op->stackop = R_ANAL_STACK_INC;
		op->val = b[0];
	} else if (b[3] == 0xe2 && b[2] == 0x4c && b[1] == 0xb0) {
		// SUB SP, FP, ..
		op->type = R_ANAL_OP_TYPE_SUB;
		op->stackop = R_ANAL_STACK_INC;
		op->val = -b[0];
	} else if (b[3] == 0xe2 && b[2] == 0x4b && b[1] == 0xd0) {
		// SUB SP, IP, ..
		op->type = R_ANAL_OP_TYPE_SUB;
		op->stackop = R_ANAL_STACK_INC;
		op->val = -b[0];
	} else if ((code[i] == 0x1eff2fe1) ||
	           (code[i] == 0xe12fff1e)) {  // bx lr
		op->type = R_ANAL_OP_TYPE_RET;
	} else if ((code[i] & ARM_DTX_LOAD)) {  // IS_LOAD(code[i])) {
		ut32 ptr = 0;
		op->type = R_ANAL_OP_TYPE_MOV;
		if (b[2] == 0x1b) {
			/* XXX pretty incomplete */
			op->stackop = R_ANAL_STACK_GET;
			op->ptr = b[0];
			// var_add_access(addr, -b[0], 1, 0); // TODO: set/get (the last 0)
		} else {
			// ut32 oaddr = addr+8+b[0];
			// XXX TODO ret = radare_read_at(oaddr, (ut8*)&ptr, 4);
			if (anal->bits == 32) {
				b = (ut8 *) &ptr;
				op->ptr = b[0] + (b[1] << 8) + (b[2] << 16) + (b[3] << 24);
				// XXX data_xrefs_add(oaddr, op->ptr, 1);
				// TODO change data type to pointer
			} else {
				op->ptr = 0;
			}
		}
	}

	if (IS_LOAD (code[i])) {
		op->type = R_ANAL_OP_TYPE_LOAD;
		op->refptr = 4;
	}
	if (((((code[i] & 0xff) >= 0x10 && (code[i] & 0xff) < 0x20)) &&
	     ((code[i] & 0xffffff00) == 0xe12fff00)) ||
	    IS_EXITPOINT (code[i])) {
		// if (IS_EXITPOINT (code[i])) {
		b = data;
		branch_dst_addr = disarm_branch_offset (
			addr, b[0] | (b[1] << 8) |
			(b[2] << 16));                // code[i]&0x00FFFFFF);
		op->ptr = 0;
		if ((((code[i] & 0xff) >= 0x10 && (code[i] & 0xff) < 0x20)) &&
		    ((code[i] & 0xffffff00) == 0xe12fff00)) {
			op->type = R_ANAL_OP_TYPE_UJMP;
		} else if (IS_BRANCHL (code[i])) {
			if (IS_BRANCH (code[i])) {
				op->type = R_ANAL_OP_TYPE_CALL;
				op->jump = branch_dst_addr;
				op->fail = addr + 4;
			} else {
				op->type = R_ANAL_OP_TYPE_RET;
			}
		} else if (IS_BRANCH (code[i])) {
			if (IS_CONDAL (code[i])) {
				op->type = R_ANAL_OP_TYPE_JMP;
				op->jump = branch_dst_addr;
				op->fail = UT64_MAX;
			} else {
				op->type = R_ANAL_OP_TYPE_CJMP;
				op->jump = branch_dst_addr;
				op->fail = addr + 4;
			}
		} else {
			// unknown jump o return
			// op->type = R_ANAL_OP_TYPE_UJMP;
			// op->type = R_ANAL_OP_TYPE_NOP;
		}
	}
	// op->jump = arminsn->jmp;
	// op->fail = arminsn->fail;
	arm_free (arminsn);
	return op->size;
}