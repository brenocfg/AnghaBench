#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int ut8 ;
typedef  int /*<<< orphan*/  ut64 ;
struct TYPE_4__ {int size; short jump; int eob; int /*<<< orphan*/  fail; void* type; int /*<<< orphan*/  addr; } ;
typedef  int /*<<< orphan*/  RAnalOpMask ;
typedef  TYPE_1__ RAnalOp ;
typedef  int /*<<< orphan*/  RAnal ;

/* Variables and functions */
 void* R_ANAL_OP_TYPE_CJMP ; 
 void* R_ANAL_OP_TYPE_CMP ; 
 void* R_ANAL_OP_TYPE_JMP ; 
 void* R_ANAL_OP_TYPE_RET ; 
 void* R_ANAL_OP_TYPE_SWI ; 
 int /*<<< orphan*/  memset (TYPE_1__*,char,int) ; 

__attribute__((used)) static int ppc_op(RAnal *anal, RAnalOp *op, ut64 addr, const ut8 *bytes, int len, RAnalOpMask mask) {
//int arch_ppc_op(ut64 addr, const u8 *bytes, struct op_t *op)
	// XXX hack
	int opcode = (bytes[0] & 0xf8) >> 3; // bytes 0-5
	short baddr = ((bytes[2]<<8) | (bytes[3]&0xfc));// 16-29
	int aa = bytes[3]&0x2;
	int lk = bytes[3]&0x1;
	//if (baddr>0x7fff)
	//      baddr = -baddr;

	memset (op, '\0', sizeof (RAnalOp));
	op->addr = addr;
	op->type = 0;
	op->size = 4;

	//eprintf("OPCODE IS %08x : %02x (opcode=%d) baddr = %d\n", addr, bytes[0], opcode, baddr);

	switch (opcode) {
//	case 0: // bl op->type = R_ANAL_OP_TYPE_NOP; break;
	case 11: // cmpi
		op->type = R_ANAL_OP_TYPE_CMP;
		break;
	case 9: // pure branch
		if (bytes[0] == 0x4e) {
			// bctr
		} else {
			op->jump = (aa)?(baddr):(addr+baddr);
			if (lk) {
				op->fail = addr + 4;
			}
		}
		op->eob = 1;
		break;
	case 6: // bc // conditional jump
		op->type = R_ANAL_OP_TYPE_JMP;
		op->jump = (aa)?(baddr):(addr+baddr+4);
		op->eob = 1;
		break;
#if 0
	case 7: // sc/svc
		op->type = R_ANAL_OP_TYPE_SWI;
		break;
#endif
#if 0
	case 15: // bl
		// OK
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = (aa)?(baddr):(addr+baddr);
		op->fail = addr+4;
		op->eob = 1;
		break;
#endif
	case 8: // bne i tal
		// OK
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = (aa)?(baddr):(addr+baddr+4);
		op->fail = addr+4;
		op->eob = 1;
		break;
	case 19: // bclr/bcr/bcctr/bcc
		op->type = R_ANAL_OP_TYPE_RET; // jump to LR
		if (lk) {
			op->jump = 0xFFFFFFFF; // LR ?!?
			op->fail = addr+4;
		}
		op->eob = 1;
		break;
	}
	op->size = 4;
	return op->size;
}