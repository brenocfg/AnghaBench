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
struct TYPE_5__ {int /*<<< orphan*/  value; } ;
struct TYPE_6__ {TYPE_1__ imm; } ;
typedef  TYPE_2__ aarch64_opnd_info ;
typedef  int /*<<< orphan*/  aarch64_operand_error ;
typedef  int /*<<< orphan*/  aarch64_operand ;
typedef  int /*<<< orphan*/  aarch64_inst ;
typedef  int /*<<< orphan*/  aarch64_insn ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  aarch64_ext_limm (int /*<<< orphan*/  const*,TYPE_2__*,int /*<<< orphan*/  const,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

bfd_boolean
aarch64_ext_inv_limm (const aarch64_operand *self,
		      aarch64_opnd_info *info, const aarch64_insn code,
		      const aarch64_inst *inst,
		      aarch64_operand_error *errors)
{
  if (!aarch64_ext_limm (self, info, code, inst, errors))
    return FALSE;
  info->imm.value = ~info->imm.value;
  return TRUE;
}