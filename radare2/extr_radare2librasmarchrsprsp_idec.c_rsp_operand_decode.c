#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut64 ;
typedef  int ut32 ;
struct TYPE_5__ {int type; int u_shift; int u_mask; int u_lshift; int s_shift; int s_mask; int s_lshift; int /*<<< orphan*/  s_smask; } ;
typedef  TYPE_1__ rsp_operand_decoder ;
struct TYPE_6__ {int type; int u; int s; } ;
typedef  TYPE_2__ rsp_operand ;

/* Variables and functions */
 int /*<<< orphan*/  RSP_IMEM_OFFSET ; 
#define  RSP_OPND_OFFSET 129 
#define  RSP_OPND_TARGET 128 
 void* rsp_mem_addr (int,int /*<<< orphan*/ ) ; 
 int rsp_sign_extend (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static rsp_operand rsp_operand_decode(ut64 pc, ut32 iw, const rsp_operand_decoder* odec) {
	rsp_operand opnd;

	opnd.type = odec->type;
	opnd.u = ((iw >> odec->u_shift) & odec->u_mask) << odec->u_lshift;
	opnd.s = rsp_sign_extend ((iw >> odec->s_shift) & odec->s_mask, odec->s_smask) << odec->s_lshift;

	/* handle targets/offsets IMEM addresses */
	switch (opnd.type) {
	case RSP_OPND_TARGET:
		opnd.u = rsp_mem_addr (opnd.u, RSP_IMEM_OFFSET);
		break;
	case RSP_OPND_OFFSET:
		/* +4 for delay slot */
		opnd.u = rsp_mem_addr (pc + 4 + opnd.s, RSP_IMEM_OFFSET);
		break;
	default: /* do nothing */ break;
	}

	return opnd;
}