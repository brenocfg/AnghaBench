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
struct lh5801_insn {int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  buf_asm ;
struct TYPE_3__ {int size; int /*<<< orphan*/  buf_asm; } ;
typedef  TYPE_1__ RAsmOp ;
typedef  int /*<<< orphan*/  RAsm ;

/* Variables and functions */
 int lh5801_decode (struct lh5801_insn*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  lh5801_print_insn (char*,int,struct lh5801_insn*) ; 
 int /*<<< orphan*/  r_strbuf_set (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int disassemble(RAsm *as, RAsmOp *op, const ut8 *buf, int len) {
	struct lh5801_insn insn = {0};
	if (!op) {
		return 0;
	}
	int consumed = lh5801_decode (&insn, buf, len);
	if (consumed == -1 || consumed == 0) {
		r_strbuf_set (&op->buf_asm, "invalid");
		op->size = 1;
		return 0;
	}
	char buf_asm[128] = {0};
	lh5801_print_insn (buf_asm, sizeof (buf_asm), &insn);
	r_strbuf_set (&op->buf_asm, buf_asm);
	op->size = consumed;
	//op->payload = lh5801_insn_descs[insn.type].format & 3;
	// ^ MAYBE?
	return op->size;
}