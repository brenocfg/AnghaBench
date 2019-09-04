#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  enum aarch64_opnd { ____Placeholder_aarch64_opnd } aarch64_opnd ;
struct TYPE_11__ {int index; int /*<<< orphan*/ * error; int /*<<< orphan*/  kind; } ;
typedef  TYPE_2__ aarch64_operand_error ;
struct TYPE_12__ {TYPE_5__* opcode; TYPE_4__* operands; } ;
typedef  TYPE_3__ aarch64_inst ;
struct TYPE_14__ {int tied_operand; int* operands; } ;
struct TYPE_10__ {scalar_t__ regno; } ;
struct TYPE_13__ {scalar_t__ skip; TYPE_1__ reg; } ;

/* Variables and functions */
 int AARCH64_MAX_OPND_NUM ; 
 int /*<<< orphan*/  AARCH64_OPDE_INVALID_VARIANT ; 
 int /*<<< orphan*/  AARCH64_OPDE_UNTIED_OPERAND ; 
 int AARCH64_OPND_NIL ; 
 int /*<<< orphan*/  DEBUG_TRACE (char*,...) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ match_operands_qualifier (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ operand_general_constraint_met_p (TYPE_4__*,int,int,TYPE_5__*,TYPE_2__*) ; 

int
aarch64_match_operands_constraint (aarch64_inst *inst,
				   aarch64_operand_error *mismatch_detail)
{
  int i;

  DEBUG_TRACE ("enter");

  /* Check for cases where a source register needs to be the same as the
     destination register.  Do this before matching qualifiers since if
     an instruction has both invalid tying and invalid qualifiers,
     the error about qualifiers would suggest several alternative
     instructions that also have invalid tying.  */
  i = inst->opcode->tied_operand;
  if (i > 0 && (inst->operands[0].reg.regno != inst->operands[i].reg.regno))
    {
      if (mismatch_detail)
	{
	  mismatch_detail->kind = AARCH64_OPDE_UNTIED_OPERAND;
	  mismatch_detail->index = i;
	  mismatch_detail->error = NULL;
	}
      return 0;
    }

  /* Match operands' qualifier.
     *INST has already had qualifier establish for some, if not all, of
     its operands; we need to find out whether these established
     qualifiers match one of the qualifier sequence in
     INST->OPCODE->QUALIFIERS_LIST.  If yes, we will assign each operand
     with the corresponding qualifier in such a sequence.
     Only basic operand constraint checking is done here; the more thorough
     constraint checking will carried out by operand_general_constraint_met_p,
     which has be to called after this in order to get all of the operands'
     qualifiers established.  */
  if (match_operands_qualifier (inst, TRUE /* update_p */) == 0)
    {
      DEBUG_TRACE ("FAIL on operand qualifier matching");
      if (mismatch_detail)
	{
	  /* Return an error type to indicate that it is the qualifier
	     matching failure; we don't care about which operand as there
	     are enough information in the opcode table to reproduce it.  */
	  mismatch_detail->kind = AARCH64_OPDE_INVALID_VARIANT;
	  mismatch_detail->index = -1;
	  mismatch_detail->error = NULL;
	}
      return 0;
    }

  /* Match operands' constraint.  */
  for (i = 0; i < AARCH64_MAX_OPND_NUM; ++i)
    {
      enum aarch64_opnd type = inst->opcode->operands[i];
      if (type == AARCH64_OPND_NIL)
	break;
      if (inst->operands[i].skip)
	{
	  DEBUG_TRACE ("skip the incomplete operand %d", i);
	  continue;
	}
      if (operand_general_constraint_met_p (inst->operands, i, type,
					    inst->opcode, mismatch_detail) == 0)
	{
	  DEBUG_TRACE ("FAIL on operand %d", i);
	  return 0;
	}
    }

  DEBUG_TRACE ("PASS");

  return 1;
}