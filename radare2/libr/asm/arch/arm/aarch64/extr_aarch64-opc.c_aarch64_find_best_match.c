#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ aarch64_opnd_qualifier_t ;
typedef  scalar_t__* aarch64_opnd_qualifier_seq_t ;
struct TYPE_5__ {TYPE_2__* operands; int /*<<< orphan*/  opcode; } ;
typedef  TYPE_1__ aarch64_inst ;
struct TYPE_6__ {scalar_t__ qualifier; } ;

/* Variables and functions */
 int AARCH64_MAX_OPND_NUM ; 
 int AARCH64_MAX_QLF_SEQ_NUM ; 
 scalar_t__ AARCH64_OPND_QLF_NIL ; 
 int /*<<< orphan*/  DEBUG_TRACE (char*,...) ; 
 int /*<<< orphan*/  DEBUG_TRACE_IF (int,char*) ; 
 scalar_t__ TRUE ; 
 int aarch64_num_of_operands (int /*<<< orphan*/ ) ; 
 scalar_t__ debug_dump ; 
 int /*<<< orphan*/  dump_match_qualifiers (TYPE_2__*,scalar_t__ const*) ; 
 int /*<<< orphan*/  dump_qualifier_sequence (scalar_t__ const*) ; 
 scalar_t__ empty_qualifier_sequence_p (scalar_t__ const*) ; 
 scalar_t__ operand_also_qualified_p (TYPE_2__*,scalar_t__ const) ; 

int
aarch64_find_best_match (const aarch64_inst *inst,
			 const aarch64_opnd_qualifier_seq_t *qualifiers_list,
			 int stop_at, aarch64_opnd_qualifier_t *ret)
{
  int found = 0;
  int i, num_opnds;
  const aarch64_opnd_qualifier_t *qualifiers;

  num_opnds = aarch64_num_of_operands (inst->opcode);
  if (num_opnds == 0)
    {
      DEBUG_TRACE ("SUCCEED: no operand");
      return 1;
    }

  if (stop_at < 0 || stop_at >= num_opnds)
    stop_at = num_opnds - 1;

  /* For each pattern.  */
  for (i = 0; i < AARCH64_MAX_QLF_SEQ_NUM; ++i, ++qualifiers_list)
    {
      int j;
      qualifiers = *qualifiers_list;

      /* Start as positive.  */
      found = 1;

      DEBUG_TRACE ("%d", i);
#ifdef DEBUG_AARCH64
      if (debug_dump)
	dump_match_qualifiers (inst->operands, qualifiers);
#endif

      /* Most opcodes has much fewer patterns in the list.
	 First NIL qualifier indicates the end in the list.   */
      if (empty_qualifier_sequence_p (qualifiers) == TRUE)
	{
	  DEBUG_TRACE_IF (i == 0, "SUCCEED: empty qualifier list");
	  if (i)
	    found = 0;
	  break;
	}

      for (j = 0; j < num_opnds && j <= stop_at; ++j, ++qualifiers)
	{
	  if (inst->operands[j].qualifier == AARCH64_OPND_QLF_NIL)
	    {
	      /* Either the operand does not have qualifier, or the qualifier
		 for the operand needs to be deduced from the qualifier
		 sequence.
		 In the latter case, any constraint checking related with
		 the obtained qualifier should be done later in
		 operand_general_constraint_met_p.  */
	      continue;
	    }
	  else if (*qualifiers != inst->operands[j].qualifier)
	    {
	      /* Unless the target qualifier can also qualify the operand
		 (which has already had a non-nil qualifier), non-equal
		 qualifiers are generally un-matched.  */
	      if (operand_also_qualified_p (inst->operands + j, *qualifiers))
		continue;
	      else
		{
		  found = 0;
		  break;
		}
	    }
	  else
	    continue;	/* Equal qualifiers are certainly matched.  */
	}

      /* Qualifiers established.  */
      if (found == 1)
	break;
    }

  if (found == 1)
    {
      /* Fill the result in *RET.  */
      int j;
      qualifiers = *qualifiers_list;

      DEBUG_TRACE ("complete qualifiers using list %d", i);
#ifdef DEBUG_AARCH64
      if (debug_dump)
	dump_qualifier_sequence (qualifiers);
#endif

      for (j = 0; j <= stop_at; ++j, ++qualifiers)
	ret[j] = *qualifiers;
      for (; j < AARCH64_MAX_OPND_NUM; ++j)
	ret[j] = AARCH64_OPND_QLF_NIL;

      DEBUG_TRACE ("SUCCESS");
      return 1;
    }

  DEBUG_TRACE ("FAIL");
  return 0;
}