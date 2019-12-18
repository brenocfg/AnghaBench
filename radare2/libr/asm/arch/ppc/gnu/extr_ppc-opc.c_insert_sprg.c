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
typedef  int ppc_cpu_t ;

/* Variables and functions */
 int PPC_OPCODE_405 ; 
 int PPC_OPCODE_BOOKE ; 
 char* _ (char*) ; 

__attribute__((used)) static unsigned long
insert_sprg (unsigned long insn,
	     long value,
	     ppc_cpu_t dialect,
	     const char **errmsg)
{
	if (value > 7 || (value > 3 && (dialect & (PPC_OPCODE_BOOKE | PPC_OPCODE_405)) == 0)) {
		*errmsg = _ ("invalid sprg number");
	}

	/* If this is mfsprg4..7 then use spr 260..263 which can be read in
     user mode.  Anything else must use spr 272..279.  */
	if (value <= 3 || (insn & 0x100) != 0) {
		value |= 0x10;
	}

	return insn | ((value & 0x17) << 16);
}