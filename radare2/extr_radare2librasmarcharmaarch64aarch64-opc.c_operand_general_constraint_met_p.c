#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_9__ ;
typedef  struct TYPE_26__   TYPE_8__ ;
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_13__ ;
typedef  struct TYPE_17__   TYPE_10__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int int64_t ;
typedef  enum aarch64_opnd { ____Placeholder_aarch64_opnd } aarch64_opnd ;
typedef  int /*<<< orphan*/  aarch64_opnd_qualifier_t ;
struct TYPE_26__ {int amount; int kind; int /*<<< orphan*/  operator_present; int /*<<< orphan*/  amount_present; } ;
struct TYPE_25__ {int index; int regno; } ;
struct TYPE_24__ {int value; int is_fp; } ;
struct TYPE_23__ {int num_regs; int index; } ;
struct TYPE_21__ {int imm; int is_reg; int regno; } ;
struct TYPE_22__ {int writeback; int preind; TYPE_3__ offset; } ;
struct TYPE_19__ {int regno; } ;
struct TYPE_27__ {scalar_t__ type; int pstatefield; TYPE_8__ shifter; TYPE_7__ reglane; int /*<<< orphan*/  qualifier; TYPE_6__ imm; TYPE_5__ reglist; TYPE_4__ addr; TYPE_2__* cond; TYPE_1__ reg; int /*<<< orphan*/  sysins_op; int /*<<< orphan*/  present; } ;
typedef  TYPE_9__ aarch64_opnd_info ;
typedef  int /*<<< orphan*/  aarch64_operand_error ;
struct TYPE_17__ {scalar_t__* operands; int /*<<< orphan*/  iclass; int /*<<< orphan*/  op; } ;
typedef  TYPE_10__ aarch64_opcode ;
struct TYPE_20__ {int value; } ;
struct TYPE_18__ {int op_class; int flags; } ;

/* Variables and functions */
#define  AARCH64_MOD_LSL 272 
#define  AARCH64_MOD_MSL 271 
 int const AARCH64_MOD_MUL ; 
 int AARCH64_MOD_MUL_VL ; 
 int AARCH64_MOD_NONE ; 
 int const AARCH64_MOD_ROR ; 
#define  AARCH64_MOD_SXTW 270 
#define  AARCH64_MOD_SXTX 269 
#define  AARCH64_MOD_UXTW 268 
 int const AARCH64_MOD_UXTX ; 
#define  AARCH64_OPND_ADDR_OFFSET 267 
#define  AARCH64_OPND_ADDR_PCREL14 266 
#define  AARCH64_OPND_ADDR_PCREL19 265 
#define  AARCH64_OPND_ADDR_PCREL21 264 
#define  AARCH64_OPND_ADDR_PCREL26 263 
#define  AARCH64_OPND_ADDR_REGOFF 262 
#define  AARCH64_OPND_ADDR_SIMM10 261 
#define  AARCH64_OPND_ADDR_SIMM7 260 
#define  AARCH64_OPND_ADDR_SIMM9 259 
#define  AARCH64_OPND_ADDR_SIMM9_2 258 
#define  AARCH64_OPND_ADDR_UIMM12 257 
#define  AARCH64_OPND_AIMM 256 
#define  AARCH64_OPND_CCMP_IMM 255 
#define  AARCH64_OPND_CLASS_ADDRESS 254 
#define  AARCH64_OPND_CLASS_COND 253 
#define  AARCH64_OPND_CLASS_IMMEDIATE 252 
#define  AARCH64_OPND_CLASS_INT_REG 251 
#define  AARCH64_OPND_CLASS_MODIFIED_REG 250 
#define  AARCH64_OPND_CLASS_PRED_REG 249 
#define  AARCH64_OPND_CLASS_SIMD_ELEMENT 248 
#define  AARCH64_OPND_CLASS_SIMD_REGLIST 247 
#define  AARCH64_OPND_CLASS_SVE_REG 246 
#define  AARCH64_OPND_CLASS_SYSTEM 245 
 int AARCH64_OPND_COND1 ; 
#define  AARCH64_OPND_EXCEPTION 244 
 int AARCH64_OPND_Em16 ; 
#define  AARCH64_OPND_FPIMM 243 
#define  AARCH64_OPND_FPIMM0 242 
#define  AARCH64_OPND_HALF 241 
 int AARCH64_OPND_IMM ; 
#define  AARCH64_OPND_IMM0 240 
#define  AARCH64_OPND_IMM_MOV 239 
#define  AARCH64_OPND_IMM_ROT1 238 
#define  AARCH64_OPND_IMM_ROT2 237 
#define  AARCH64_OPND_IMM_ROT3 236 
#define  AARCH64_OPND_IMM_VLSL 235 
#define  AARCH64_OPND_IMM_VLSR 234 
#define  AARCH64_OPND_LEt 233 
#define  AARCH64_OPND_LIMM 232 
#define  AARCH64_OPND_LVt 231 
#define  AARCH64_OPND_LVt_AL 230 
#define  AARCH64_OPND_NZCV 229 
 int AARCH64_OPND_PAIRREG ; 
#define  AARCH64_OPND_PSTATEFIELD 228 
#define  AARCH64_OPND_QLF_LSL 227 
#define  AARCH64_OPND_QLF_MSL 226 
#define  AARCH64_OPND_QLF_NIL 225 
#define  AARCH64_OPND_QLF_SP 224 
 int /*<<< orphan*/  AARCH64_OPND_QLF_S_H ; 
 int /*<<< orphan*/  AARCH64_OPND_QLF_W ; 
#define  AARCH64_OPND_QLF_WSP 223 
 int /*<<< orphan*/  AARCH64_OPND_QLF_X ; 
 int AARCH64_OPND_Rd ; 
#define  AARCH64_OPND_Rm_EXT 222 
#define  AARCH64_OPND_Rm_SFT 221 
 int AARCH64_OPND_Rt_SYS ; 
#define  AARCH64_OPND_SHLL_IMM 220 
#define  AARCH64_OPND_SIMD_ADDR_POST 219 
#define  AARCH64_OPND_SIMD_FPIMM 218 
#define  AARCH64_OPND_SIMD_IMM 217 
#define  AARCH64_OPND_SIMD_IMM_SFT 216 
#define  AARCH64_OPND_SIMM5 215 
#define  AARCH64_OPND_SVE_ADDR_R 214 
#define  AARCH64_OPND_SVE_ADDR_RI_S4x16 213 
#define  AARCH64_OPND_SVE_ADDR_RI_S4x2xVL 212 
#define  AARCH64_OPND_SVE_ADDR_RI_S4x3xVL 211 
#define  AARCH64_OPND_SVE_ADDR_RI_S4x4xVL 210 
#define  AARCH64_OPND_SVE_ADDR_RI_S4xVL 209 
#define  AARCH64_OPND_SVE_ADDR_RI_S6xVL 208 
#define  AARCH64_OPND_SVE_ADDR_RI_S9xVL 207 
#define  AARCH64_OPND_SVE_ADDR_RI_U6 206 
#define  AARCH64_OPND_SVE_ADDR_RI_U6x2 205 
#define  AARCH64_OPND_SVE_ADDR_RI_U6x4 204 
#define  AARCH64_OPND_SVE_ADDR_RI_U6x8 203 
#define  AARCH64_OPND_SVE_ADDR_RR 202 
#define  AARCH64_OPND_SVE_ADDR_RR_LSL1 201 
#define  AARCH64_OPND_SVE_ADDR_RR_LSL2 200 
#define  AARCH64_OPND_SVE_ADDR_RR_LSL3 199 
#define  AARCH64_OPND_SVE_ADDR_RX 198 
#define  AARCH64_OPND_SVE_ADDR_RX_LSL1 197 
#define  AARCH64_OPND_SVE_ADDR_RX_LSL2 196 
#define  AARCH64_OPND_SVE_ADDR_RX_LSL3 195 
#define  AARCH64_OPND_SVE_ADDR_RZ 194 
#define  AARCH64_OPND_SVE_ADDR_RZ_LSL1 193 
#define  AARCH64_OPND_SVE_ADDR_RZ_LSL2 192 
#define  AARCH64_OPND_SVE_ADDR_RZ_LSL3 191 
#define  AARCH64_OPND_SVE_ADDR_RZ_XTW1_14 190 
#define  AARCH64_OPND_SVE_ADDR_RZ_XTW1_22 189 
#define  AARCH64_OPND_SVE_ADDR_RZ_XTW2_14 188 
#define  AARCH64_OPND_SVE_ADDR_RZ_XTW2_22 187 
#define  AARCH64_OPND_SVE_ADDR_RZ_XTW3_14 186 
#define  AARCH64_OPND_SVE_ADDR_RZ_XTW3_22 185 
#define  AARCH64_OPND_SVE_ADDR_RZ_XTW_14 184 
#define  AARCH64_OPND_SVE_ADDR_RZ_XTW_22 183 
#define  AARCH64_OPND_SVE_ADDR_ZI_U5 182 
#define  AARCH64_OPND_SVE_ADDR_ZI_U5x2 181 
#define  AARCH64_OPND_SVE_ADDR_ZI_U5x4 180 
#define  AARCH64_OPND_SVE_ADDR_ZI_U5x8 179 
#define  AARCH64_OPND_SVE_ADDR_ZZ_LSL 178 
#define  AARCH64_OPND_SVE_ADDR_ZZ_SXTW 177 
#define  AARCH64_OPND_SVE_ADDR_ZZ_UXTW 176 
#define  AARCH64_OPND_SVE_AIMM 175 
#define  AARCH64_OPND_SVE_ASIMM 174 
#define  AARCH64_OPND_SVE_FPIMM8 173 
#define  AARCH64_OPND_SVE_I1_HALF_ONE 172 
#define  AARCH64_OPND_SVE_I1_HALF_TWO 171 
#define  AARCH64_OPND_SVE_I1_ZERO_ONE 170 
#define  AARCH64_OPND_SVE_IMM_ROT1 169 
#define  AARCH64_OPND_SVE_IMM_ROT2 168 
#define  AARCH64_OPND_SVE_INV_LIMM 167 
#define  AARCH64_OPND_SVE_LIMM 166 
#define  AARCH64_OPND_SVE_LIMM_MOV 165 
#define  AARCH64_OPND_SVE_PATTERN_SCALED 164 
#define  AARCH64_OPND_SVE_SHLIMM_PRED 163 
#define  AARCH64_OPND_SVE_SHLIMM_UNPRED 162 
#define  AARCH64_OPND_SVE_SHRIMM_PRED 161 
#define  AARCH64_OPND_SVE_SHRIMM_UNPRED 160 
#define  AARCH64_OPND_SVE_SIMM5 159 
#define  AARCH64_OPND_SVE_SIMM5B 158 
#define  AARCH64_OPND_SVE_SIMM6 157 
#define  AARCH64_OPND_SVE_SIMM8 156 
#define  AARCH64_OPND_SVE_UIMM3 155 
#define  AARCH64_OPND_SVE_UIMM7 154 
#define  AARCH64_OPND_SVE_UIMM8 153 
#define  AARCH64_OPND_SVE_UIMM8_53 152 
#define  AARCH64_OPND_SVE_Zm3_22_INDEX 151 
#define  AARCH64_OPND_SVE_Zm3_INDEX 150 
#define  AARCH64_OPND_SVE_Zm4_INDEX 149 
#define  AARCH64_OPND_SVE_Zn_INDEX 148 
#define  AARCH64_OPND_SVE_ZnxN 147 
#define  AARCH64_OPND_SVE_ZtxN 146 
#define  AARCH64_OPND_UIMM3_OP1 145 
#define  AARCH64_OPND_UIMM3_OP2 144 
#define  AARCH64_OPND_UIMM4 143 
#define  AARCH64_OPND_UIMM7 142 
#define  AARCH64_OPND_WIDTH 141 
 int OPD_F_NO_ZR ; 
 int /*<<< orphan*/  OP_BIC ; 
 int /*<<< orphan*/  OP_FCMLA_ELEM ; 
#define  OP_MOV_IMM_LOG 140 
#define  OP_MOV_IMM_WIDE 139 
#define  OP_MOV_IMM_WIDEN 138 
 int /*<<< orphan*/ * _ (char*) ; 
 int /*<<< orphan*/  aarch64_extend_operator_p (int const) ; 
 int aarch64_get_operand_class (int) ; 
 unsigned int aarch64_get_qualifier_esize (int /*<<< orphan*/ ) ; 
 int aarch64_get_qualifier_nelem (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aarch64_logical_immediate_p (int,int,int /*<<< orphan*/ *) ; 
 TYPE_13__* aarch64_operands ; 
 int /*<<< orphan*/  aarch64_shift_operator_p (int const) ; 
 int /*<<< orphan*/  aarch64_shrink_expanded_imm8 (int) ; 
 int /*<<< orphan*/  aarch64_stack_pointer_p (TYPE_9__ const*) ; 
 int /*<<< orphan*/  aarch64_sve_dupm_mov_immediate_p (int,int) ; 
 int /*<<< orphan*/  aarch64_sys_ins_reg_has_xt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aarch64_wide_constant_p (int,int,int /*<<< orphan*/ *) ; 
#define  asisdlsep 137 
#define  asisdlsop 136 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ get_logsz (unsigned char) ; 
 int get_lower_bound (int /*<<< orphan*/ ) ; 
 int get_opcode_dependent_value (TYPE_10__ const*) ; 
 int get_operand_fields_width (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_operand_from_code (int) ; 
 int get_operand_specific_data (TYPE_13__*) ; 
 int get_upper_bound (int /*<<< orphan*/ ) ; 
#define  ldst_imm10 135 
#define  ldst_imm9 134 
#define  ldst_pos 133 
#define  ldst_unpriv 132 
#define  ldst_unscaled 131 
#define  ldstnapair_offs 130 
#define  ldstpair_indexed 129 
#define  ldstpair_off 128 
 int /*<<< orphan*/  log_shift ; 
 int /*<<< orphan*/  operand_need_shift_by_two (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qualifier_value_in_range_constraint_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_elem_idx_out_of_range_error (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  set_imm_out_of_range_error (int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  set_multiplier_out_of_range_error (int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  set_offset_out_of_range_error (int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  set_other_error (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_reg_list_error (int /*<<< orphan*/ *,int,unsigned int) ; 
 int /*<<< orphan*/  set_regno_out_of_range_error (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_sft_amount_out_of_range_error (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  set_syntax_error (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_unaligned_error (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  value_aligned_p (int,int) ; 
 int /*<<< orphan*/  value_fit_signed_field_p (int,unsigned char) ; 
 int /*<<< orphan*/  value_fit_unsigned_field_p (int,unsigned char) ; 
 int /*<<< orphan*/  value_in_range_p (int,int,unsigned int) ; 

__attribute__((used)) static int
operand_general_constraint_met_p (const aarch64_opnd_info *opnds, int idx,
				  enum aarch64_opnd type,
				  const aarch64_opcode *opcode,
				  aarch64_operand_error *mismatch_detail)
{
  unsigned num, modifiers, shift;
  unsigned char size;
  int64_t imm, min_value, max_value;
  uint64_t uvalue, mask;
  const aarch64_opnd_info *opnd = opnds + idx;
  aarch64_opnd_qualifier_t qualifier = opnd->qualifier;

  assert (opcode->operands[idx] == opnd->type && opnd->type == type);

  switch (aarch64_operands[type].op_class)
    {
    case AARCH64_OPND_CLASS_INT_REG:
      /* Check pair reg constraints for cas* instructions.  */
      if (type == AARCH64_OPND_PAIRREG)
	{
	  assert (idx == 1 || idx == 3);
	  if (opnds[idx - 1].reg.regno % 2 != 0)
	    {
	      set_syntax_error (mismatch_detail, idx - 1,
				_("reg pair must start from even reg"));
	      return 0;
	    }
	  if (opnds[idx].reg.regno != opnds[idx - 1].reg.regno + 1)
	    {
	      set_syntax_error (mismatch_detail, idx,
				_("reg pair must be contiguous"));
	      return 0;
	    }
	  break;
	}

      /* <Xt> may be optional in some IC and TLBI instructions.  */
      if (type == AARCH64_OPND_Rt_SYS)
	{
	  assert (idx == 1 && (aarch64_get_operand_class (opnds[0].type)
			       == AARCH64_OPND_CLASS_SYSTEM));
	  if (opnds[1].present
	      && !aarch64_sys_ins_reg_has_xt (opnds[0].sysins_op))
	    {
	      set_other_error (mismatch_detail, idx, _("extraneous register"));
	      return 0;
	    }
	  if (!opnds[1].present
	      && aarch64_sys_ins_reg_has_xt (opnds[0].sysins_op))
	    {
	      set_other_error (mismatch_detail, idx, _("missing register"));
	      return 0;
	    }
	}
      switch (qualifier)
	{
	case AARCH64_OPND_QLF_WSP:
	case AARCH64_OPND_QLF_SP:
	  if (!aarch64_stack_pointer_p (opnd))
	    {
	      set_other_error (mismatch_detail, idx,
			       _("stack pointer register expected"));
	      return 0;
	    }
	  break;
	default:
	  break;
	}
      break;

    case AARCH64_OPND_CLASS_SVE_REG:
      switch (type)
	{
	case AARCH64_OPND_SVE_Zm3_INDEX:
	case AARCH64_OPND_SVE_Zm3_22_INDEX:
	case AARCH64_OPND_SVE_Zm4_INDEX:
	  size = get_operand_fields_width (get_operand_from_code (type));
	  shift = get_operand_specific_data (&aarch64_operands[type]);
	  mask = (1 << shift) - 1;
	  if (opnd->reg.regno > mask)
	    {
	      assert (mask == 7 || mask == 15);
	      set_other_error (mismatch_detail, idx,
			       mask == 15
			       ? _("z0-z15 expected")
			       : _("z0-z7 expected"));
	      return 0;
	    }
	  mask = (1 << (size - shift)) - 1;
	  if (!value_in_range_p (opnd->reglane.index, 0, mask))
	    {
	      set_elem_idx_out_of_range_error (mismatch_detail, idx, 0, mask);
	      return 0;
	    }
	  break;

	case AARCH64_OPND_SVE_Zn_INDEX:
	  size = aarch64_get_qualifier_esize (opnd->qualifier);
	  if (!value_in_range_p (opnd->reglane.index, 0, 64 / size - 1))
	    {
	      set_elem_idx_out_of_range_error (mismatch_detail, idx,
					       0, 64 / size - 1);
	      return 0;
	    }
	  break;

	case AARCH64_OPND_SVE_ZnxN:
	case AARCH64_OPND_SVE_ZtxN:
	  if (opnd->reglist.num_regs != get_opcode_dependent_value (opcode))
	    {
	      set_other_error (mismatch_detail, idx,
			       _("invalid register list"));
	      return 0;
	    }
	  break;

	default:
	  break;
	}
      break;

    case AARCH64_OPND_CLASS_PRED_REG:
      if (opnd->reg.regno >= 8
	  && get_operand_fields_width (get_operand_from_code (type)) == 3)
	{
	  set_other_error (mismatch_detail, idx, _("p0-p7 expected"));
	  return 0;
	}
      break;

    case AARCH64_OPND_CLASS_COND:
      if (type == AARCH64_OPND_COND1
	  && (opnds[idx].cond->value & 0xe) == 0xe)
	{
	  /* Not allow AL or NV.  */
	  set_syntax_error (mismatch_detail, idx, NULL);
	}
      break;

    case AARCH64_OPND_CLASS_ADDRESS:
      /* Check writeback.  */
      switch (opcode->iclass)
	{
	case ldst_pos:
	case ldst_unscaled:
	case ldstnapair_offs:
	case ldstpair_off:
	case ldst_unpriv:
	  if (opnd->addr.writeback == 1)
	    {
	      set_syntax_error (mismatch_detail, idx,
				_("unexpected address writeback"));
	      return 0;
	    }
	  break;
	case ldst_imm10:
	  if (opnd->addr.writeback == 1 && opnd->addr.preind != 1)
	    {
	      set_syntax_error (mismatch_detail, idx,
				_("unexpected address writeback"));
	      return 0;
	    }
	  break;
	case ldst_imm9:
	case ldstpair_indexed:
	case asisdlsep:
	case asisdlsop:
	  if (opnd->addr.writeback == 0)
	    {
	      set_syntax_error (mismatch_detail, idx,
				_("address writeback expected"));
	      return 0;
	    }
	  break;
	default:
	  assert (opnd->addr.writeback == 0);
	  break;
	}
      switch (type)
	{
	case AARCH64_OPND_ADDR_SIMM7:
	  /* Scaled signed 7 bits immediate offset.  */
	  /* Get the size of the data element that is accessed, which may be
	     different from that of the source register size,
	     e.g. in strb/ldrb.  */
	  size = aarch64_get_qualifier_esize (opnd->qualifier);
	  if (!value_in_range_p (opnd->addr.offset.imm, -64 * size, 63 * size))
	    {
	      set_offset_out_of_range_error (mismatch_detail, idx,
					     -64 * size, 63 * size);
	      return 0;
	    }
	  if (!value_aligned_p (opnd->addr.offset.imm, size))
	    {
	      set_unaligned_error (mismatch_detail, idx, size);
	      return 0;
	    }
	  break;
	case AARCH64_OPND_ADDR_OFFSET:
	case AARCH64_OPND_ADDR_SIMM9:
	  /* Unscaled signed 9 bits immediate offset.  */
	  if (!value_in_range_p (opnd->addr.offset.imm, -256, 255))
	    {
	      set_offset_out_of_range_error (mismatch_detail, idx, -256, 255);
	      return 0;
	    }
	  break;

	case AARCH64_OPND_ADDR_SIMM9_2:
	  /* Unscaled signed 9 bits immediate offset, which has to be negative
	     or unaligned.  */
	  size = aarch64_get_qualifier_esize (qualifier);
	  if ((value_in_range_p (opnd->addr.offset.imm, 0, 255)
	       && !value_aligned_p (opnd->addr.offset.imm, size))
	      || value_in_range_p (opnd->addr.offset.imm, -256, -1))
	    return 1;
	  set_other_error (mismatch_detail, idx,
			   _("negative or unaligned offset expected"));
	  return 0;

	case AARCH64_OPND_ADDR_SIMM10:
	  /* Scaled signed 10 bits immediate offset.  */
	  if (!value_in_range_p (opnd->addr.offset.imm, -4096, 4088))
	    {
	      set_offset_out_of_range_error (mismatch_detail, idx, -4096, 4088);
	      return 0;
	    }
	  if (!value_aligned_p (opnd->addr.offset.imm, 8))
	    {
	      set_unaligned_error (mismatch_detail, idx, 8);
	      return 0;
	    }
	  break;

	case AARCH64_OPND_SIMD_ADDR_POST:
	  /* AdvSIMD load/store multiple structures, post-index.  */
	  assert (idx == 1);
	  if (opnd->addr.offset.is_reg)
	    {
	      if (value_in_range_p (opnd->addr.offset.regno, 0, 30))
		return 1;
	      else
		{
		  set_other_error (mismatch_detail, idx,
				   _("invalid register offset"));
		  return 0;
		}
	    }
	  else
	    {
	      const aarch64_opnd_info *prev = &opnds[idx-1];
	      unsigned num_bytes; /* total number of bytes transferred.  */
	      /* The opcode dependent area stores the number of elements in
		 each structure to be loaded/stored.  */
	      int is_ld1r = get_opcode_dependent_value (opcode) == 1;
	      if (opcode->operands[0] == AARCH64_OPND_LVt_AL)
		/* Special handling of loading single structure to all lane.  */
		num_bytes = (is_ld1r ? 1 : prev->reglist.num_regs)
		  * aarch64_get_qualifier_esize (prev->qualifier);
	      else
		num_bytes = prev->reglist.num_regs
		  * aarch64_get_qualifier_esize (prev->qualifier)
		  * aarch64_get_qualifier_nelem (prev->qualifier);
	      if ((int) num_bytes != opnd->addr.offset.imm)
		{
		  set_other_error (mismatch_detail, idx,
				   _("invalid post-increment amount"));
		  return 0;
		}
	    }
	  break;

	case AARCH64_OPND_ADDR_REGOFF:
	  /* Get the size of the data element that is accessed, which may be
	     different from that of the source register size,
	     e.g. in strb/ldrb.  */
	  size = aarch64_get_qualifier_esize (opnd->qualifier);
	  /* It is either no shift or shift by the binary logarithm of SIZE.  */
	  if (opnd->shifter.amount != 0
	      && opnd->shifter.amount != (int)get_logsz (size))
	    {
	      set_other_error (mismatch_detail, idx,
			       _("invalid shift amount"));
	      return 0;
	    }
	  /* Only UXTW, LSL, SXTW and SXTX are the accepted extending
	     operators.  */
	  switch (opnd->shifter.kind)
	    {
	    case AARCH64_MOD_UXTW:
	    case AARCH64_MOD_LSL:
	    case AARCH64_MOD_SXTW:
	    case AARCH64_MOD_SXTX: break;
	    default:
	      set_other_error (mismatch_detail, idx,
			       _("invalid extend/shift operator"));
	      return 0;
	    }
	  break;

	case AARCH64_OPND_ADDR_UIMM12:
	  imm = opnd->addr.offset.imm;
	  /* Get the size of the data element that is accessed, which may be
	     different from that of the source register size,
	     e.g. in strb/ldrb.  */
	  size = aarch64_get_qualifier_esize (qualifier);
	  if (!value_in_range_p (opnd->addr.offset.imm, 0, 4095 * size))
	    {
	      set_offset_out_of_range_error (mismatch_detail, idx,
					     0, 4095 * size);
	      return 0;
	    }
	  if (!value_aligned_p (opnd->addr.offset.imm, size))
	    {
	      set_unaligned_error (mismatch_detail, idx, size);
	      return 0;
	    }
	  break;

	case AARCH64_OPND_ADDR_PCREL14:
	case AARCH64_OPND_ADDR_PCREL19:
	case AARCH64_OPND_ADDR_PCREL21:
	case AARCH64_OPND_ADDR_PCREL26:
	  imm = opnd->imm.value;
	  if (operand_need_shift_by_two (get_operand_from_code (type)))
	    {
	      /* The offset value in a PC-relative branch instruction is alway
		 4-byte aligned and is encoded without the lowest 2 bits.  */
	      if (!value_aligned_p (imm, 4))
		{
		  set_unaligned_error (mismatch_detail, idx, 4);
		  return 0;
		}
	      /* Right shift by 2 so that we can carry out the following check
		 canonically.  */
	      imm >>= 2;
	    }
	  size = get_operand_fields_width (get_operand_from_code (type));
	  if (!value_fit_signed_field_p (imm, size))
	    {
	      set_other_error (mismatch_detail, idx,
			       _("immediate out of range"));
	      return 0;
	    }
	  break;

	case AARCH64_OPND_SVE_ADDR_RI_S4xVL:
	case AARCH64_OPND_SVE_ADDR_RI_S4x2xVL:
	case AARCH64_OPND_SVE_ADDR_RI_S4x3xVL:
	case AARCH64_OPND_SVE_ADDR_RI_S4x4xVL:
	  min_value = -8;
	  max_value = 7;
	sve_imm_offset_vl:
	  assert (!opnd->addr.offset.is_reg);
	  assert (opnd->addr.preind);
	  num = 1 + get_operand_specific_data (&aarch64_operands[type]);
	  min_value *= num;
	  max_value *= num;
	  if ((opnd->addr.offset.imm != 0 && !opnd->shifter.operator_present)
	      || (opnd->shifter.operator_present
		  && opnd->shifter.kind != AARCH64_MOD_MUL_VL))
	    {
	      set_other_error (mismatch_detail, idx,
			       _("invalid addressing mode"));
	      return 0;
	    }
	  if (!value_in_range_p (opnd->addr.offset.imm, min_value, max_value))
	    {
	      set_offset_out_of_range_error (mismatch_detail, idx,
					     min_value, max_value);
	      return 0;
	    }
	  if (!value_aligned_p (opnd->addr.offset.imm, num))
	    {
	      set_unaligned_error (mismatch_detail, idx, num);
	      return 0;
	    }
	  break;

	case AARCH64_OPND_SVE_ADDR_RI_S6xVL:
	  min_value = -32;
	  max_value = 31;
	  goto sve_imm_offset_vl;

	case AARCH64_OPND_SVE_ADDR_RI_S9xVL:
	  min_value = -256;
	  max_value = 255;
	  goto sve_imm_offset_vl;

	case AARCH64_OPND_SVE_ADDR_RI_U6:
	case AARCH64_OPND_SVE_ADDR_RI_U6x2:
	case AARCH64_OPND_SVE_ADDR_RI_U6x4:
	case AARCH64_OPND_SVE_ADDR_RI_U6x8:
	  min_value = 0;
	  max_value = 63;
	sve_imm_offset:
	  assert (!opnd->addr.offset.is_reg);
	  assert (opnd->addr.preind);
	  num = 1 << get_operand_specific_data (&aarch64_operands[type]);
	  min_value *= num;
	  max_value *= num;
	  if (opnd->shifter.operator_present
	      || opnd->shifter.amount_present)
	    {
	      set_other_error (mismatch_detail, idx,
			       _("invalid addressing mode"));
	      return 0;
	    }
	  if (!value_in_range_p (opnd->addr.offset.imm, min_value, max_value))
	    {
	      set_offset_out_of_range_error (mismatch_detail, idx,
					     min_value, max_value);
	      return 0;
	    }
	  if (!value_aligned_p (opnd->addr.offset.imm, num))
	    {
	      set_unaligned_error (mismatch_detail, idx, num);
	      return 0;
	    }
	  break;

	case AARCH64_OPND_SVE_ADDR_RI_S4x16:
	  min_value = -8;
	  max_value = 7;
	  goto sve_imm_offset;

	case AARCH64_OPND_SVE_ADDR_R:
	case AARCH64_OPND_SVE_ADDR_RR:
	case AARCH64_OPND_SVE_ADDR_RR_LSL1:
	case AARCH64_OPND_SVE_ADDR_RR_LSL2:
	case AARCH64_OPND_SVE_ADDR_RR_LSL3:
	case AARCH64_OPND_SVE_ADDR_RX:
	case AARCH64_OPND_SVE_ADDR_RX_LSL1:
	case AARCH64_OPND_SVE_ADDR_RX_LSL2:
	case AARCH64_OPND_SVE_ADDR_RX_LSL3:
	case AARCH64_OPND_SVE_ADDR_RZ:
	case AARCH64_OPND_SVE_ADDR_RZ_LSL1:
	case AARCH64_OPND_SVE_ADDR_RZ_LSL2:
	case AARCH64_OPND_SVE_ADDR_RZ_LSL3:
	  modifiers = 1 << AARCH64_MOD_LSL;
	sve_rr_operand:
	  assert (opnd->addr.offset.is_reg);
	  assert (opnd->addr.preind);
	  if ((aarch64_operands[type].flags & OPD_F_NO_ZR) != 0
	      && opnd->addr.offset.regno == 31)
	    {
	      set_other_error (mismatch_detail, idx,
			       _("index register xzr is not allowed"));
	      return 0;
	    }
	  if (((1 << opnd->shifter.kind) & modifiers) == 0
	      || (opnd->shifter.amount
		  != get_operand_specific_data (&aarch64_operands[type])))
	    {
	      set_other_error (mismatch_detail, idx,
			       _("invalid addressing mode"));
	      return 0;
	    }
	  break;

	case AARCH64_OPND_SVE_ADDR_RZ_XTW_14:
	case AARCH64_OPND_SVE_ADDR_RZ_XTW_22:
	case AARCH64_OPND_SVE_ADDR_RZ_XTW1_14:
	case AARCH64_OPND_SVE_ADDR_RZ_XTW1_22:
	case AARCH64_OPND_SVE_ADDR_RZ_XTW2_14:
	case AARCH64_OPND_SVE_ADDR_RZ_XTW2_22:
	case AARCH64_OPND_SVE_ADDR_RZ_XTW3_14:
	case AARCH64_OPND_SVE_ADDR_RZ_XTW3_22:
	  modifiers = (1 << AARCH64_MOD_SXTW) | (1 << AARCH64_MOD_UXTW);
	  goto sve_rr_operand;

	case AARCH64_OPND_SVE_ADDR_ZI_U5:
	case AARCH64_OPND_SVE_ADDR_ZI_U5x2:
	case AARCH64_OPND_SVE_ADDR_ZI_U5x4:
	case AARCH64_OPND_SVE_ADDR_ZI_U5x8:
	  min_value = 0;
	  max_value = 31;
	  goto sve_imm_offset;

	case AARCH64_OPND_SVE_ADDR_ZZ_LSL:
	  modifiers = 1 << AARCH64_MOD_LSL;
	sve_zz_operand:
	  assert (opnd->addr.offset.is_reg);
	  assert (opnd->addr.preind);
	  if (((1 << opnd->shifter.kind) & modifiers) == 0
	      || opnd->shifter.amount < 0
	      || opnd->shifter.amount > 3)
	    {
	      set_other_error (mismatch_detail, idx,
			       _("invalid addressing mode"));
	      return 0;
	    }
	  break;

	case AARCH64_OPND_SVE_ADDR_ZZ_SXTW:
	  modifiers = (1 << AARCH64_MOD_SXTW);
	  goto sve_zz_operand;

	case AARCH64_OPND_SVE_ADDR_ZZ_UXTW:
	  modifiers = 1 << AARCH64_MOD_UXTW;
	  goto sve_zz_operand;

	default:
	  break;
	}
      break;

    case AARCH64_OPND_CLASS_SIMD_REGLIST:
      if (type == AARCH64_OPND_LEt)
	{
	  /* Get the upper bound for the element index.  */
	  num = 16 / aarch64_get_qualifier_esize (qualifier) - 1;
	  if (!value_in_range_p (opnd->reglist.index, 0, num))
	    {
	      set_elem_idx_out_of_range_error (mismatch_detail, idx, 0, num);
	      return 0;
	    }
	}
      /* The opcode dependent area stores the number of elements in
	 each structure to be loaded/stored.  */
      num = get_opcode_dependent_value (opcode);
      switch (type)
	{
	case AARCH64_OPND_LVt:
	  assert (num >= 1 && num <= 4);
	  /* Unless LD1/ST1, the number of registers should be equal to that
	     of the structure elements.  */
	  if (num != 1 && opnd->reglist.num_regs != num)
	    {
	      set_reg_list_error (mismatch_detail, idx, num);
	      return 0;
	    }
	  break;
	case AARCH64_OPND_LVt_AL:
	case AARCH64_OPND_LEt:
	  assert (num >= 1 && num <= 4);
	  /* The number of registers should be equal to that of the structure
	     elements.  */
	  if (opnd->reglist.num_regs != num)
	    {
	      set_reg_list_error (mismatch_detail, idx, num);
	      return 0;
	    }
	  break;
	default:
	  break;
	}
      break;

    case AARCH64_OPND_CLASS_IMMEDIATE:
      /* Constraint check on immediate operand.  */
      imm = opnd->imm.value;
      /* E.g. imm_0_31 constrains value to be 0..31.  */
      if (qualifier_value_in_range_constraint_p (qualifier)
	  && !value_in_range_p (imm, get_lower_bound (qualifier),
				get_upper_bound (qualifier)))
	{
	  set_imm_out_of_range_error (mismatch_detail, idx,
				      get_lower_bound (qualifier),
				      get_upper_bound (qualifier));
	  return 0;
	}

      switch (type)
	{
	case AARCH64_OPND_AIMM:
	  if (opnd->shifter.kind != AARCH64_MOD_LSL)
	    {
	      set_other_error (mismatch_detail, idx,
			       _("invalid shift operator"));
	      return 0;
	    }
	  if (opnd->shifter.amount != 0 && opnd->shifter.amount != 12)
	    {
	      set_other_error (mismatch_detail, idx,
			       _("shift amount must be 0 or 12"));
	      return 0;
	    }
	  if (!value_fit_unsigned_field_p (opnd->imm.value, 12))
	    {
	      set_other_error (mismatch_detail, idx,
			       _("immediate out of range"));
	      return 0;
	    }
	  break;

	case AARCH64_OPND_HALF:
	  assert (idx == 1 && opnds[0].type == AARCH64_OPND_Rd);
	  if (opnd->shifter.kind != AARCH64_MOD_LSL)
	    {
	      set_other_error (mismatch_detail, idx,
			       _("invalid shift operator"));
	      return 0;
	    }
	  size = aarch64_get_qualifier_esize (opnds[0].qualifier);
	  if (!value_aligned_p (opnd->shifter.amount, 16))
	    {
	      set_other_error (mismatch_detail, idx,
			       _("shift amount must be a multiple of 16"));
	      return 0;
	    }
	  if (!value_in_range_p (opnd->shifter.amount, 0, size * 8 - 16))
	    {
	      set_sft_amount_out_of_range_error (mismatch_detail, idx,
						 0, size * 8 - 16);
	      return 0;
	    }
	  if (opnd->imm.value < 0)
	    {
	      set_other_error (mismatch_detail, idx,
			       _("negative immediate value not allowed"));
	      return 0;
	    }
	  if (!value_fit_unsigned_field_p (opnd->imm.value, 16))
	    {
	      set_other_error (mismatch_detail, idx,
			       _("immediate out of range"));
	      return 0;
	    }
	  break;

	case AARCH64_OPND_IMM_MOV:
	    {
	      int esize = aarch64_get_qualifier_esize (opnds[0].qualifier);
	      imm = opnd->imm.value;
	      assert (idx == 1);
	      switch (opcode->op)
		{
		case OP_MOV_IMM_WIDEN:
		  imm = ~imm;
		  /* Fall through.  */
		case OP_MOV_IMM_WIDE:
		  if (!aarch64_wide_constant_p (imm, esize == 4, NULL))
		    {
		      set_other_error (mismatch_detail, idx,
				       _("immediate out of range"));
		      return 0;
		    }
		  break;
		case OP_MOV_IMM_LOG:
		  if (!aarch64_logical_immediate_p (imm, esize, NULL))
		    {
		      set_other_error (mismatch_detail, idx,
				       _("immediate out of range"));
		      return 0;
		    }
		  break;
		default:
		  assert (0);
		  return 0;
		}
	    }
	  break;

	case AARCH64_OPND_NZCV:
	case AARCH64_OPND_CCMP_IMM:
	case AARCH64_OPND_EXCEPTION:
	case AARCH64_OPND_UIMM4:
	case AARCH64_OPND_UIMM7:
	case AARCH64_OPND_UIMM3_OP1:
	case AARCH64_OPND_UIMM3_OP2:
	case AARCH64_OPND_SVE_UIMM3:
	case AARCH64_OPND_SVE_UIMM7:
	case AARCH64_OPND_SVE_UIMM8:
	case AARCH64_OPND_SVE_UIMM8_53:
	  size = get_operand_fields_width (get_operand_from_code (type));
	  assert (size < 32);
	  if (!value_fit_unsigned_field_p (opnd->imm.value, size))
	    {
	      set_imm_out_of_range_error (mismatch_detail, idx, 0,
					  (1 << size) - 1);
	      return 0;
	    }
	  break;

	case AARCH64_OPND_SIMM5:
	case AARCH64_OPND_SVE_SIMM5:
	case AARCH64_OPND_SVE_SIMM5B:
	case AARCH64_OPND_SVE_SIMM6:
	case AARCH64_OPND_SVE_SIMM8:
	  size = get_operand_fields_width (get_operand_from_code (type));
	  assert (size < 32);
	  if (!value_fit_signed_field_p (opnd->imm.value, size))
	    {
	      set_imm_out_of_range_error (mismatch_detail, idx,
					  -(1 << (size - 1)),
					  (1 << (size - 1)) - 1);
	      return 0;
	    }
	  break;

	case AARCH64_OPND_WIDTH:
	  assert (idx > 1 && opnds[idx-1].type == AARCH64_OPND_IMM
		  && opnds[0].type == AARCH64_OPND_Rd);
	  size = get_upper_bound (qualifier);
	  if (opnd->imm.value + opnds[idx-1].imm.value > size)
	    /* lsb+width <= reg.size  */
	    {
	      set_imm_out_of_range_error (mismatch_detail, idx, 1,
					  size - opnds[idx-1].imm.value);
	      return 0;
	    }
	  break;

	case AARCH64_OPND_LIMM:
	case AARCH64_OPND_SVE_LIMM:
	  {
	    int esize = aarch64_get_qualifier_esize (opnds[0].qualifier);
	    uint64_t uimm = opnd->imm.value;
	    if (opcode->op == OP_BIC)
	      uimm = ~uimm;
	    if (!aarch64_logical_immediate_p (uimm, esize, NULL))
	      {
		set_other_error (mismatch_detail, idx,
				 _("immediate out of range"));
		return 0;
	      }
	  }
	  break;

	case AARCH64_OPND_IMM0:
	case AARCH64_OPND_FPIMM0:
	  if (opnd->imm.value != 0)
	    {
	      set_other_error (mismatch_detail, idx,
			       _("immediate zero expected"));
	      return 0;
	    }
	  break;

	case AARCH64_OPND_IMM_ROT1:
	case AARCH64_OPND_IMM_ROT2:
	case AARCH64_OPND_SVE_IMM_ROT2:
	  if (opnd->imm.value != 0
	      && opnd->imm.value != 90
	      && opnd->imm.value != 180
	      && opnd->imm.value != 270)
	    {
	      set_other_error (mismatch_detail, idx,
			       _("rotate expected to be 0, 90, 180 or 270"));
	      return 0;
	    }
	  break;

	case AARCH64_OPND_IMM_ROT3:
	case AARCH64_OPND_SVE_IMM_ROT1:
	  if (opnd->imm.value != 90 && opnd->imm.value != 270)
	    {
	      set_other_error (mismatch_detail, idx,
			       _("rotate expected to be 90 or 270"));
	      return 0;
	    }
	  break;

	case AARCH64_OPND_SHLL_IMM:
	  assert (idx == 2);
	  size = 8 * aarch64_get_qualifier_esize (opnds[idx - 1].qualifier);
	  if (opnd->imm.value != size)
	    {
	      set_other_error (mismatch_detail, idx,
			       _("invalid shift amount"));
	      return 0;
	    }
	  break;

	case AARCH64_OPND_IMM_VLSL:
	  size = aarch64_get_qualifier_esize (qualifier);
	  if (!value_in_range_p (opnd->imm.value, 0, size * 8 - 1))
	    {
	      set_imm_out_of_range_error (mismatch_detail, idx, 0,
					  size * 8 - 1);
	      return 0;
	    }
	  break;

	case AARCH64_OPND_IMM_VLSR:
	  size = aarch64_get_qualifier_esize (qualifier);
	  if (!value_in_range_p (opnd->imm.value, 1, size * 8))
	    {
	      set_imm_out_of_range_error (mismatch_detail, idx, 1, size * 8);
	      return 0;
	    }
	  break;

	case AARCH64_OPND_SIMD_IMM:
	case AARCH64_OPND_SIMD_IMM_SFT:
	  /* Qualifier check.  */
	  switch (qualifier)
	    {
	    case AARCH64_OPND_QLF_LSL:
	      if (opnd->shifter.kind != AARCH64_MOD_LSL)
		{
		  set_other_error (mismatch_detail, idx,
				   _("invalid shift operator"));
		  return 0;
		}
	      break;
	    case AARCH64_OPND_QLF_MSL:
	      if (opnd->shifter.kind != AARCH64_MOD_MSL)
		{
		  set_other_error (mismatch_detail, idx,
				   _("invalid shift operator"));
		  return 0;
		}
	      break;
	    case AARCH64_OPND_QLF_NIL:
	      if (opnd->shifter.kind != AARCH64_MOD_NONE)
		{
		  set_other_error (mismatch_detail, idx,
				   _("shift is not permitted"));
		  return 0;
		}
	      break;
	    default:
	      assert (0);
	      return 0;
	    }
	  /* Is the immediate valid?  */
	  assert (idx == 1);
	  if (aarch64_get_qualifier_esize (opnds[0].qualifier) != 8)
	    {
	      /* uimm8 or simm8 */
	      if (!value_in_range_p (opnd->imm.value, -128, 255))
		{
		  set_imm_out_of_range_error (mismatch_detail, idx, -128, 255);
		  return 0;
		}
	    }
	  else if (aarch64_shrink_expanded_imm8 (opnd->imm.value) < 0)
	    {
	      /* uimm64 is not
		 'aaaaaaaabbbbbbbbccccccccddddddddeeeeeeee
		 ffffffffgggggggghhhhhhhh'.  */
	      set_other_error (mismatch_detail, idx,
			       _("invalid value for immediate"));
	      return 0;
	    }
	  /* Is the shift amount valid?  */
	  switch (opnd->shifter.kind)
	    {
	    case AARCH64_MOD_LSL:
	      size = aarch64_get_qualifier_esize (opnds[0].qualifier);
	      if (!value_in_range_p (opnd->shifter.amount, 0, (size - 1) * 8))
		{
		  set_sft_amount_out_of_range_error (mismatch_detail, idx, 0,
						     (size - 1) * 8);
		  return 0;
		}
	      if (!value_aligned_p (opnd->shifter.amount, 8))
		{
		  set_unaligned_error (mismatch_detail, idx, 8);
		  return 0;
		}
	      break;
	    case AARCH64_MOD_MSL:
	      /* Only 8 and 16 are valid shift amount.  */
	      if (opnd->shifter.amount != 8 && opnd->shifter.amount != 16)
		{
		  set_other_error (mismatch_detail, idx,
				   _("shift amount must be 0 or 16"));
		  return 0;
		}
	      break;
	    default:
	      if (opnd->shifter.kind != AARCH64_MOD_NONE)
		{
		  set_other_error (mismatch_detail, idx,
				   _("invalid shift operator"));
		  return 0;
		}
	      break;
	    }
	  break;

	case AARCH64_OPND_FPIMM:
	case AARCH64_OPND_SIMD_FPIMM:
	case AARCH64_OPND_SVE_FPIMM8:
	  if (opnd->imm.is_fp == 0)
	    {
	      set_other_error (mismatch_detail, idx,
			       _("floating-point immediate expected"));
	      return 0;
	    }
	  /* The value is expected to be an 8-bit floating-point constant with
	     sign, 3-bit exponent and normalized 4 bits of precision, encoded
	     in "a:b:c:d:e:f:g:h" or FLD_imm8 (depending on the type of the
	     instruction).  */
	  if (!value_in_range_p (opnd->imm.value, 0, 255))
	    {
	      set_other_error (mismatch_detail, idx,
			       _("immediate out of range"));
	      return 0;
	    }
	  if (opnd->shifter.kind != AARCH64_MOD_NONE)
	    {
	      set_other_error (mismatch_detail, idx,
			       _("invalid shift operator"));
	      return 0;
	    }
	  break;

	case AARCH64_OPND_SVE_AIMM:
	  min_value = 0;
	sve_aimm:
	  assert (opnd->shifter.kind == AARCH64_MOD_LSL);
	  size = aarch64_get_qualifier_esize (opnds[0].qualifier);
	  mask = ~((uint64_t) -1 << (size * 4) << (size * 4));
	  uvalue = opnd->imm.value;
	  shift = opnd->shifter.amount;
	  if (size == 1)
	    {
	      if (shift != 0)
		{
		  set_other_error (mismatch_detail, idx,
				   _("no shift amount allowed for"
				     " 8-bit constants"));
		  return 0;
		}
	    }
	  else
	    {
	      if (shift != 0 && shift != 8)
		{
		  set_other_error (mismatch_detail, idx,
				   _("shift amount must be 0 or 8"));
		  return 0;
		}
	      if (shift == 0 && (uvalue & 0xff) == 0)
		{
		  shift = 8;
		  uvalue = (int64_t) uvalue / 256;
		}
	    }
	  mask >>= shift;
	  if ((uvalue & mask) != uvalue && (uvalue | ~mask) != uvalue)
	    {
	      set_other_error (mismatch_detail, idx,
			       _("immediate too big for element size"));
	      return 0;
	    }
	  uvalue = (uvalue - min_value) & mask;
	  if (uvalue > 0xff)
	    {
	      set_other_error (mismatch_detail, idx,
			       _("invalid arithmetic immediate"));
	      return 0;
	    }
	  break;

	case AARCH64_OPND_SVE_ASIMM:
	  min_value = -128;
	  goto sve_aimm;

	case AARCH64_OPND_SVE_I1_HALF_ONE:
	  assert (opnd->imm.is_fp);
	  if (opnd->imm.value != 0x3f000000 && opnd->imm.value != 0x3f800000)
	    {
	      set_other_error (mismatch_detail, idx,
			       _("floating-point value must be 0.5 or 1.0"));
	      return 0;
	    }
	  break;

	case AARCH64_OPND_SVE_I1_HALF_TWO:
	  assert (opnd->imm.is_fp);
	  if (opnd->imm.value != 0x3f000000 && opnd->imm.value != 0x40000000)
	    {
	      set_other_error (mismatch_detail, idx,
			       _("floating-point value must be 0.5 or 2.0"));
	      return 0;
	    }
	  break;

	case AARCH64_OPND_SVE_I1_ZERO_ONE:
	  assert (opnd->imm.is_fp);
	  if (opnd->imm.value != 0 && opnd->imm.value != 0x3f800000)
	    {
	      set_other_error (mismatch_detail, idx,
			       _("floating-point value must be 0.0 or 1.0"));
	      return 0;
	    }
	  break;

	case AARCH64_OPND_SVE_INV_LIMM:
	  {
	    int esize = aarch64_get_qualifier_esize (opnds[0].qualifier);
	    uint64_t uimm = ~opnd->imm.value;
	    if (!aarch64_logical_immediate_p (uimm, esize, NULL))
	      {
		set_other_error (mismatch_detail, idx,
				 _("immediate out of range"));
		return 0;
	      }
	  }
	  break;

	case AARCH64_OPND_SVE_LIMM_MOV:
	  {
	    int esize = aarch64_get_qualifier_esize (opnds[0].qualifier);
	    uint64_t uimm = opnd->imm.value;
	    if (!aarch64_logical_immediate_p (uimm, esize, NULL))
	      {
		set_other_error (mismatch_detail, idx,
				 _("immediate out of range"));
		return 0;
	      }
	    if (!aarch64_sve_dupm_mov_immediate_p (uimm, esize))
	      {
		set_other_error (mismatch_detail, idx,
				 _("invalid replicated MOV immediate"));
		return 0;
	      }
	  }
	  break;

	case AARCH64_OPND_SVE_PATTERN_SCALED:
	  assert (opnd->shifter.kind == AARCH64_MOD_MUL);
	  if (!value_in_range_p (opnd->shifter.amount, 1, 16))
	    {
	      set_multiplier_out_of_range_error (mismatch_detail, idx, 1, 16);
	      return 0;
	    }
	  break;

	case AARCH64_OPND_SVE_SHLIMM_PRED:
	case AARCH64_OPND_SVE_SHLIMM_UNPRED:
	  size = aarch64_get_qualifier_esize (opnds[idx - 1].qualifier);
	  if (!value_in_range_p (opnd->imm.value, 0, 8 * size - 1))
	    {
	      set_imm_out_of_range_error (mismatch_detail, idx,
					  0, 8 * size - 1);
	      return 0;
	    }
	  break;

	case AARCH64_OPND_SVE_SHRIMM_PRED:
	case AARCH64_OPND_SVE_SHRIMM_UNPRED:
	  size = aarch64_get_qualifier_esize (opnds[idx - 1].qualifier);
	  if (!value_in_range_p (opnd->imm.value, 1, 8 * size))
	    {
	      set_imm_out_of_range_error (mismatch_detail, idx, 1, 8 * size);
	      return 0;
	    }
	  break;

	default:
	  break;
	}
      break;

    case AARCH64_OPND_CLASS_SYSTEM:
      switch (type)
	{
	case AARCH64_OPND_PSTATEFIELD:
	  assert (idx == 0 && opnds[1].type == AARCH64_OPND_UIMM4);
	  /* MSR UAO, #uimm4
	     MSR PAN, #uimm4
	     The immediate must be #0 or #1.  */
	  if ((opnd->pstatefield == 0x03	/* UAO.  */
	       || opnd->pstatefield == 0x04	/* PAN.  */
	       || opnd->pstatefield == 0x1a)	/* DIT.  */
	      && opnds[1].imm.value > 1)
	    {
	      set_imm_out_of_range_error (mismatch_detail, idx, 0, 1);
	      return 0;
	    }
	  /* MSR SPSel, #uimm4
	     Uses uimm4 as a control value to select the stack pointer: if
	     bit 0 is set it selects the current exception level's stack
	     pointer, if bit 0 is clear it selects shared EL0 stack pointer.
	     Bits 1 to 3 of uimm4 are reserved and should be zero.  */
	  if (opnd->pstatefield == 0x05 /* spsel */ && opnds[1].imm.value > 1)
	    {
	      set_imm_out_of_range_error (mismatch_detail, idx, 0, 1);
	      return 0;
	    }
	  break;
	default:
	  break;
	}
      break;

    case AARCH64_OPND_CLASS_SIMD_ELEMENT:
      /* Get the upper bound for the element index.  */
      if (opcode->op == OP_FCMLA_ELEM)
	/* FCMLA index range depends on the vector size of other operands
	   and is halfed because complex numbers take two elements.  */
	num = aarch64_get_qualifier_nelem (opnds[0].qualifier)
	      * aarch64_get_qualifier_esize (opnds[0].qualifier) / 2;
      else
	num = 16;
      num = num / aarch64_get_qualifier_esize (qualifier) - 1;

      /* Index out-of-range.  */
      if (!value_in_range_p (opnd->reglane.index, 0, num))
	{
	  set_elem_idx_out_of_range_error (mismatch_detail, idx, 0, num);
	  return 0;
	}
      /* SMLAL<Q> <Vd>.<Ta>, <Vn>.<Tb>, <Vm>.<Ts>[<index>].
	 <Vm>	Is the vector register (V0-V31) or (V0-V15), whose
	 number is encoded in "size:M:Rm":
	 size	<Vm>
	 00		RESERVED
	 01		0:Rm
	 10		M:Rm
	 11		RESERVED  */
      if (type == AARCH64_OPND_Em16 && qualifier == AARCH64_OPND_QLF_S_H
	  && !value_in_range_p (opnd->reglane.regno, 0, 15))
	{
	  set_regno_out_of_range_error (mismatch_detail, idx, 0, 15);
	  return 0;
	}
      break;

    case AARCH64_OPND_CLASS_MODIFIED_REG:
      assert (idx == 1 || idx == 2);
      switch (type)
	{
	case AARCH64_OPND_Rm_EXT:
	  if (!aarch64_extend_operator_p (opnd->shifter.kind)
	      && opnd->shifter.kind != AARCH64_MOD_LSL)
	    {
	      set_other_error (mismatch_detail, idx,
			       _("extend operator expected"));
	      return 0;
	    }
	  /* It is not optional unless at least one of "Rd" or "Rn" is '11111'
	     (i.e. SP), in which case it defaults to LSL. The LSL alias is
	     only valid when "Rd" or "Rn" is '11111', and is preferred in that
	     case.  */
	  if (!aarch64_stack_pointer_p (opnds + 0)
	      && (idx != 2 || !aarch64_stack_pointer_p (opnds + 1)))
	    {
	      if (!opnd->shifter.operator_present)
		{
		  set_other_error (mismatch_detail, idx,
				   _("missing extend operator"));
		  return 0;
		}
	      else if (opnd->shifter.kind == AARCH64_MOD_LSL)
		{
		  set_other_error (mismatch_detail, idx,
				   _("'LSL' operator not allowed"));
		  return 0;
		}
	    }
	  assert (opnd->shifter.operator_present	/* Default to LSL.  */
		  || opnd->shifter.kind == AARCH64_MOD_LSL);
	  if (!value_in_range_p (opnd->shifter.amount, 0, 4))
	    {
	      set_sft_amount_out_of_range_error (mismatch_detail, idx, 0, 4);
	      return 0;
	    }
	  /* In the 64-bit form, the final register operand is written as Wm
	     for all but the (possibly omitted) UXTX/LSL and SXTX
	     operators.
	     N.B. GAS allows X register to be used with any operator as a
	     programming convenience.  */
	  if (qualifier == AARCH64_OPND_QLF_X
	      && opnd->shifter.kind != AARCH64_MOD_LSL
	      && opnd->shifter.kind != AARCH64_MOD_UXTX
	      && opnd->shifter.kind != AARCH64_MOD_SXTX)
	    {
	      set_other_error (mismatch_detail, idx, _("W register expected"));
	      return 0;
	    }
	  break;

	case AARCH64_OPND_Rm_SFT:
	  /* ROR is not available to the shifted register operand in
	     arithmetic instructions.  */
	  if (!aarch64_shift_operator_p (opnd->shifter.kind))
	    {
	      set_other_error (mismatch_detail, idx,
			       _("shift operator expected"));
	      return 0;
	    }
	  if (opnd->shifter.kind == AARCH64_MOD_ROR
	      && opcode->iclass != log_shift)
	    {
	      set_other_error (mismatch_detail, idx,
			       _("'ROR' operator not allowed"));
	      return 0;
	    }
	  num = qualifier == AARCH64_OPND_QLF_W ? 31 : 63;
	  if (!value_in_range_p (opnd->shifter.amount, 0, num))
	    {
	      set_sft_amount_out_of_range_error (mismatch_detail, idx, 0, num);
	      return 0;
	    }
	  break;

	default:
	  break;
	}
      break;

    default:
      break;
    }

  return 1;
}