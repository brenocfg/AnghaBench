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
struct cris_spec_reg {int reg_size; } ;
struct cris_opcode {char* args; scalar_t__ imm_oprnd_size; } ;
typedef  enum cris_disass_family { ____Placeholder_cris_disass_family } cris_disass_family ;

/* Variables and functions */
 scalar_t__ SIZE_FIX_32 ; 
 scalar_t__ SIZE_SPEC_REG ; 
 int cris_dis_v32 ; 
 struct cris_spec_reg* spec_reg_info (unsigned int,int) ; 

__attribute__((used)) static unsigned
bytes_to_skip (unsigned int insn,
	       const struct cris_opcode *matchedp,
	       enum cris_disass_family distype,
	       const struct cris_opcode *prefix_matchedp)
{
  /* Each insn is a word plus "immediate" operands.  */
  unsigned to_skip = 2;
  const char *template = matchedp->args;
  const char *s;

  for (s = template; *s; s++) {
	  if ((*s == 's' || *s == 'N' || *s == 'Y') && (insn & 0x400) && (insn & 15) == 15 && !prefix_matchedp) {
		  /* Immediate via [pc+], so we have to check the size of the
	   operand.  */
		  int mode_size = 1 << ((insn >> 4) & (*template == 'z' ? 1 : 3));

		  if (matchedp->imm_oprnd_size == SIZE_FIX_32) {
			  to_skip += 4;
		  } else if (matchedp->imm_oprnd_size == SIZE_SPEC_REG) {
			  const struct cris_spec_reg *sregp = spec_reg_info ((insn >> 12) & 15, distype);

			  /* FIXME: Improve error handling; should have been caught
	       earlier.  */
			  if (!sregp) {
				  return 2;
			  }

			  /* PC is incremented by two, not one, for a byte.  Except on
	       CRISv32, where constants are always DWORD-size for
	       special registers.  */
			  to_skip +=
				  distype == cris_dis_v32 ? 4 : (sregp->reg_size + 1) & ~1;
		  } else {
			  to_skip += (mode_size + 1) & ~1;
		  }
	  } else if (*s == 'n') {
		  to_skip += 4;
	  } else if (*s == 'b') {
		  to_skip += 2;
	  }
  }

  return to_skip;
}