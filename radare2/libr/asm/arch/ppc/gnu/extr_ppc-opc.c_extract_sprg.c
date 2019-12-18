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

__attribute__((used)) static long
extract_sprg (unsigned long insn,
	      ppc_cpu_t dialect,
	      int *invalid)
{
  unsigned long val = (insn >> 16) & 0x1f;

  /* mfsprg can use 260..263 and 272..279.  mtsprg only uses spr 272..279
     If not BOOKE or 405, then both use only 272..275.  */
  if ((val - 0x10 > 3 && (dialect & (PPC_OPCODE_BOOKE | PPC_OPCODE_405)) == 0) || (val - 0x10 > 7 && (insn & 0x100) != 0) || val <= 3 || (val & 8) != 0) {
	  *invalid = 1;
  }
  return val & 7;
}