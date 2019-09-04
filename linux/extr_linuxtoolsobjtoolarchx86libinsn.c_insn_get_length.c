#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  got; } ;
struct insn {char length; scalar_t__ kaddr; scalar_t__ next_byte; TYPE_1__ immediate; } ;

/* Variables and functions */
 int /*<<< orphan*/  insn_get_immediate (struct insn*) ; 

void insn_get_length(struct insn *insn)
{
	if (insn->length)
		return;
	if (!insn->immediate.got)
		insn_get_immediate(insn);
	insn->length = (unsigned char)((unsigned long)insn->next_byte
				     - (unsigned long)insn->kaddr);
}