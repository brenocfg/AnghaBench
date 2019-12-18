#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_11__ ;

/* Type definitions */
typedef  enum aarch64_opnd { ____Placeholder_aarch64_opnd } aarch64_opnd ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  aarch64_operand_error ;
typedef  int /*<<< orphan*/  aarch64_operand ;
struct TYPE_15__ {int const mask; int const opcode; scalar_t__* operands; int /*<<< orphan*/  (* verifier ) (TYPE_1__ const*,int const) ;int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ aarch64_opcode ;
struct TYPE_16__ {int value; TYPE_11__* operands; TYPE_1__ const* opcode; } ;
typedef  TYPE_2__ aarch64_inst ;
typedef  int aarch64_insn ;
struct TYPE_14__ {scalar_t__ type; int idx; } ;

/* Variables and functions */
 int AARCH64_MAX_OPND_NUM ; 
 scalar_t__ AARCH64_OPND_NIL ; 
 int /*<<< orphan*/  DEBUG_TRACE (char*,...) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  aarch64_decode_variant_using_iclass (TYPE_2__*) ; 
 int /*<<< orphan*/  aarch64_extract_operand (int /*<<< orphan*/  const*,TYPE_11__*,int const,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int aarch64_match_operands_constraint (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * aarch64_operands ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  determine_disassembling_preference (TYPE_2__*,int /*<<< orphan*/ *) ; 
 scalar_t__ do_special_decoding (TYPE_2__*) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,char,int) ; 
 scalar_t__ opcode_has_special_coder (TYPE_1__ const*) ; 
 scalar_t__ operand_has_extractor (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__ const*,int const) ; 

__attribute__((used)) static bfd_boolean
aarch64_opcode_decode (const aarch64_opcode *opcode, const aarch64_insn code,
		       aarch64_inst *inst, int noaliases_p,
		       aarch64_operand_error *errors)
{
  int i;

  DEBUG_TRACE ("enter with %s", opcode->name);

  assert (opcode && inst);

  /* Clear inst.  */
  memset (inst, '\0', sizeof (aarch64_inst));

  /* Check the base opcode.  */
  if ((code & opcode->mask) != (opcode->opcode & opcode->mask))
    {
      DEBUG_TRACE ("base opcode match FAIL");
      goto decode_fail;
    }

  inst->opcode = opcode;
  inst->value = code;

  /* Assign operand codes and indexes.  */
  for (i = 0; i < AARCH64_MAX_OPND_NUM; ++i)
    {
      if (opcode->operands[i] == AARCH64_OPND_NIL)
	break;
      inst->operands[i].type = opcode->operands[i];
      inst->operands[i].idx = i;
    }

  /* Call the opcode decoder indicated by flags.  */
  if (opcode_has_special_coder (opcode) && do_special_decoding (inst) == 0)
    {
      DEBUG_TRACE ("opcode flag-based decoder FAIL");
      goto decode_fail;
    }

  /* Possibly use the instruction class to determine the correct
     qualifier.  */
  if (!aarch64_decode_variant_using_iclass (inst))
    {
      DEBUG_TRACE ("iclass-based decoder FAIL");
      goto decode_fail;
    }

  /* Call operand decoders.  */
  for (i = 0; i < AARCH64_MAX_OPND_NUM; ++i)
    {
      const aarch64_operand *opnd;
      enum aarch64_opnd type;

      type = opcode->operands[i];
      if (type == AARCH64_OPND_NIL)
	break;
      opnd = &aarch64_operands[type];
      if (operand_has_extractor (opnd)
	  && (! aarch64_extract_operand (opnd, &inst->operands[i], code, inst,
					 errors)))
	{
	  DEBUG_TRACE ("operand decoder FAIL at operand %d", i);
	  goto decode_fail;
	}
    }

  /* If the opcode has a verifier, then check it now.  */
  if (opcode->verifier && ! opcode->verifier (opcode, code))
    {
      DEBUG_TRACE ("operand verifier FAIL");
      goto decode_fail;
    }

  /* Match the qualifiers.  */
  if (aarch64_match_operands_constraint (inst, NULL) == 1)
    {
      /* Arriving here, the CODE has been determined as a valid instruction
	 of OPCODE and *INST has been filled with information of this OPCODE
	 instruction.  Before the return, check if the instruction has any
	 alias and should be disassembled in the form of its alias instead.
	 If the answer is yes, *INST will be updated.  */
      if (!noaliases_p)
	determine_disassembling_preference (inst, errors);
      DEBUG_TRACE ("SUCCESS");
      return TRUE;
    }
  else
    {
      DEBUG_TRACE ("constraint matching FAIL");
    }

decode_fail:
  return FALSE;
}