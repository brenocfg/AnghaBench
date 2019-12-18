#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  enum aarch64_opnd_qualifier { ____Placeholder_aarch64_opnd_qualifier } aarch64_opnd_qualifier ;
typedef  enum aarch64_field_kind { ____Placeholder_aarch64_field_kind } aarch64_field_kind ;
struct TYPE_6__ {int value; TYPE_1__* operands; TYPE_4__* opcode; } ;
typedef  TYPE_2__ aarch64_inst ;
typedef  int aarch64_insn ;
struct TYPE_7__ {scalar_t__ iclass; int mask; int /*<<< orphan*/  qualifiers_list; } ;
struct TYPE_5__ {int qualifier; } ;

/* Variables and functions */
 int AARCH64_MAX_QLF_SEQ_NUM ; 
 int AARCH64_OPND_QLF_NIL ; 
 int /*<<< orphan*/  DEBUG_TRACE (char*,int,...) ; 
 int /*<<< orphan*/  FLD_Q ; 
 int FLD_size ; 
 int FLD_vldst_size ; 
 int aarch64_get_qualifier_name (int) ; 
 int aarch64_select_operand_for_sizeq_field_coding (TYPE_4__*) ; 
 scalar_t__ asisdlse ; 
 scalar_t__ asisdlsep ; 
 scalar_t__ asisdlso ; 
 scalar_t__ asisdlsop ; 
 scalar_t__ debug_dump ; 
 int extract_fields (int,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_operand_possible_qualifiers (int,int /*<<< orphan*/ ,int*) ; 
 int get_qualifier_from_partial_encoding (int,int*,int) ; 
 int get_vreg_qualifier_from_value (int) ; 

__attribute__((used)) static int
decode_sizeq (aarch64_inst *inst)
{
  int idx;
  enum aarch64_opnd_qualifier qualifier;
  aarch64_insn code;
  aarch64_insn value, mask;
  enum aarch64_field_kind fld_sz;
  enum aarch64_opnd_qualifier candidates[AARCH64_MAX_QLF_SEQ_NUM];

  if (inst->opcode->iclass == asisdlse
     || inst->opcode->iclass == asisdlsep
     || inst->opcode->iclass == asisdlso
     || inst->opcode->iclass == asisdlsop)
    fld_sz = FLD_vldst_size;
  else
    fld_sz = FLD_size;

  code = inst->value;
  value = extract_fields (code, inst->opcode->mask, 2, fld_sz, FLD_Q);
  /* Obtain the info that which bits of fields Q and size are actually
     available for operand encoding.  Opcodes like FMAXNM and FMLA have
     size[1] unavailable.  */
  mask = extract_fields (~inst->opcode->mask, 0, 2, fld_sz, FLD_Q);

  /* The index of the operand we are going to tag a qualifier and the qualifer
     itself are reasoned from the value of the size and Q fields and the
     possible valid qualifier lists.  */
  idx = aarch64_select_operand_for_sizeq_field_coding (inst->opcode);
  DEBUG_TRACE ("key idx: %d", idx);

  /* For most related instruciton, size:Q are fully available for operand
     encoding.  */
  if (mask == 0x7)
    {
      inst->operands[idx].qualifier = get_vreg_qualifier_from_value (value);
      return 1;
    }

  get_operand_possible_qualifiers (idx, inst->opcode->qualifiers_list,
				   candidates);
#ifdef DEBUG_AARCH64
  if (debug_dump)
    {
      int i;
      for (i = 0; candidates[i] != AARCH64_OPND_QLF_NIL
	   && i < AARCH64_MAX_QLF_SEQ_NUM; ++i)
	DEBUG_TRACE ("qualifier %d: %s", i,
		     aarch64_get_qualifier_name(candidates[i]));
      DEBUG_TRACE ("%d, %d", (int)value, (int)mask);
    }
#endif /* DEBUG_AARCH64 */

  qualifier = get_qualifier_from_partial_encoding (value, candidates, mask);

  if (qualifier == AARCH64_OPND_QLF_NIL)
    return 0;

  inst->operands[idx].qualifier = qualifier;
  return 1;
}