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
typedef  int /*<<< orphan*/  ut8 ;
typedef  int /*<<< orphan*/  ut64 ;
typedef  int ut32 ;
typedef  int ut16 ;
typedef  int /*<<< orphan*/  dword_instr ;
struct TYPE_4__ {int size; int cycles; int jump; void* type; int /*<<< orphan*/  esil; } ;
typedef  TYPE_1__ RAnalOp ;
typedef  int /*<<< orphan*/  RAnal ;

/* Variables and functions */
 void* R_ANAL_OP_TYPE_ADD ; 
 void* R_ANAL_OP_TYPE_AND ; 
 void* R_ANAL_OP_TYPE_CALL ; 
 void* R_ANAL_OP_TYPE_CJMP ; 
 void* R_ANAL_OP_TYPE_CMP ; 
 void* R_ANAL_OP_TYPE_CPL ; 
 void* R_ANAL_OP_TYPE_ILL ; 
 void* R_ANAL_OP_TYPE_JMP ; 
 void* R_ANAL_OP_TYPE_LOAD ; 
 void* R_ANAL_OP_TYPE_MOV ; 
 void* R_ANAL_OP_TYPE_MUL ; 
 void* R_ANAL_OP_TYPE_NOP ; 
 void* R_ANAL_OP_TYPE_OR ; 
 void* R_ANAL_OP_TYPE_POP ; 
 void* R_ANAL_OP_TYPE_PUSH ; 
 void* R_ANAL_OP_TYPE_RET ; 
 void* R_ANAL_OP_TYPE_ROL ; 
 void* R_ANAL_OP_TYPE_ROR ; 
 void* R_ANAL_OP_TYPE_STORE ; 
 void* R_ANAL_OP_TYPE_SUB ; 
 void* R_ANAL_OP_TYPE_UNK ; 
 void* R_ANAL_OP_TYPE_XOR ; 
 int /*<<< orphan*/  R_MIN (int,int) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pic18_cond_branch (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,char*) ; 
 int /*<<< orphan*/  r_strbuf_setf (int /*<<< orphan*/ *,char*,...) ; 

__attribute__((used)) static int anal_pic_pic18_op(RAnal *anal, RAnalOp *op, ut64 addr, const ut8 *buf, int len) {
	//TODO code should be refactored and broken into smaller chunks!!
	//TODO complete the esil emitter
	if (len < 2) {
		op->size = len;
		goto beach; //pancake style :P
	}
	op->size = 2;
	ut16 b = *(ut16 *)buf;
	ut32 dword_instr = 0;
	memcpy (&dword_instr, buf, R_MIN (sizeof (dword_instr), len));
	switch (b >> 9) {
	case 0x76: //call
		if (len < 4) {
			goto beach;
		}
		if (dword_instr >> 28 != 0xf) {
			goto beach;
		}
		op->size = 4;
		op->type = R_ANAL_OP_TYPE_CALL;
		return op->size;
	};
	switch (b >> 11) { //NEX_T
	case 0x1b:	//rcall
		op->type = R_ANAL_OP_TYPE_CALL;
		return op->size;
	case 0x1a: //bra
		op->type = R_ANAL_OP_TYPE_JMP;
		op->cycles = 2;
		op->jump = addr + 2 + 2 * (*(ut16 *)buf & 0x7ff);
		r_strbuf_setf (&op->esil, "0x%x,pc,=", op->jump);
		return op->size;
	}
	switch (b >> 12) { //NOP,movff,BAF_T
	case 0xf:	//nop
		op->type = R_ANAL_OP_TYPE_NOP;
		op->cycles = 1;
		r_strbuf_setf (&op->esil, ",");
		return op->size;
	case 0xc: //movff
		if (len < 4) {
			goto beach;
		}
		if (dword_instr >> 28 != 0xf) {
			goto beach;
		}
		op->size = 4;
		op->type = R_ANAL_OP_TYPE_MOV;
		return op->size;
	case 0xb: //btfsc
	case 0xa: //btfss
		op->type = R_ANAL_OP_TYPE_CJMP;
		return op->size;
	case 0x9: //bcf
	case 0x8: //bsf
	case 0x7: //btg
		op->type = R_ANAL_OP_TYPE_UNK;
		return op->size;
	};

	switch (b >> 8) { //GOTO_T,N_T,K_T
	case 0xe0:	//bz
		pic18_cond_branch (op, addr, buf, "z");
		return op->size;
	case 0xe1: //bnz
		pic18_cond_branch (op, addr, buf, "z,!");
		return op->size;
	case 0xe3: //bnc
		pic18_cond_branch (op, addr, buf, "c,!");
		return op->size;
	case 0xe4: //bov
		pic18_cond_branch (op, addr, buf, "ov");
		return op->size;
	case 0xe5: //bnov
		pic18_cond_branch (op, addr, buf, "ov,!");
		return op->size;
	case 0xe6: //bn
		pic18_cond_branch (op, addr, buf, "n");
		return op->size;
	case 0xe7: //bnn
		pic18_cond_branch (op, addr, buf, "n,!");
		return op->size;
	case 0xe2: //bc
		pic18_cond_branch (op, addr, buf, "c");
		return op->size;
	case 0xef: //goto
		if (len < 4) {
			goto beach;
		}
		if (dword_instr >> 28 != 0xf) {
			goto beach;
		}
		op->size = 4;
		op->cycles = 2;
		op->jump = ((dword_instr & 0xff) | ((dword_instr & 0xfff0000) >> 8)) * 2;
		r_strbuf_setf (&op->esil, "0x%x,pc,=", op->jump);
		op->type = R_ANAL_OP_TYPE_JMP;
		return op->size;
	case 0xf: //addlw
		op->type = R_ANAL_OP_TYPE_ADD;
		op->cycles = 1;
		//TODO add support for dc flag
		r_strbuf_setf (&op->esil, "0x%x,wreg,+=,$z,z,:=,7,$s,n,:=,7,$c,c,:=,7,$o,ov,:=,", *(ut16 *)buf & 0xff);
		return op->size;
	case 0xe: //movlw
		op->type = R_ANAL_OP_TYPE_LOAD;
		op->cycles = 1;
		r_strbuf_setf (&op->esil, "0x%x,wreg,=,");
		return op->size;
	case 0xd: //mullw
		op->type = R_ANAL_OP_TYPE_MUL;
		op->cycles = 1;
		r_strbuf_setf (&op->esil, "0x%x,wreg,*,prod,=", *(ut16 *)buf & 0xff);
		return op->size;
	case 0xc: //retlw
		op->type = R_ANAL_OP_TYPE_RET;
		op->cycles = 2;
		r_strbuf_setf (&op->esil, "0x%x,wreg,=,tos,pc,=,", *(ut16 *)buf & 0xff);
		return op->size;
	case 0xb: //andlw
		op->type = R_ANAL_OP_TYPE_AND;
		op->cycles = 1;
		r_strbuf_setf (&op->esil, "0x%x,wreg,&=,$z,z,:=,7,$s,n,:=,", *(ut16 *)buf & 0xff);
		return op->size;
	case 0xa: //xorlw
		op->type = R_ANAL_OP_TYPE_XOR;
		op->cycles = 1;
		r_strbuf_setf (&op->esil, "0x%x,wreg,^=,$z,z,:=,7,$s,n,:=,", *(ut16 *)buf & 0xff);
		return op->size;
	case 0x9: //iorlw
		op->type = R_ANAL_OP_TYPE_OR;
		op->cycles = 1;
		r_strbuf_setf (&op->esil, "0x%x,wreg,^=,$z,z,:=,7,$s,n,:=,", *(ut16 *)buf & 0xff);
		return op->size;
	case 0x8: //sublw
		op->type = R_ANAL_OP_TYPE_SUB;
		op->cycles = 1;
		//TODO add support for dc flag
		r_strbuf_setf (&op->esil, "wreg,0x%x,-,wreg,=,$z,z,:=,7,$s,n,:=,7,$c,c,:=,7,$o,ov,:=,", *(ut16 *)buf & 0xff);
		return op->size;
	};

	switch (b >> 6) { //LFSR
	case 0x3b8:       //lfsr
		if (len < 4) {
			goto beach;
		}
		if (dword_instr >> 28 != 0xf) {
			goto beach;
		}
		op->size = 4;
		op->type = R_ANAL_OP_TYPE_LOAD;
		return op->size;
	};
	switch (b >> 10) { //DAF_T
	case 0x17:	//subwf
	case 0x16:	//subwfb
	case 0x15:	//subfwb
	case 0x13:	//dcfsnz
	case 0xb:	//decfsz
	case 0x1:	//decf
		op->type = R_ANAL_OP_TYPE_SUB;
		return op->size;
	case 0x14: //movf
		op->type = R_ANAL_OP_TYPE_MOV;
		return op->size;
	case 0x12: //infsnz
	case 0xf:  //incfsz
	case 0xa:  //incf
	case 0x8:  //addwfc
		op->type = R_ANAL_OP_TYPE_ADD;
		return op->size;
	case 0x9: //addwf
		op->cycles = 1;
		op->type = R_ANAL_OP_TYPE_ADD;
		return op->size;
	case 0x11: //rlncf
	case 0xd:  //rlcf
		op->type = R_ANAL_OP_TYPE_ROL;
		return op->size;
	case 0x10: //rrncf
	case 0xc:  //rrcf
		op->type = R_ANAL_OP_TYPE_ROR;
		return op->size;
	case 0xe: //swapf
		op->type = R_ANAL_OP_TYPE_UNK;
		return op->size;
	case 0x7: //comf
		op->type = R_ANAL_OP_TYPE_CPL;
		return op->size;
	case 0x6: //xorwf
		op->type = R_ANAL_OP_TYPE_XOR;
		return op->size;
	case 0x5: //andwf
		op->type = R_ANAL_OP_TYPE_AND;
		return op->size;
	case 0x4: //iorwf
		op->type = R_ANAL_OP_TYPE_OR;
		return op->size;
	};
	switch (b >> 9) { //AF_T
	case 0x37:	//movwf
		op->type = R_ANAL_OP_TYPE_STORE;
		return op->size;
	case 0x36: //negf
	case 0x35: //clrf
	case 0x34: //setf
		op->type = R_ANAL_OP_TYPE_UNK;
		return op->size;
	case 0x33: //tstfsz
		op->type = R_ANAL_OP_TYPE_CJMP;
		return op->size;
	case 0x32: //cpfsgt
	case 0x31: //cpfseq
	case 0x30: //cpfslt
		op->type = R_ANAL_OP_TYPE_CMP;
		return op->size;
	case 0x1: //mulwf
		op->type = R_ANAL_OP_TYPE_MUL;
		return op->size;
	};
	switch (b >> 4) {
	case 0x10: //movlb
		op->type = R_ANAL_OP_TYPE_LOAD;
		op->cycles = 1;
		r_strbuf_setf (&op->esil, "0x%x,bsr,=,", *(ut16 *)buf & 0xf);
		return op->size;
	};
	switch (b) {
	case 0xff: //reset
	case 0x7:  //daw
	case 0x4:  //clwdt
	case 0x3:  //sleep
		op->type = R_ANAL_OP_TYPE_UNK;
		return op->size;
	case 0x13: //return
		op->type = R_ANAL_OP_TYPE_RET;
		op->cycles = 2;
		r_strbuf_setf (&op->esil, "tos,pc,=,");
		return op->size;
	case 0x12: //return
		op->type = R_ANAL_OP_TYPE_RET;
		op->cycles = 2;
		r_strbuf_setf (&op->esil, "tos,pc,=");
		return op->size;
	case 0x11: //retfie
	case 0x10: //retfie
		op->type = R_ANAL_OP_TYPE_RET;
		return op->size;
	case 0xf: //tblwt
	case 0xe: //tblwt
	case 0xd: //tblwt
	case 0xc: //tblwt
		op->type = R_ANAL_OP_TYPE_LOAD;
		return op->size;
	case 0xb: //tblrd
	case 0xa: //tblrd
	case 0x9: //tblrd
	case 0x8: //tblrd
		op->type = R_ANAL_OP_TYPE_STORE;
		return op->size;
	case 0x6: //pop
		op->type = R_ANAL_OP_TYPE_POP;
		return op->size;
	case 0x5: //push
		op->type = R_ANAL_OP_TYPE_PUSH;
		return op->size;
	case 0x0: //nop
		op->type = R_ANAL_OP_TYPE_NOP;
		op->cycles = 1;
		r_strbuf_setf (&op->esil, ",");
		return op->size;
	};
beach:
	op->type = R_ANAL_OP_TYPE_ILL;
	return op->size;
}