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
 int /*<<< orphan*/  r_strbuf_appendf (int /*<<< orphan*/ *,char*,char const*,...) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static void arm32mathaddsub(RAnal *a, RAnalOp *op, ut64 addr, const ut8 *buf, int len, csh *handle, cs_insn *insn, int pcdelta, char (*str)[32], const char *opchar) {
	const char *dst = ARG(0);
	const char *src;
	bool noflags = false;
	if (!strcmp (dst, "pc")) {	//this is because strbuf_prepend doesn't exist and E_TOO_LAZY
//		r_strbuf_append (&op->esil, "$$,pc,=,");
		noflags = true;
	}
	if (OPCOUNT() == 3) {
		r_strbuf_appendf (&op->esil, "%s,0xffffffff,&,%s,=,", ARG (1), dst);
		src = ARG (2);
	} else {
//		src = (!strcmp (ARG (1), "pc")) ? "$$" : ARG (1);
		src = ARG (1);

	}
	r_strbuf_appendf (&op->esil, "%s,%s,%s,0xffffffff,&,%s,=", src, dst, opchar, dst);
	if (noflags) {
		return;
	}
	r_strbuf_appendf (&op->esil, ",$z,zf,:=,%s,cf,:=,vf,=,0,nf,=",
			(!strcmp (opchar, "+") ? "30,$c,31,$c,^,31,$c" : "30,$c,31,$c,^,32,$b"));
}