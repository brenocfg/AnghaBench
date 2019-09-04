#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_7__ {int value; TYPE_2__* opcode; TYPE_1__* operands; } ;
typedef  TYPE_3__ aarch64_inst ;
struct TYPE_6__ {int iclass; int /*<<< orphan*/ ** qualifiers_list; } ;
struct TYPE_5__ {int /*<<< orphan*/  qualifier; } ;

/* Variables and functions */
 int AARCH64_MAX_OPND_NUM ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FLD_SVE_M_14 ; 
 int /*<<< orphan*/  FLD_SVE_M_16 ; 
 int /*<<< orphan*/  FLD_SVE_M_4 ; 
 int /*<<< orphan*/  FLD_SVE_sz ; 
 int /*<<< orphan*/  FLD_SVE_tszh ; 
 int /*<<< orphan*/  FLD_SVE_tszl_19 ; 
 int /*<<< orphan*/  FLD_SVE_tszl_8 ; 
 int /*<<< orphan*/  FLD_imm5 ; 
 int /*<<< orphan*/  FLD_size ; 
 int /*<<< orphan*/  TRUE ; 
 int extract_field (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int extract_fields (int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  sve_cpy 139 
#define  sve_index 138 
#define  sve_limm 137 
#define  sve_misc 136 
#define  sve_movprfx 135 
#define  sve_pred_zm 134 
#define  sve_shift_pred 133 
#define  sve_shift_unpred 132 
#define  sve_size_bhs 131 
#define  sve_size_bhsd 130 
#define  sve_size_hsd 129 
#define  sve_size_sd 128 

__attribute__((used)) static bfd_boolean
aarch64_decode_variant_using_iclass (aarch64_inst *inst)
{
  int i, variant;

  variant = 0;
  switch (inst->opcode->iclass)
    {
    case sve_cpy:
      variant = extract_fields (inst->value, 0, 2, FLD_size, FLD_SVE_M_14);
      break;

    case sve_index:
      i = extract_fields (inst->value, 0, 2, FLD_SVE_tszh, FLD_imm5);
      if ((i & 31) == 0)
	return FALSE;
      while ((i & 1) == 0)
	{
	  i >>= 1;
	  variant += 1;
	}
      break;

    case sve_limm:
      /* Pick the smallest applicable element size.  */
      if ((inst->value & 0x20600) == 0x600)
	variant = 0;
      else if ((inst->value & 0x20400) == 0x400)
	variant = 1;
      else if ((inst->value & 0x20000) == 0)
	variant = 2;
      else
	variant = 3;
      break;

    case sve_misc:
      /* sve_misc instructions have only a single variant.  */
      break;

    case sve_movprfx:
      variant = extract_fields (inst->value, 0, 2, FLD_size, FLD_SVE_M_16);
      break;

    case sve_pred_zm:
      variant = extract_field (FLD_SVE_M_4, inst->value, 0);
      break;

    case sve_shift_pred:
      i = extract_fields (inst->value, 0, 2, FLD_SVE_tszh, FLD_SVE_tszl_8);
    sve_shift:
      if (i == 0)
	return FALSE;
      while (i != 1)
	{
	  i >>= 1;
	  variant += 1;
	}
      break;

    case sve_shift_unpred:
      i = extract_fields (inst->value, 0, 2, FLD_SVE_tszh, FLD_SVE_tszl_19);
      goto sve_shift;

    case sve_size_bhs:
      variant = extract_field (FLD_size, inst->value, 0);
      if (variant >= 3)
	return FALSE;
      break;

    case sve_size_bhsd:
      variant = extract_field (FLD_size, inst->value, 0);
      break;

    case sve_size_hsd:
      i = extract_field (FLD_size, inst->value, 0);
      if (i < 1)
	return FALSE;
      variant = i - 1;
      break;

    case sve_size_sd:
      variant = extract_field (FLD_SVE_sz, inst->value, 0);
      break;

    default:
      /* No mapping between instruction class and qualifiers.  */
      return TRUE;
    }

  for (i = 0; i < AARCH64_MAX_OPND_NUM; ++i)
    inst->operands[i].qualifier = inst->opcode->qualifiers_list[variant][i];
  return TRUE;
}