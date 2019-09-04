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
struct cris_spec_reg {unsigned int reg_size; } ;
struct cris_opcode {int /*<<< orphan*/  match; } ;
struct cris_disasm_data {int /*<<< orphan*/  distype; } ;

/* Variables and functions */
 int /*<<< orphan*/  BDAP_QUICK_OPCODE ; 
 int /*<<< orphan*/  DIP_OPCODE ; 
 unsigned int NO_CRIS_PREFIX ; 
 int /*<<< orphan*/  cris_dis_v0_v10 ; 
 struct cris_opcode* get_opcode_entry (unsigned int,unsigned int,struct cris_disasm_data*) ; 
 struct cris_spec_reg* spec_reg_info (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cris_constraint (const char *cs,
		 unsigned int insn,
		 unsigned int prefix_insn,
		 struct cris_disasm_data *disdata)
{
  int retval = 0;
  int tmp;
  int prefix_ok = 0;
  const char *s;

  for (s = cs; *s; s++) {
	  switch (*s) {
	  case '!':
		  /* Do not recognize "pop" if there's a prefix and then only for
           v0..v10.  */
		  if (prefix_insn != NO_CRIS_PREFIX || disdata->distype != cris_dis_v0_v10) {
			  return -1;
		  }
		  break;

	  case 'U':
		  /* Not recognized at disassembly.  */
		  return -1;

	  case 'M':
		  /* Size modifier for "clear", i.e. special register 0, 4 or 8.
	   Check that it is one of them.  Only special register 12 could
	   be mismatched, but checking for matches is more logical than
	   checking for mismatches when there are only a few cases.  */
		  tmp = ((insn >> 12) & 0xf);
		  if (tmp != 0 && tmp != 4 && tmp != 8) {
			  return -1;
		  }
		  break;

	  case 'm':
		  if ((insn & 0x30) == 0x30) {
			  return -1;
		  }
		  break;

	  case 'S':
		  /* A prefix operand without side-effect.  */
		  if (prefix_insn != NO_CRIS_PREFIX && (insn & 0x400) == 0) {
			  prefix_ok = 1;
			  break;
		  } else {
			  return -1;
		  }

	  case 's':
	  case 'y':
	  case 'Y':
		  /* If this is a prefixed insn with postincrement (side-effect),
	   the prefix must not be DIP.  */
		  if (prefix_insn != NO_CRIS_PREFIX) {
			  if (insn & 0x400) {
				  const struct cris_opcode *prefix_opcodep = get_opcode_entry (prefix_insn, NO_CRIS_PREFIX, disdata);

				  if (prefix_opcodep->match == DIP_OPCODE) {
					  return -1;
				  }
			  }

			  prefix_ok = 1;
		  }
		  break;

	  case 'B':
		  /* If we don't fall through, then the prefix is ok.  */
		  prefix_ok = 1;

		  /* A "push" prefix.  Check for valid "push" size.
	   In case of special register, it may be != 4.  */
		  if (prefix_insn != NO_CRIS_PREFIX) {
			  /* Match the prefix insn to BDAPQ.  */
			  const struct cris_opcode *prefix_opcodep = get_opcode_entry (prefix_insn, NO_CRIS_PREFIX, disdata);

			  if (prefix_opcodep->match == BDAP_QUICK_OPCODE) {
				  int pushsize = (prefix_insn & 255);

				  if (pushsize > 127) {
					  pushsize -= 256;
				  }

				  if (s[1] == 'P') {
					  unsigned int spec_reg = (insn >> 12) & 15;
					  const struct cris_spec_reg *sregp = spec_reg_info (spec_reg, disdata->distype);

					  /* For a special-register, the "prefix size" must
		       match the size of the register.  */
					  if (sregp && sregp->reg_size == (unsigned int)-pushsize) {
						  break;
					  }
				  } else if (s[1] == 'R') {
					  if ((insn & 0x30) == 0x20 && pushsize == -4) {
						  break;
					  }
				  }
				  /* FIXME:  Should abort here; next constraint letter
		   *must* be 'P' or 'R'.  */
			  }
		  }
		  return -1;

	  case 'D':
		  retval = (((insn >> 12) & 15) == (insn & 15));
		  if (!retval) {
			  return -1;
		  } else {
			  retval += 4;
		  }
		  break;

	  case 'P': {
		  const struct cris_spec_reg *sregp = spec_reg_info ((insn >> 12) & 15, disdata->distype);

		  /* Since we match four bits, we will give a value of 4-1 = 3
	     in a match.  If there is a corresponding exact match of a
	     special register in another pattern, it will get a value of
	     4, which will be higher.  This should be correct in that an
	     exact pattern would match better than a general pattern.

	     Note that there is a reason for not returning zero; the
	     pattern for "clear" is partly  matched in the bit-pattern
	     (the two lower bits must be zero), while the bit-pattern
	     for a move from a special register is matched in the
	     register constraint.  */

		  if (sregp != NULL) {
			  retval += 3;
			  break;
		  } else {
			  return -1;
		  }
	  }
	  }
  }

  if (prefix_insn != NO_CRIS_PREFIX && !prefix_ok) {
	  return -1;
  }

  return retval;
}