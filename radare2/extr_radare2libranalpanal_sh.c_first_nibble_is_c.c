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
typedef  scalar_t__ ut8 ;
typedef  int ut16 ;
struct TYPE_4__ {int size; int /*<<< orphan*/  esil; void* dst; void* type; void** src; scalar_t__ val; } ;
typedef  TYPE_1__ RAnalOp ;
typedef  int /*<<< orphan*/  RAnal ;

/* Variables and functions */
 scalar_t__ IS_BINLOGIC_IMM_GBR (int) ; 
 scalar_t__ IS_BINLOGIC_IMM_R0 (int) ; 
 scalar_t__ IS_MOVA_PCREL_R0 (int) ; 
 scalar_t__ IS_MOVB_GBRREF_R0 (int) ; 
 scalar_t__ IS_MOVB_R0_GBRREF (int) ; 
 scalar_t__ IS_MOVL_GBRREF_R0 (int) ; 
 scalar_t__ IS_MOVL_R0_GBRREF (int) ; 
 scalar_t__ IS_MOVW_GBRREF_R0 (int) ; 
 scalar_t__ IS_MOVW_R0_GBRREF (int) ; 
 scalar_t__ IS_TRAP (int) ; 
 int /*<<< orphan*/  LONG_SIZE ; 
 void* R_ANAL_OP_TYPE_ACMP ; 
 void* R_ANAL_OP_TYPE_AND ; 
 void* R_ANAL_OP_TYPE_LEA ; 
 void* R_ANAL_OP_TYPE_LOAD ; 
 void* R_ANAL_OP_TYPE_OR ; 
 void* R_ANAL_OP_TYPE_STORE ; 
 void* R_ANAL_OP_TYPE_SWI ; 
 void* R_ANAL_OP_TYPE_XOR ; 
 void* anal_fill_ai_rg (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* anal_fill_im (int /*<<< orphan*/ *,int) ; 
 void* anal_pcrel_disp_mov (int /*<<< orphan*/ *,TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_strbuf_setf (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static int first_nibble_is_c(RAnal* anal, RAnalOp* op, ut16 code) {
	if (IS_TRAP (code)) {
		op->type = R_ANAL_OP_TYPE_SWI;
		op->val = (ut8)(code & 0xFF);
		r_strbuf_setf (&op->esil, "4,r15,-=,sr,r15,=[4],4,r15,-=,2,pc,-,r15,=[4],2,0x%x,<<,4,+,vbr,+,pc,=", code & 0xFF);
	} else if (IS_MOVA_PCREL_R0 (code)) {
		// 11000111i8p4.... mova @(<disp>,PC),R0
		op->type = R_ANAL_OP_TYPE_LEA;
		op->src[0] = anal_pcrel_disp_mov (anal, op, code & 0xFF, LONG_SIZE);	//this is wrong !
		op->dst = anal_fill_ai_rg (anal, 0); //Always R0
		r_strbuf_setf (&op->esil, "0x%x,pc,+,r0,=", (code & 0xFF) * 4);
	} else if (IS_BINLOGIC_IMM_R0 (code)) {	// 110010__i8 (binop) #imm, R0
		op->src[0] = anal_fill_im (anal, code & 0xFF);
		op->src[1] = anal_fill_ai_rg (anal, 0);	//Always R0
		op->dst = anal_fill_ai_rg (anal, 0); //Always R0 except tst #imm, R0
		switch(code & 0xFF00) {
		case 0xC800:	//tst
			//TODO : get correct op->dst ! (T flag)
			op->type = R_ANAL_OP_TYPE_ACMP;
			r_strbuf_setf (&op->esil, "0xFFFFFFFE,sr,&=,r0,0x%x,&,!,?{,1,sr,|=,}", code & 0xFF);
			break;
		case 0xC900:	//and
			op->type = R_ANAL_OP_TYPE_AND;
			r_strbuf_setf (&op->esil, "0x%x,r0,&=", code & 0xFF);
			break;
		case 0xCA00:	//xor
			op->type = R_ANAL_OP_TYPE_XOR;
			r_strbuf_setf (&op->esil, "0x%x,r0,^=", code & 0xFF);
			break;
		case 0xCB00:	//or
			op->type = R_ANAL_OP_TYPE_OR;
			r_strbuf_setf (&op->esil, "0x%x,r0,|=", code & 0xFF);
			break;
		}
	} else if (IS_BINLOGIC_IMM_GBR (code)) {	//110011__i8 (binop).b #imm, @(R0,gbr)
		op->src[0] = anal_fill_im (anal, code & 0xFF);
		switch(code & 0xFF00) {
		case 0xCC00:	//tst
			//TODO : get correct op->dst ! (T flag)
			op->type = R_ANAL_OP_TYPE_ACMP;
			r_strbuf_setf (&op->esil, "0xFFFFFFFE,sr,&=,r0,gbr,+,[1],0x%x,&,!,?{,1,sr,|=,}", code & 0xFF);
			break;
		case 0xCD00:	//and
			op->type = R_ANAL_OP_TYPE_AND;
			r_strbuf_setf (&op->esil, "r0,gbr,+,[1],0x%x,&,r0,gbr,+,=[1]", code & 0xFF);
			break;
		case 0xCE00:	//xor
			op->type = R_ANAL_OP_TYPE_XOR;
			r_strbuf_setf (&op->esil, "r0,gbr,+,[1],0x%x,^,r0,gbr,+,=[1]", code & 0xFF);
			break;
		case 0xCF00:	//or
			op->type = R_ANAL_OP_TYPE_OR;
			r_strbuf_setf (&op->esil, "r0,gbr,+,[1],0x%x,|,r0,gbr,+,=[1]", code & 0xFF);
			break;
		}
		//TODO : implement @(R0,gbr) dest and src[1]
	} else if (IS_MOVB_R0_GBRREF (code)) {
		op->type = R_ANAL_OP_TYPE_STORE;
		op->src[0] = anal_fill_ai_rg (anal, 0);
		r_strbuf_setf (&op->esil, "r0,gbr,0x%x,+,=[1]", code & 0xFF);
	} else if (IS_MOVW_R0_GBRREF (code)) {
		op->type = R_ANAL_OP_TYPE_STORE;
		op->src[0] = anal_fill_ai_rg (anal, 0);
		r_strbuf_setf (&op->esil, "r0,gbr,0x%x,+,=[2]", (code & 0xFF) * 2);
	} else if (IS_MOVL_R0_GBRREF (code)) {
		op->type = R_ANAL_OP_TYPE_STORE;
		op->src[0] = anal_fill_ai_rg (anal, 0);
		r_strbuf_setf (&op->esil, "r0,gbr,0x%x,+,=[4]", (code & 0xFF) * 4);
	} else if (IS_MOVB_GBRREF_R0 (code)) {
		op->type = R_ANAL_OP_TYPE_LOAD;
		op->dst = anal_fill_ai_rg (anal, 0);
		r_strbuf_setf (&op->esil, "gbr,0x%x,+,[1],DUP,0x80,&,?{,0xFFFFFF00,|,},r0,=", (code & 0xFF));
	} else if (IS_MOVW_GBRREF_R0 (code)) {
		op->type = R_ANAL_OP_TYPE_LOAD;
		op->dst = anal_fill_ai_rg (anal, 0);
		r_strbuf_setf (&op->esil, "gbr,0x%x,+,[2],DUP,0x8000,&,?{,0xFFFF0000,|,},r0,=", (code & 0xFF)*2);
	} else if (IS_MOVL_GBRREF_R0 (code)) {
		op->type = R_ANAL_OP_TYPE_LOAD;
		op->dst = anal_fill_ai_rg (anal, 0);
		r_strbuf_setf (&op->esil, "gbr,0x%x,+,[4],r0,=", (code & 0xFF) * 4);
	}

	return op->size;
}