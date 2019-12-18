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
typedef  int /*<<< orphan*/  ut64 ;
typedef  int /*<<< orphan*/  ut32 ;
struct TYPE_3__ {int /*<<< orphan*/  limm; int /*<<< orphan*/  imm; int /*<<< orphan*/  c; int /*<<< orphan*/  b; int /*<<< orphan*/  a; int /*<<< orphan*/  format; int /*<<< orphan*/  subopcode; int /*<<< orphan*/  opcode; } ;
typedef  TYPE_1__ arc_fields ;

/* Variables and functions */
 int /*<<< orphan*/  eprintf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void arccompact_dump_fields(ut64 addr, ut32 words[2], arc_fields *f) {
#if DEBUG
	/* Quick and dirty debug print */
	eprintf ("DEBUG: 0x%04llx: %08x op=0x%x subop=0x%x format=0x%x fields.a=0x%x fields.b=0x%x fields.c=0x%x imm=%i limm=%lli\n",
		addr, words[0], f->opcode, f->subopcode, f->format, f->a, f->b, f->c, f->imm, f->limm);
#endif
}