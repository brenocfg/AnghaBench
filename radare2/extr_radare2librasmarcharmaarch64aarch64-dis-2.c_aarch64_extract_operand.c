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
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  aarch64_opnd_info ;
typedef  int /*<<< orphan*/  aarch64_operand_error ;
typedef  int /*<<< orphan*/  aarch64_operand ;
typedef  int /*<<< orphan*/  aarch64_inst ;
typedef  int /*<<< orphan*/  aarch64_insn ;

/* Variables and functions */
 int /*<<< orphan*/  aarch64_ext_addr_offset (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aarch64_ext_addr_regoff (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aarch64_ext_addr_simm (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aarch64_ext_addr_simm10 (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aarch64_ext_addr_simple (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aarch64_ext_addr_uimm12 (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aarch64_ext_advsimd_imm_modified (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aarch64_ext_advsimd_imm_shift (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aarch64_ext_aimm (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aarch64_ext_barrier (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aarch64_ext_cond (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aarch64_ext_fbits (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aarch64_ext_fpimm (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aarch64_ext_ft (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aarch64_ext_hint (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aarch64_ext_imm (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aarch64_ext_imm_half (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aarch64_ext_imm_rotate1 (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aarch64_ext_imm_rotate2 (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aarch64_ext_inv_limm (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aarch64_ext_ldst_elemlist (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aarch64_ext_ldst_reglist (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aarch64_ext_ldst_reglist_r (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aarch64_ext_limm (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aarch64_ext_prfop (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aarch64_ext_pstatefield (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aarch64_ext_reg_extended (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aarch64_ext_reg_shifted (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aarch64_ext_reglane (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aarch64_ext_reglist (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aarch64_ext_regno (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aarch64_ext_regno_pair (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aarch64_ext_regrt_sysins (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aarch64_ext_shll_imm (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aarch64_ext_simd_addr_post (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aarch64_ext_sve_addr_ri_s4 (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aarch64_ext_sve_addr_ri_s4xvl (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aarch64_ext_sve_addr_ri_s6xvl (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aarch64_ext_sve_addr_ri_s9xvl (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aarch64_ext_sve_addr_ri_u6 (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aarch64_ext_sve_addr_rr_lsl (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aarch64_ext_sve_addr_rz_xtw (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aarch64_ext_sve_addr_zi_u5 (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aarch64_ext_sve_addr_zz_lsl (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aarch64_ext_sve_addr_zz_sxtw (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aarch64_ext_sve_addr_zz_uxtw (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aarch64_ext_sve_aimm (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aarch64_ext_sve_asimm (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aarch64_ext_sve_float_half_one (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aarch64_ext_sve_float_half_two (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aarch64_ext_sve_float_zero_one (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aarch64_ext_sve_index (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aarch64_ext_sve_limm_mov (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aarch64_ext_sve_quad_index (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aarch64_ext_sve_reglist (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aarch64_ext_sve_scale (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aarch64_ext_sve_shlimm (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aarch64_ext_sve_shrimm (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aarch64_ext_sysins_op (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aarch64_ext_sysreg (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  const* aarch64_operands ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

bfd_boolean
aarch64_extract_operand (const aarch64_operand *self,
			   aarch64_opnd_info *info,
			   aarch64_insn code, const aarch64_inst *inst,
			   aarch64_operand_error *errors)
{
  /* Use the index as the key.  */
  int key = self - aarch64_operands;
  switch (key)
    {
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 9:
    case 10:
    case 11:
    case 15:
    case 16:
    case 17:
    case 18:
    case 20:
    case 21:
    case 22:
    case 23:
    case 24:
    case 25:
    case 26:
    case 27:
    case 28:
    case 29:
    case 153:
    case 154:
    case 155:
    case 156:
    case 157:
    case 158:
    case 159:
    case 160:
    case 161:
    case 162:
    case 175:
    case 176:
    case 177:
    case 178:
    case 179:
    case 180:
    case 181:
    case 182:
    case 183:
    case 187:
    case 190:
      return aarch64_ext_regno (self, info, code, inst, errors);
    case 8:
      return aarch64_ext_regrt_sysins (self, info, code, inst, errors);
    case 12:
      return aarch64_ext_regno_pair (self, info, code, inst, errors);
    case 13:
      return aarch64_ext_reg_extended (self, info, code, inst, errors);
    case 14:
      return aarch64_ext_reg_shifted (self, info, code, inst, errors);
    case 19:
      return aarch64_ext_ft (self, info, code, inst, errors);
    case 30:
    case 31:
    case 32:
    case 33:
    case 192:
      return aarch64_ext_reglane (self, info, code, inst, errors);
    case 34:
      return aarch64_ext_reglist (self, info, code, inst, errors);
    case 35:
      return aarch64_ext_ldst_reglist (self, info, code, inst, errors);
    case 36:
      return aarch64_ext_ldst_reglist_r (self, info, code, inst, errors);
    case 37:
      return aarch64_ext_ldst_elemlist (self, info, code, inst, errors);
    case 38:
    case 39:
    case 40:
    case 41:
    case 51:
    case 52:
    case 53:
    case 54:
    case 55:
    case 56:
    case 57:
    case 58:
    case 59:
    case 60:
    case 61:
    case 62:
    case 63:
    case 64:
    case 75:
    case 76:
    case 77:
    case 78:
    case 79:
    case 150:
    case 152:
    case 167:
    case 168:
    case 169:
    case 170:
    case 171:
    case 172:
    case 173:
    case 174:
      return aarch64_ext_imm (self, info, code, inst, errors);
    case 42:
    case 43:
      return aarch64_ext_advsimd_imm_shift (self, info, code, inst, errors);
    case 44:
    case 45:
    case 46:
      return aarch64_ext_advsimd_imm_modified (self, info, code, inst, errors);
    case 47:
      return aarch64_ext_shll_imm (self, info, code, inst, errors);
    case 50:
    case 141:
      return aarch64_ext_fpimm (self, info, code, inst, errors);
    case 65:
    case 148:
      return aarch64_ext_limm (self, info, code, inst, errors);
    case 66:
      return aarch64_ext_aimm (self, info, code, inst, errors);
    case 67:
      return aarch64_ext_imm_half (self, info, code, inst, errors);
    case 68:
      return aarch64_ext_fbits (self, info, code, inst, errors);
    case 70:
    case 71:
    case 146:
      return aarch64_ext_imm_rotate2 (self, info, code, inst, errors);
    case 72:
    case 145:
      return aarch64_ext_imm_rotate1 (self, info, code, inst, errors);
    case 73:
    case 74:
      return aarch64_ext_cond (self, info, code, inst, errors);
    case 80:
    case 87:
      return aarch64_ext_addr_simple (self, info, code, inst, errors);
    case 81:
      return aarch64_ext_addr_regoff (self, info, code, inst, errors);
    case 82:
    case 83:
    case 84:
      return aarch64_ext_addr_simm (self, info, code, inst, errors);
    case 85:
      return aarch64_ext_addr_simm10 (self, info, code, inst, errors);
    case 86:
      return aarch64_ext_addr_uimm12 (self, info, code, inst, errors);
    case 88:
      return aarch64_ext_addr_offset (self, info, code, inst, errors);
    case 89:
      return aarch64_ext_simd_addr_post (self, info, code, inst, errors);
    case 90:
      return aarch64_ext_sysreg (self, info, code, inst, errors);
    case 91:
      return aarch64_ext_pstatefield (self, info, code, inst, errors);
    case 92:
    case 93:
    case 94:
    case 95:
      return aarch64_ext_sysins_op (self, info, code, inst, errors);
    case 96:
    case 97:
      return aarch64_ext_barrier (self, info, code, inst, errors);
    case 98:
      return aarch64_ext_prfop (self, info, code, inst, errors);
    case 99:
      return aarch64_ext_hint (self, info, code, inst, errors);
    case 100:
      return aarch64_ext_sve_addr_ri_s4 (self, info, code, inst, errors);
    case 101:
    case 102:
    case 103:
    case 104:
      return aarch64_ext_sve_addr_ri_s4xvl (self, info, code, inst, errors);
    case 105:
      return aarch64_ext_sve_addr_ri_s6xvl (self, info, code, inst, errors);
    case 106:
      return aarch64_ext_sve_addr_ri_s9xvl (self, info, code, inst, errors);
    case 107:
    case 108:
    case 109:
    case 110:
      return aarch64_ext_sve_addr_ri_u6 (self, info, code, inst, errors);
    case 111:
    case 112:
    case 113:
    case 114:
    case 115:
    case 116:
    case 117:
    case 118:
    case 119:
    case 120:
    case 121:
    case 122:
    case 123:
      return aarch64_ext_sve_addr_rr_lsl (self, info, code, inst, errors);
    case 124:
    case 125:
    case 126:
    case 127:
    case 128:
    case 129:
    case 130:
    case 131:
      return aarch64_ext_sve_addr_rz_xtw (self, info, code, inst, errors);
    case 132:
    case 133:
    case 134:
    case 135:
      return aarch64_ext_sve_addr_zi_u5 (self, info, code, inst, errors);
    case 136:
      return aarch64_ext_sve_addr_zz_lsl (self, info, code, inst, errors);
    case 137:
      return aarch64_ext_sve_addr_zz_sxtw (self, info, code, inst, errors);
    case 138:
      return aarch64_ext_sve_addr_zz_uxtw (self, info, code, inst, errors);
    case 139:
      return aarch64_ext_sve_aimm (self, info, code, inst, errors);
    case 140:
      return aarch64_ext_sve_asimm (self, info, code, inst, errors);
    case 142:
      return aarch64_ext_sve_float_half_one (self, info, code, inst, errors);
    case 143:
      return aarch64_ext_sve_float_half_two (self, info, code, inst, errors);
    case 144:
      return aarch64_ext_sve_float_zero_one (self, info, code, inst, errors);
    case 147:
      return aarch64_ext_inv_limm (self, info, code, inst, errors);
    case 149:
      return aarch64_ext_sve_limm_mov (self, info, code, inst, errors);
    case 151:
      return aarch64_ext_sve_scale (self, info, code, inst, errors);
    case 163:
    case 164:
      return aarch64_ext_sve_shlimm (self, info, code, inst, errors);
    case 165:
    case 166:
      return aarch64_ext_sve_shrimm (self, info, code, inst, errors);
    case 184:
    case 185:
    case 186:
      return aarch64_ext_sve_quad_index (self, info, code, inst, errors);
    case 188:
      return aarch64_ext_sve_index (self, info, code, inst, errors);
    case 189:
    case 191:
      return aarch64_ext_sve_reglist (self, info, code, inst, errors);
    default: assert (0); abort ();
    }
}