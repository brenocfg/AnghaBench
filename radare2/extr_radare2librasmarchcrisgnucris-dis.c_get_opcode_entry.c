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
struct cris_opcode {scalar_t__ match; int applicable_version; unsigned int lose; int /*<<< orphan*/  args; int /*<<< orphan*/ * name; } ;
struct cris_disasm_data {scalar_t__ distype; } ;
typedef  int /*<<< orphan*/  rest_prefixes ;
typedef  int /*<<< orphan*/  opc_table ;
typedef  int /*<<< orphan*/  dip_prefixes ;
typedef  int /*<<< orphan*/  bdapq_m4_prefixes ;
typedef  int /*<<< orphan*/  bdapq_m2_prefixes ;
typedef  int /*<<< orphan*/  bdapq_m1_prefixes ;

/* Variables and functions */
 scalar_t__ BDAP_QUICK_OPCODE ; 
 scalar_t__ DIP_OPCODE ; 
 unsigned int NO_CRIS_PREFIX ; 
 int /*<<< orphan*/  abort () ; 
 struct cris_opcode** calloc (int,int) ; 
 int cris_constraint (int /*<<< orphan*/ ,unsigned int,unsigned int,struct cris_disasm_data*) ; 
 scalar_t__ cris_dis_v32 ; 
 struct cris_opcode* cris_opcodes ; 
#define  cris_ver_sim_v0_10 140 
#define  cris_ver_v0_10 139 
#define  cris_ver_v0_3 138 
#define  cris_ver_v10 137 
#define  cris_ver_v10p 136 
#define  cris_ver_v32p 135 
#define  cris_ver_v3_10 134 
#define  cris_ver_v3p 133 
#define  cris_ver_v8 132 
#define  cris_ver_v8_10 131 
#define  cris_ver_v8p 130 
#define  cris_ver_version_all 129 
#define  cris_ver_warning 128 
 int number_of_bits (int) ; 

__attribute__((used)) static const struct cris_opcode *
get_opcode_entry (unsigned int insn,
		  unsigned int prefix_insn,
		  struct cris_disasm_data *disdata)
{
  /* For non-prefixed insns, we keep a table of pointers, indexed by the
     insn code.  Each entry is initialized when found to be NULL.  */
  static const struct cris_opcode **opc_table = NULL;

  const struct cris_opcode *max_matchedp = NULL;
  const struct cris_opcode **prefix_opc_table = NULL;

  /* We hold a table for each prefix that need to be handled differently.  */
  static const struct cris_opcode **dip_prefixes = NULL;
  static const struct cris_opcode **bdapq_m1_prefixes = NULL;
  static const struct cris_opcode **bdapq_m2_prefixes = NULL;
  static const struct cris_opcode **bdapq_m4_prefixes = NULL;
  static const struct cris_opcode **rest_prefixes = NULL;

  /* Allocate and clear the opcode-table.  */
  if (!opc_table)
    {
      opc_table = calloc (65536, sizeof (opc_table[0]));
      if (!opc_table) {
	      return NULL;
      }

      dip_prefixes
	= calloc (65536, sizeof (dip_prefixes[0]));
      if (!dip_prefixes) {
	      return NULL;
      }

      bdapq_m1_prefixes
	= calloc (65536, sizeof (bdapq_m1_prefixes[0]));
      if (!bdapq_m1_prefixes) {
	      return NULL;
      }

      bdapq_m2_prefixes
	= calloc (65536, sizeof (bdapq_m2_prefixes[0]));
      if (!bdapq_m2_prefixes) {
	      return NULL;
      }

      bdapq_m4_prefixes
	= calloc (65536, sizeof (bdapq_m4_prefixes[0]));
      if (!bdapq_m4_prefixes) {
	      return NULL;
      }

      rest_prefixes
	= calloc (65536, sizeof (rest_prefixes[0]));
      if (!rest_prefixes) {
	      return NULL;
      }
    }

  /* Get the right table if this is a prefix.
     This code is connected to cris_constraints in that it knows what
     prefixes play a role in recognition of patterns; the necessary
     state is reflected by which table is used.  If constraints
     involving match or non-match of prefix insns are changed, then this
     probably needs changing too.  */
  if (prefix_insn != NO_CRIS_PREFIX)
    {
      const struct cris_opcode *popcodep
	= (opc_table[prefix_insn] != NULL
	   ? opc_table[prefix_insn]
	   : get_opcode_entry (prefix_insn, NO_CRIS_PREFIX, disdata));

      if (!popcodep) {
	      return NULL;
      }

      if (popcodep->match == BDAP_QUICK_OPCODE)
	{
	  /* Since some offsets are recognized with "push" macros, we
	     have to have different tables for them.  */
	  int offset = (prefix_insn & 255);

	  if (offset > 127) {
		  offset -= 256;
	  }

	  switch (offset)
	    {
	    case -4:
	      prefix_opc_table = bdapq_m4_prefixes;
	      break;

	    case -2:
	      prefix_opc_table = bdapq_m2_prefixes;
	      break;

	    case -1:
	      prefix_opc_table = bdapq_m1_prefixes;
	      break;

	    default:
	      prefix_opc_table = rest_prefixes;
	      break;
	    }
      } else if (popcodep->match == DIP_OPCODE) {
	      /* We don't allow postincrement when the prefix is DIP, so use a
	   different table for DIP.  */
	      prefix_opc_table = dip_prefixes;
      } else {
	      prefix_opc_table = rest_prefixes;
      }
    }

    if (prefix_insn != NO_CRIS_PREFIX && prefix_opc_table[insn] != NULL) {
	    max_matchedp = prefix_opc_table[insn];
    } else if (prefix_insn == NO_CRIS_PREFIX && opc_table[insn] != NULL) {
	    max_matchedp = opc_table[insn];
    } else {
	    const struct cris_opcode *opcodep;
	    int max_level_of_match = -1;

	    for (opcodep = cris_opcodes;
		    opcodep->name != NULL;
		    opcodep++) {
		    int level_of_match;

		    if (disdata->distype == cris_dis_v32) {
			    switch (opcodep->applicable_version) {
			    case cris_ver_version_all:
				    break;

			    case cris_ver_v0_3:
			    case cris_ver_v0_10:
			    case cris_ver_v3_10:
			    case cris_ver_sim_v0_10:
			    case cris_ver_v8_10:
			    case cris_ver_v10:
			    case cris_ver_warning:
				    continue;

			    case cris_ver_v3p:
			    case cris_ver_v8p:
			    case cris_ver_v10p:
			    case cris_ver_v32p:
				    break;

			    case cris_ver_v8:
				    abort ();
			    default:
				    abort ();
			    }
		    } else {
			    switch (opcodep->applicable_version) {
			    case cris_ver_version_all:
			    case cris_ver_v0_3:
			    case cris_ver_v3p:
			    case cris_ver_v0_10:
			    case cris_ver_v8p:
			    case cris_ver_v8_10:
			    case cris_ver_v10:
			    case cris_ver_sim_v0_10:
			    case cris_ver_v10p:
			    case cris_ver_warning:
				    break;

			    case cris_ver_v32p:
				    continue;

			    case cris_ver_v8:
				    abort ();
			    default:
				    abort ();
			    }
		    }

		    /* We give a double lead for bits matching the template in
	     cris_opcodes.  Not even, because then "move p8,r10" would
	     be given 2 bits lead over "clear.d r10".  When there's a
	     tie, the first entry in the table wins.  This is
	     deliberate, to avoid a more complicated recognition
	     formula.  */
		    if ((opcodep->match & insn) == opcodep->match && (opcodep->lose & insn) == 0 && ((level_of_match = cris_constraint (opcodep->args, insn, prefix_insn, disdata)) >= 0) && ((level_of_match += 2 * number_of_bits (opcodep->match | opcodep->lose)) > max_level_of_match)) {
			    max_matchedp = opcodep;
			    max_level_of_match = level_of_match;

			    /* If there was a full match, never mind looking
			 further.  */
			    if (level_of_match >= 2 * 16) {
				    break;
			    }
		    }
		}
      /* Fill in the new entry.

	 If there are changes to the opcode-table involving prefixes, and
	 disassembly then does not work correctly, try removing the
	 else-clause below that fills in the prefix-table.  If that
	 helps, you need to change the prefix_opc_table setting above, or
	 something related.  */
		if (prefix_insn == NO_CRIS_PREFIX) {
			opc_table[insn] = max_matchedp;
		} else {
			prefix_opc_table[insn] = max_matchedp;
		}
    }

  return max_matchedp;
}