#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  ut64 ;
typedef  int /*<<< orphan*/  ut32 ;
typedef  int /*<<< orphan*/  arc_fields ;

/* Variables and functions */

__attribute__((used)) static void arccompact_dump_fields(ut64 addr, ut32 words[2], arc_fields *f) {
#if DEBUG
	/* Quick and dirty debug print */
	eprintf ("DEBUG: 0x%04llx: %08x op=0x%x subop=0x%x format=0x%x fields.a=0x%x fields.b=0x%x fields.c=0x%x imm=%i limm=%lli\n",
		addr, words[0], f->opcode, f->subopcode, f->format, f->a, f->b, f->c, f->imm, f->limm);
#endif
}