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
struct TYPE_3__ {int /*<<< orphan*/  esil; } ;
typedef  TYPE_1__ RAnalOp ;

/* Variables and functions */
 int _6502_FLAGS_B ; 
 int _6502_FLAGS_C ; 
 int _6502_FLAGS_N ; 
 int _6502_FLAGS_Z ; 
 int /*<<< orphan*/  r_strbuf_append (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void _6502_anal_update_flags(RAnalOp *op, int flags) {
	/* FIXME: 9,$b instead of 8,$b to prevent the bug triggered by: A = 0 - 0xff - 1 */
	if (flags & _6502_FLAGS_B) {
		r_strbuf_append (&op->esil, ",9,$b,C,:=");
	}
	if (flags & _6502_FLAGS_C) {
		r_strbuf_append (&op->esil, ",7,$c,C,:=");
	}
	if (flags & _6502_FLAGS_Z) {
		r_strbuf_append (&op->esil, ",$z,Z,:=");
	}
	if (flags & _6502_FLAGS_N) {
		r_strbuf_append (&op->esil, ",7,$s,N,:=");
	}
}