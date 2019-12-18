#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int int64_t ;
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_10__ {void* amount_present; void* operator_present; } ;
struct TYPE_9__ {int imm; void* is_reg; } ;
struct TYPE_11__ {int /*<<< orphan*/  preind; void* writeback; TYPE_1__ offset; int /*<<< orphan*/  base_regno; } ;
struct TYPE_12__ {TYPE_2__ shifter; TYPE_3__ addr; } ;
typedef  TYPE_4__ aarch64_opnd_info ;
struct TYPE_13__ {int /*<<< orphan*/ * fields; } ;
typedef  TYPE_5__ aarch64_operand ;
typedef  int /*<<< orphan*/  aarch64_insn ;

/* Variables and functions */
 void* FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  extract_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int get_operand_specific_data (TYPE_5__ const*) ; 

__attribute__((used)) static bfd_boolean
aarch64_ext_sve_addr_reg_imm (const aarch64_operand *self,
			      aarch64_opnd_info *info, aarch64_insn code,
			      int64_t offset)
{
  info->addr.base_regno = extract_field (self->fields[0], code, 0);
  info->addr.offset.imm = offset * (1 << get_operand_specific_data (self));
  info->addr.offset.is_reg = FALSE;
  info->addr.writeback = FALSE;
  info->addr.preind = TRUE;
  info->shifter.operator_present = FALSE;
  info->shifter.amount_present = FALSE;
  return TRUE;
}