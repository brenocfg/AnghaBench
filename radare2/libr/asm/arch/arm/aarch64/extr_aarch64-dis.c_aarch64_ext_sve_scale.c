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
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_5__ {int amount; int operator_present; int amount_present; int /*<<< orphan*/  kind; } ;
struct TYPE_6__ {TYPE_1__ shifter; } ;
typedef  TYPE_2__ aarch64_opnd_info ;
typedef  int /*<<< orphan*/  aarch64_operand_error ;
typedef  int /*<<< orphan*/  aarch64_operand ;
typedef  int /*<<< orphan*/  aarch64_inst ;
typedef  int /*<<< orphan*/  aarch64_insn ;

/* Variables and functions */
 int /*<<< orphan*/  AARCH64_MOD_MUL ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FLD_SVE_imm4 ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  aarch64_ext_imm (int /*<<< orphan*/  const*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int extract_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bfd_boolean
aarch64_ext_sve_scale (const aarch64_operand *self,
		       aarch64_opnd_info *info, aarch64_insn code,
		       const aarch64_inst *inst, aarch64_operand_error *errors)
{
  int val;

  if (!aarch64_ext_imm (self, info, code, inst, errors))
    return FALSE;
  val = extract_field (FLD_SVE_imm4, code, 0);
  info->shifter.kind = AARCH64_MOD_MUL;
  info->shifter.amount = val + 1;
  info->shifter.operator_present = (val != 0);
  info->shifter.amount_present = (val != 0);
  return TRUE;
}