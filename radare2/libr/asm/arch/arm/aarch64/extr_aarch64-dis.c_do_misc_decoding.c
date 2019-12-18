#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  value; TYPE_1__* opcode; } ;
typedef  TYPE_2__ aarch64_inst ;
struct TYPE_7__ {int op; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLD_SVE_Pd ; 
 int /*<<< orphan*/  FLD_SVE_Pg4_10 ; 
 int /*<<< orphan*/  FLD_SVE_Pm ; 
 int /*<<< orphan*/  FLD_SVE_Pn ; 
 int /*<<< orphan*/  FLD_SVE_Zd ; 
 int /*<<< orphan*/  FLD_SVE_Zm_16 ; 
 int /*<<< orphan*/  FLD_SVE_Zn ; 
 int /*<<< orphan*/  FLD_SVE_tszh ; 
 int /*<<< orphan*/  FLD_imm5 ; 
#define  OP_FCVT 144 
#define  OP_FCVTL 143 
#define  OP_FCVTL2 142 
#define  OP_FCVTN 141 
#define  OP_FCVTN2 140 
#define  OP_FCVTXN_S 139 
#define  OP_MOVM_P_P_P 138 
#define  OP_MOVS_P_P 137 
#define  OP_MOVZS_P_P_P 136 
#define  OP_MOVZ_P_P_P 135 
#define  OP_MOV_P_P 134 
#define  OP_MOV_Z_P_Z 133 
#define  OP_MOV_Z_V 132 
#define  OP_MOV_Z_Z 131 
#define  OP_MOV_Z_Zi 130 
#define  OP_NOTS_P_P_P_Z 129 
#define  OP_NOT_P_P_P_Z 128 
 int decode_asimd_fcvt (TYPE_2__*) ; 
 int decode_asisd_fcvtxn (TYPE_2__*) ; 
 int decode_fcvt (TYPE_2__*) ; 
 unsigned int extract_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int extract_fields (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
do_misc_decoding (aarch64_inst *inst)
{
  unsigned int value;
  switch (inst->opcode->op)
    {
    case OP_FCVT:
      return decode_fcvt (inst);

    case OP_FCVTN:
    case OP_FCVTN2:
    case OP_FCVTL:
    case OP_FCVTL2:
      return decode_asimd_fcvt (inst);

    case OP_FCVTXN_S:
      return decode_asisd_fcvtxn (inst);

    case OP_MOV_P_P:
    case OP_MOVS_P_P:
      value = extract_field (FLD_SVE_Pn, inst->value, 0);
      return (value == extract_field (FLD_SVE_Pm, inst->value, 0)
	      && value == extract_field (FLD_SVE_Pg4_10, inst->value, 0));

    case OP_MOV_Z_P_Z:
      return (extract_field (FLD_SVE_Zd, inst->value, 0)
	      == extract_field (FLD_SVE_Zm_16, inst->value, 0));

    case OP_MOV_Z_V:
      /* Index must be zero.  */
      value = extract_fields (inst->value, 0, 2, FLD_SVE_tszh, FLD_imm5);
      return value > 0 && value <= 16 && value == (value & -value);

    case OP_MOV_Z_Z:
      return (extract_field (FLD_SVE_Zn, inst->value, 0)
	      == extract_field (FLD_SVE_Zm_16, inst->value, 0));

    case OP_MOV_Z_Zi:
      /* Index must be nonzero.  */
      value = extract_fields (inst->value, 0, 2, FLD_SVE_tszh, FLD_imm5);
      return value > 0 && value != (value & -value);

    case OP_MOVM_P_P_P:
      return (extract_field (FLD_SVE_Pd, inst->value, 0)
	      == extract_field (FLD_SVE_Pm, inst->value, 0));

    case OP_MOVZS_P_P_P:
    case OP_MOVZ_P_P_P:
      return (extract_field (FLD_SVE_Pn, inst->value, 0)
	      == extract_field (FLD_SVE_Pm, inst->value, 0));

    case OP_NOTS_P_P_P_Z:
    case OP_NOT_P_P_P_Z:
      return (extract_field (FLD_SVE_Pm, inst->value, 0)
	      == extract_field (FLD_SVE_Pg4_10, inst->value, 0));

    default:
      return 0;
    }
}