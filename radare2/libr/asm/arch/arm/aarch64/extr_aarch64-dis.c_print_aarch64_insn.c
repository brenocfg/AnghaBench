#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct disassemble_info {int dummy; } ;
typedef  int /*<<< orphan*/  bfd_vma ;
struct TYPE_5__ {int /*<<< orphan*/  operands; int /*<<< orphan*/  opcode; } ;
typedef  TYPE_1__ aarch64_inst ;

/* Variables and functions */
 int /*<<< orphan*/  print_comment (TYPE_1__ const*,struct disassemble_info*) ; 
 int /*<<< orphan*/  print_mnemonic_name (TYPE_1__ const*,struct disassemble_info*) ; 
 int /*<<< orphan*/  print_operands (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct disassemble_info*) ; 

__attribute__((used)) static void
print_aarch64_insn (bfd_vma pc, const aarch64_inst *inst,
		    struct disassemble_info *info)
{
  print_mnemonic_name (inst, info);
  print_operands (pc, inst->opcode, inst->operands, info);
  print_comment (inst, info);
}