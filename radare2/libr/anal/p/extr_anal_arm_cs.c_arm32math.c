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
typedef  int /*<<< orphan*/  ut64 ;
typedef  int /*<<< orphan*/  csh ;
typedef  int /*<<< orphan*/  cs_insn ;
struct TYPE_3__ {int /*<<< orphan*/  esil; } ;
typedef  TYPE_1__ RAnalOp ;
typedef  int /*<<< orphan*/  RAnal ;

/* Variables and functions */
 char* ARG (int) ; 
 int OPCOUNT () ; 
 int /*<<< orphan*/  r_strbuf_appendf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static void arm32math(RAnal *a, RAnalOp *op, ut64 addr, const ut8 *buf, int len, csh *handle, cs_insn *insn, int pcdelta, char (*str)[32], const char *opchar, int negate) {
	const char *dest = ARG(0);
	const char *op1;
	const char *op2;
	bool rotate_imm = OPCOUNT() > 3;
	if (OPCOUNT() > 2) {
		 op1 = ARG(1);
		 op2 = ARG(2);
	} else {
		op1 = dest;
		op2 = ARG(1);
	}
	// right operand
	if (rotate_imm) {
		r_strbuf_appendf (&op->esil, "%s,", ARG(3));
	}
	if (!strcmp (op2, "pc")) {
		r_strbuf_appendf (&op->esil, "%d,$$,+", pcdelta);
	} else {
		r_strbuf_appendf (&op->esil, "%s", op2);
	}
	if (rotate_imm) {
		r_strbuf_appendf (&op->esil, ",>>>");
	}
	if (negate) {
		r_strbuf_appendf (&op->esil, ",-1,^");
	}
	if (!strcmp (op1, "pc")) {
		r_strbuf_appendf (&op->esil, ",%d,$$,+,%s,0xffffffff,&,%s,=", pcdelta, opchar, dest);
	} else {
		r_strbuf_appendf (&op->esil, ",%s,%s,0xffffffff,&,%s,=", op1, opchar, dest);
	}
}