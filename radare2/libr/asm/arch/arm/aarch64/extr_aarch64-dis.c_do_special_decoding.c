#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  enum aarch64_opnd_qualifier { ____Placeholder_aarch64_opnd_qualifier } aarch64_opnd_qualifier ;
struct TYPE_13__ {TYPE_4__* opcode; TYPE_1__* operands; int /*<<< orphan*/  value; int /*<<< orphan*/  cond; } ;
typedef  TYPE_2__ aarch64_inst ;
typedef  int aarch64_insn ;
struct TYPE_14__ {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_3__ aarch64_field ;
struct TYPE_15__ {int flags; int /*<<< orphan*/ * operands; int /*<<< orphan*/  mask; int /*<<< orphan*/  qualifiers_list; } ;
struct TYPE_12__ {void* qualifier; } ;

/* Variables and functions */
 int AARCH64_MAX_QLF_SEQ_NUM ; 
 scalar_t__ AARCH64_OPND_CLASS_INT_REG ; 
 scalar_t__ AARCH64_OPND_CLASS_SIMD_REG ; 
 void* AARCH64_OPND_QLF_S_D ; 
 void* AARCH64_OPND_QLF_S_H ; 
 void* AARCH64_OPND_QLF_S_S ; 
 void* AARCH64_OPND_QLF_W ; 
 void* AARCH64_OPND_QLF_X ; 
 int /*<<< orphan*/  AARCH64_OPND_Rt ; 
 int /*<<< orphan*/  FLD_N ; 
 int /*<<< orphan*/  FLD_Q ; 
 int /*<<< orphan*/  FLD_cond2 ; 
 int /*<<< orphan*/  FLD_imm5 ; 
 int /*<<< orphan*/  FLD_lse_sz ; 
 int /*<<< orphan*/  FLD_opc ; 
 int /*<<< orphan*/  FLD_sf ; 
 int /*<<< orphan*/  FLD_size ; 
 int /*<<< orphan*/  FLD_type ; 
 int F_COND ; 
 int F_FPTYPE ; 
 int F_GPRSIZE_IN_Q ; 
 int F_LDS_SIZE ; 
 int F_LSE_SZ ; 
 int F_MISC ; 
 int F_N ; 
 int F_SF ; 
 int F_SIZEQ ; 
 int F_SSIZE ; 
 int F_T ; 
 scalar_t__ aarch64_get_operand_class (int /*<<< orphan*/ ) ; 
 int aarch64_operand_index (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int decode_sizeq (TYPE_2__*) ; 
 int do_misc_decoding (TYPE_2__*) ; 
 int extract_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int extract_field_2 (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_sub_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,TYPE_3__*) ; 
 int /*<<< orphan*/  get_cond_from_value (int) ; 
 void* get_greg_qualifier_from_value (int) ; 
 int /*<<< orphan*/  get_operand_possible_qualifiers (int,int /*<<< orphan*/ ,int*) ; 
 void* get_qualifier_from_partial_encoding (int,int*,int) ; 
 void* get_sreg_qualifier_from_value (int) ; 
 void* get_vreg_qualifier_from_value (int) ; 
 int select_operand_for_fptype_field_coding (TYPE_4__*) ; 
 int select_operand_for_scalar_size_field_coding (TYPE_4__*) ; 
 int select_operand_for_sf_field_coding (TYPE_4__*) ; 

__attribute__((used)) static int
do_special_decoding (aarch64_inst *inst)
{
  int idx;
  aarch64_insn value;
  /* Condition for truly conditional executed instructions, e.g. b.cond.  */
  if (inst->opcode->flags & F_COND)
    {
      value = extract_field (FLD_cond2, inst->value, 0);
      inst->cond = get_cond_from_value (value);
    }
  /* 'sf' field.  */
  if (inst->opcode->flags & F_SF)
    {
      idx = select_operand_for_sf_field_coding (inst->opcode);
      value = extract_field (FLD_sf, inst->value, 0);
      inst->operands[idx].qualifier = get_greg_qualifier_from_value (value);
      if ((inst->opcode->flags & F_N)
	  && extract_field (FLD_N, inst->value, 0) != value)
	return 0;
    }
  /* 'sf' field.  */
  if (inst->opcode->flags & F_LSE_SZ)
    {
      idx = select_operand_for_sf_field_coding (inst->opcode);
      value = extract_field (FLD_lse_sz, inst->value, 0);
      inst->operands[idx].qualifier = get_greg_qualifier_from_value (value);
    }
  /* size:Q fields.  */
  if (inst->opcode->flags & F_SIZEQ)
    return decode_sizeq (inst);

  if (inst->opcode->flags & F_FPTYPE)
    {
      idx = select_operand_for_fptype_field_coding (inst->opcode);
      value = extract_field (FLD_type, inst->value, 0);
      switch (value)
	{
	case 0: inst->operands[idx].qualifier = AARCH64_OPND_QLF_S_S; break;
	case 1: inst->operands[idx].qualifier = AARCH64_OPND_QLF_S_D; break;
	case 3: inst->operands[idx].qualifier = AARCH64_OPND_QLF_S_H; break;
	default: return 0;
	}
    }

  if (inst->opcode->flags & F_SSIZE)
    {
      /* N.B. some opcodes like FCMGT <V><d>, <V><n>, #0 have the size[1] as part
	 of the base opcode.  */
      aarch64_insn mask;
      enum aarch64_opnd_qualifier candidates[AARCH64_MAX_QLF_SEQ_NUM];
      idx = select_operand_for_scalar_size_field_coding (inst->opcode);
      value = extract_field (FLD_size, inst->value, inst->opcode->mask);
      mask = extract_field (FLD_size, ~inst->opcode->mask, 0);
      /* For most related instruciton, the 'size' field is fully available for
	 operand encoding.  */
      if (mask == 0x3)
	inst->operands[idx].qualifier = get_sreg_qualifier_from_value (value);
      else
	{
	  get_operand_possible_qualifiers (idx, inst->opcode->qualifiers_list,
					   candidates);
	  inst->operands[idx].qualifier
	    = get_qualifier_from_partial_encoding (value, candidates, mask);
	}
    }

  if (inst->opcode->flags & F_T)
    {
      /* Num of consecutive '0's on the right side of imm5<3:0>.  */
      int num = 0;
      unsigned val, Q;
      assert (aarch64_get_operand_class (inst->opcode->operands[0])
	      == AARCH64_OPND_CLASS_SIMD_REG);
      /* imm5<3:0>	q	<t>
	 0000		x	reserved
	 xxx1		0	8b
	 xxx1		1	16b
	 xx10		0	4h
	 xx10		1	8h
	 x100		0	2s
	 x100		1	4s
	 1000		0	reserved
	 1000		1	2d  */
      val = extract_field (FLD_imm5, inst->value, 0);
      while ((val & 0x1) == 0 && ++num <= 3)
	val >>= 1;
      if (num > 3)
	return 0;
      Q = (unsigned) extract_field (FLD_Q, inst->value, inst->opcode->mask);
      inst->operands[0].qualifier =
	get_vreg_qualifier_from_value ((num << 1) | Q);
    }

  if (inst->opcode->flags & F_GPRSIZE_IN_Q)
    {
      /* Use Rt to encode in the case of e.g.
	 STXP <Ws>, <Xt1>, <Xt2>, [<Xn|SP>{,#0}].  */
      idx = aarch64_operand_index (inst->opcode->operands, AARCH64_OPND_Rt);
      if (idx == -1)
	{
	  /* Otherwise use the result operand, which has to be a integer
	     register.  */
	  assert (aarch64_get_operand_class (inst->opcode->operands[0])
		  == AARCH64_OPND_CLASS_INT_REG);
	  idx = 0;
	}
      assert (idx == 0 || idx == 1);
      value = extract_field (FLD_Q, inst->value, 0);
      inst->operands[idx].qualifier = get_greg_qualifier_from_value (value);
    }

  if (inst->opcode->flags & F_LDS_SIZE)
    {
      aarch64_field field = {0, 0};
      assert (aarch64_get_operand_class (inst->opcode->operands[0])
	      == AARCH64_OPND_CLASS_INT_REG);
      gen_sub_field (FLD_opc, 0, 1, &field);
      value = extract_field_2 (&field, inst->value, 0);
      inst->operands[0].qualifier
	= value ? AARCH64_OPND_QLF_W : AARCH64_OPND_QLF_X;
    }

  /* Miscellaneous decoding; done as the last step.  */
  if (inst->opcode->flags & F_MISC)
    return do_misc_decoding (inst);

  return 1;
}