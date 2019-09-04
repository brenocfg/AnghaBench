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
typedef  int /*<<< orphan*/  ut8 ;
typedef  int /*<<< orphan*/  ut64 ;
struct TYPE_6__ {char* syntax; } ;
struct TYPE_5__ {int size; int /*<<< orphan*/  type; scalar_t__ delay; } ;
typedef  TYPE_1__ RAnalOp ;
typedef  int /*<<< orphan*/  RAnal ;

/* Variables and functions */
 int /*<<< orphan*/  R_ANAL_OP_TYPE_ACMP ; 
 int /*<<< orphan*/  R_ANAL_OP_TYPE_CALL ; 
 int /*<<< orphan*/  R_ANAL_OP_TYPE_CCALL ; 
 int /*<<< orphan*/  R_ANAL_OP_TYPE_CJMP ; 
 int /*<<< orphan*/  R_ANAL_OP_TYPE_CMP ; 
 int /*<<< orphan*/  R_ANAL_OP_TYPE_CRET ; 
 int /*<<< orphan*/  R_ANAL_OP_TYPE_JMP ; 
 int /*<<< orphan*/  R_ANAL_OP_TYPE_MOV ; 
 int /*<<< orphan*/  R_ANAL_OP_TYPE_NOP ; 
 int /*<<< orphan*/  R_ANAL_OP_TYPE_NULL ; 
 int /*<<< orphan*/  R_ANAL_OP_TYPE_POP ; 
 int /*<<< orphan*/  R_ANAL_OP_TYPE_PUSH ; 
 int /*<<< orphan*/  R_ANAL_OP_TYPE_RET ; 
 int /*<<< orphan*/  R_ANAL_OP_TYPE_SWI ; 
 int /*<<< orphan*/  R_ANAL_OP_TYPE_TRAP ; 
 int /*<<< orphan*/  R_ANAL_OP_TYPE_UCALL ; 
 int /*<<< orphan*/  R_ANAL_OP_TYPE_UJMP ; 
 int /*<<< orphan*/  R_ANAL_OP_TYPE_UNK ; 
 int /*<<< orphan*/  R_ANAL_OP_TYPE_UPUSH ; 
 TYPE_2__ engine ; 
 scalar_t__ match (char const*,char*) ; 
 scalar_t__ strstr (char const*,char*) ; 
 int tms320_dasm (TYPE_2__*,int /*<<< orphan*/  const*,int) ; 

int tms320_c55x_op(RAnal *anal, RAnalOp *op, ut64 addr, const ut8 *buf, int len) {
	const char * str = engine.syntax;

	op->delay = 0;
	op->size = tms320_dasm(&engine, buf, len);
	op->type = R_ANAL_OP_TYPE_NULL;

	str = strstr(str, "||") ? str + 3 : str;

	if (match(str, "B ")) {
		op->type = R_ANAL_OP_TYPE_JMP;
		if (match (str, "B AC")) {
			op->type = R_ANAL_OP_TYPE_UJMP;
		}
	} else if (match(str, "BCC ") || match(str, "BCCU ")) {
		op->type = R_ANAL_OP_TYPE_CJMP;
	} else if (match(str, "CALL ")) {
		op->type = R_ANAL_OP_TYPE_CALL;
		if (match (str, "CALL AC")) {
			op->type = R_ANAL_OP_TYPE_UCALL;
		}
	} else if (match(str, "CALLCC ")) {
		op->type = R_ANAL_OP_TYPE_CCALL;
	} else if (match(str, "RET")) {
		op->type = R_ANAL_OP_TYPE_RET;
		if (match (str, "RETCC")) {
			op->type = R_ANAL_OP_TYPE_CRET;
		}
	} else if (match(str, "MOV ")) {
		op->type = R_ANAL_OP_TYPE_MOV;
	} else if (match(str, "PSHBOTH ")) {
		op->type = R_ANAL_OP_TYPE_UPUSH;
	} else if (match(str, "PSH ")) {
		op->type = R_ANAL_OP_TYPE_PUSH;
	} else if (match(str, "POPBOTH ") || match(str, "POP ")) {
		op->type = R_ANAL_OP_TYPE_POP;
	} else if (match(str, "CMP ")) {
		op->type = R_ANAL_OP_TYPE_CMP;
	} else if (match(str, "CMPAND ")) {
		op->type = R_ANAL_OP_TYPE_ACMP;
	} else if (match(str, "NOP")) {
		op->type = R_ANAL_OP_TYPE_NOP;
	} else if (match(str, "INTR ")) {
		op->type = R_ANAL_OP_TYPE_SWI;
	} else if (match(str, "TRAP ")) {
		op->type = R_ANAL_OP_TYPE_TRAP;
	} else if (match(str, "INVALID")) {
		op->type = R_ANAL_OP_TYPE_UNK;
	}

	return op->size;
}