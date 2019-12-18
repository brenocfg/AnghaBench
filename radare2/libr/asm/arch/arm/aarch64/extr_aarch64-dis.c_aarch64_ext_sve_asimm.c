#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int8_t ;
typedef  int bfd_boolean ;
struct TYPE_6__ {scalar_t__ value; } ;
struct TYPE_7__ {TYPE_1__ imm; } ;
typedef  TYPE_2__ aarch64_opnd_info ;
typedef  int /*<<< orphan*/  aarch64_operand_error ;
typedef  int /*<<< orphan*/  aarch64_operand ;
typedef  int /*<<< orphan*/  aarch64_inst ;
typedef  int /*<<< orphan*/  aarch64_insn ;

/* Variables and functions */
 scalar_t__ aarch64_ext_imm (int /*<<< orphan*/  const*,TYPE_2__*,int /*<<< orphan*/  const,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 scalar_t__ decode_sve_aimm (TYPE_2__*,int /*<<< orphan*/ ) ; 

bfd_boolean
aarch64_ext_sve_asimm (const aarch64_operand *self,
		       aarch64_opnd_info *info, const aarch64_insn code,
		       const aarch64_inst *inst,
		       aarch64_operand_error *errors)
{
  return (aarch64_ext_imm (self, info, code, inst, errors)
	  && decode_sve_aimm (info, (int8_t) info->imm.value));
}