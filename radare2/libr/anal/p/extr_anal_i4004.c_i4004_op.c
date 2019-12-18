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
typedef  int ut8 ;
typedef  int ut64 ;
typedef  int const ut16 ;
typedef  int /*<<< orphan*/  basm ;
struct TYPE_3__ {int size; int jump; int fail; int val; void* type; int /*<<< orphan*/  esil; } ;
typedef  int /*<<< orphan*/  RAnalOpMask ;
typedef  TYPE_1__ RAnalOp ;
typedef  int /*<<< orphan*/  RAnal ;

/* Variables and functions */
 void* R_ANAL_OP_TYPE_ADD ; 
 void* R_ANAL_OP_TYPE_CALL ; 
 void* R_ANAL_OP_TYPE_CJMP ; 
 void* R_ANAL_OP_TYPE_ILL ; 
 void* R_ANAL_OP_TYPE_JMP ; 
 void* R_ANAL_OP_TYPE_LOAD ; 
 void* R_ANAL_OP_TYPE_MOV ; 
 void* R_ANAL_OP_TYPE_NOP ; 
 void* R_ANAL_OP_TYPE_RET ; 
 void* R_ANAL_OP_TYPE_RJMP ; 
 void* R_ANAL_OP_TYPE_SHL ; 
 void* R_ANAL_OP_TYPE_SHR ; 
 void* R_ANAL_OP_TYPE_SUB ; 
 void* R_ANAL_OP_TYPE_XCHG ; 
 int /*<<< orphan*/ * i4004_e ; 
 int /*<<< orphan*/ * i4004_f ; 
 int i4004_get_ins_len (int const) ; 
 int /*<<< orphan*/  r_strbuf_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,size_t const,char*,int,...) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  strncpy (char*,int /*<<< orphan*/ ,size_t const) ; 

__attribute__((used)) static int i4004_op(RAnal *anal, RAnalOp *op, ut64 addr, const ut8 *buf, int len, RAnalOpMask mask) {
	char basm[128];
	const size_t basz = sizeof (basm)-1;
	int rlen = i4004_get_ins_len (*buf);
	if (!op) {
		return 2;
	}
	r_strbuf_init (&op->esil);
	ut8 high = (*buf & 0xf0)>>4;
	ut8 low = (*buf & 0xf);
	basm[0] = 0;

	if (rlen > len) {
		return op->size = 0;
	}
	switch (high) {
	case 0:
		if (low) {
			op->type = R_ANAL_OP_TYPE_ILL;
		} else {
			op->type = R_ANAL_OP_TYPE_NOP;
		}
		break;
	case 1: //snprintf (basm, basz, "jcn %d 0x%02x", low, buf[1]); break;
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = (addr & (~0xFF)) + buf[1];
		op->fail = addr + rlen;
		break;
	case 2:
		if (rlen == 1) {
			snprintf (basm, basz, "scr r%d", (low & 0xe));
		} else {
			op->type = R_ANAL_OP_TYPE_MOV;
			op->val = buf[1];
			snprintf (basm, basz, "fim r%d, 0x%02x", (low & 0xe), buf[1]);
		}
		break;
	case 3:
		if (low & 1) {
			op->type = R_ANAL_OP_TYPE_RJMP;
		} else {
			op->type = R_ANAL_OP_TYPE_MOV;
			snprintf (basm, basz, "fin r%d", (low & 0xe));
		}
		break;
	case 4:
		op->type = R_ANAL_OP_TYPE_JMP;
		op->jump = (ut16) (low<<8) | buf[1];
		break;
	case 5: //snprintf (basm, basz, "jms 0x%03x", ((ut16)(low<<8) | buf[1])); break;
		op->type = R_ANAL_OP_TYPE_CALL;
		op->jump = (ut16) (low<<8) | buf[1];
		op->fail = addr + rlen;
		break;
	case 6: //snprintf (basm, basz, "inc r%d", low); break;
		op->type = R_ANAL_OP_TYPE_ADD;
		break;
	case 7: //snprintf (basm, basz, "isz r%d, 0x%02x", low, buf[1]); 
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->fail = (addr & (~0xFF)) + buf[1];
		op->jump = addr + rlen;
		break;
	case 8:
		op->type = R_ANAL_OP_TYPE_ADD;
		//snprintf (basm, basz, "add r%d", low); break;
		break;
	case 9:
		op->type = R_ANAL_OP_TYPE_SUB;
		//snprintf (basm, basz, "sub r%d", low); break;
		break;
	case 10: //snprintf (basm, basz, "ld r%d", low); break;
		op->type = R_ANAL_OP_TYPE_MOV;
		break;
	case 11: //snprintf (basm, basz, "xch r%d", low); break;
		op->type = R_ANAL_OP_TYPE_XCHG;
		break;
	case 12: //snprintf (basm, basz, "bbl %d", low); break;
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	case 13:
		op->type = R_ANAL_OP_TYPE_LOAD;
		//snprintf (basm, basz, "ldm %d", low); break;
		break;
	case 14:
		strncpy (basm, i4004_e[low], basz);
		basm[basz] = '\0';
		break;
	case 15:
		strncpy (basm, i4004_f[low], basz);
		basm[basz] = '\0';
		if (!strcmp (basm, "dac")) {
			op->type = R_ANAL_OP_TYPE_SUB;
		}
		break;
	}
	if (!strcmp (basm, "invalid")) {
		op->type = R_ANAL_OP_TYPE_ILL;
	} else if (!strcmp (basm, "ral")) {
		op->type = R_ANAL_OP_TYPE_SHL;
	} else if (!strcmp (basm, "rar")) {
		op->type = R_ANAL_OP_TYPE_SHR;
	}
	return op->size = rlen;
}