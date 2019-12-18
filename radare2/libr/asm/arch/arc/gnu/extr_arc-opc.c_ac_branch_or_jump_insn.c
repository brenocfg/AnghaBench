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
typedef  int arc_insn ;

/* Variables and functions */
 int I (int) ; 

int
ac_branch_or_jump_insn(arc_insn insn, int compact_insn_16)
{

  return ((!compact_insn_16 && ((insn & I(-1)) == I(0x4)) &&
			       (((insn >> 18) & 0xf) == 0x8)) ||
	  (compact_insn_16 && ((insn & I(-1)) == I(0xf))) ||
	  (!compact_insn_16 && ((insn & I(-1)) == I(0x1))) ||
	  (compact_insn_16 && ((insn & I(-1)) == I(0x1f))) ||
	  (!compact_insn_16 && ((insn & I(-1)) == I(0x0))) ||
	  (compact_insn_16 && ((insn & I(-1)) == I(0x1e))));
}