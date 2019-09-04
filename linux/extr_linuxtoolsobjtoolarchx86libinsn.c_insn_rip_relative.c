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
struct insn_field {int value; scalar_t__ nbytes; int /*<<< orphan*/  got; } ;
struct insn {int /*<<< orphan*/  x86_64; struct insn_field modrm; } ;

/* Variables and functions */
 int /*<<< orphan*/  insn_get_modrm (struct insn*) ; 

int insn_rip_relative(struct insn *insn)
{
	struct insn_field *modrm = &insn->modrm;

	if (!insn->x86_64)
		return 0;
	if (!modrm->got)
		insn_get_modrm(insn);
	/*
	 * For rip-relative instructions, the mod field (top 2 bits)
	 * is zero and the r/m field (bottom 3 bits) is 0x5.
	 */
	return (modrm->nbytes && (modrm->value & 0xc7) == 0x5);
}