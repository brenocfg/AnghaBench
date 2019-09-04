#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int op; } ;
typedef  TYPE_1__ aarch64_opcode ;
typedef  int /*<<< orphan*/  aarch64_inst ;

/* Variables and functions */
#define  OP_ASR_IMM 151 
#define  OP_BFC 150 
#define  OP_BFI 149 
#define  OP_BFXIL 148 
#define  OP_CINC 147 
#define  OP_CINV 146 
#define  OP_CNEG 145 
#define  OP_CSET 144 
#define  OP_CSETM 143 
#define  OP_LSL_IMM 142 
#define  OP_LSR_IMM 141 
#define  OP_MOV_IMM_LOG 140 
#define  OP_MOV_IMM_WIDE 139 
#define  OP_MOV_IMM_WIDEN 138 
#define  OP_MOV_V 137 
#define  OP_ROR_IMM 136 
#define  OP_SBFIZ 135 
#define  OP_SBFX 134 
#define  OP_SXTL 133 
#define  OP_SXTL2 132 
#define  OP_UBFIZ 131 
#define  OP_UBFX 130 
#define  OP_UXTL 129 
#define  OP_UXTL2 128 
 int convert_bfm_to_bfc (int /*<<< orphan*/ *) ; 
 int convert_bfm_to_bfi (int /*<<< orphan*/ *) ; 
 int convert_bfm_to_bfx (int /*<<< orphan*/ *) ; 
 int convert_bfm_to_sr (int /*<<< orphan*/ *) ; 
 int convert_csinc_to_cset (int /*<<< orphan*/ *) ; 
 int convert_extr_to_ror (int /*<<< orphan*/ *) ; 
 int convert_from_csel (int /*<<< orphan*/ *) ; 
 int convert_movebitmask_to_mov (int /*<<< orphan*/ *) ; 
 int convert_movewide_to_mov (int /*<<< orphan*/ *) ; 
 int convert_orr_to_mov (int /*<<< orphan*/ *) ; 
 int convert_shll_to_xtl (int /*<<< orphan*/ *) ; 
 int convert_ubfm_to_lsl (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
convert_to_alias (aarch64_inst *inst, const aarch64_opcode *alias)
{
  switch (alias->op)
    {
    case OP_ASR_IMM:
    case OP_LSR_IMM:
      return convert_bfm_to_sr (inst);
    case OP_LSL_IMM:
      return convert_ubfm_to_lsl (inst);
    case OP_CINC:
    case OP_CINV:
    case OP_CNEG:
      return convert_from_csel (inst);
    case OP_CSET:
    case OP_CSETM:
      return convert_csinc_to_cset (inst);
    case OP_UBFX:
    case OP_BFXIL:
    case OP_SBFX:
      return convert_bfm_to_bfx (inst);
    case OP_SBFIZ:
    case OP_BFI:
    case OP_UBFIZ:
      return convert_bfm_to_bfi (inst);
    case OP_BFC:
      return convert_bfm_to_bfc (inst);
    case OP_MOV_V:
      return convert_orr_to_mov (inst);
    case OP_MOV_IMM_WIDE:
    case OP_MOV_IMM_WIDEN:
      return convert_movewide_to_mov (inst);
    case OP_MOV_IMM_LOG:
      return convert_movebitmask_to_mov (inst);
    case OP_ROR_IMM:
      return convert_extr_to_ror (inst);
    case OP_SXTL:
    case OP_SXTL2:
    case OP_UXTL:
    case OP_UXTL2:
      return convert_shll_to_xtl (inst);
    default:
      return 0;
    }
}