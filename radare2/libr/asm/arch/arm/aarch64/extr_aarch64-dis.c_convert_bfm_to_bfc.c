#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int int64_t ;
struct TYPE_11__ {TYPE_3__* operands; } ;
typedef  TYPE_4__ aarch64_inst ;
struct TYPE_9__ {int value; } ;
struct TYPE_8__ {int regno; } ;
struct TYPE_10__ {scalar_t__ qualifier; TYPE_2__ imm; int /*<<< orphan*/  type; TYPE_1__ reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  AARCH64_OPND_NIL ; 
 scalar_t__ AARCH64_OPND_QLF_imm_0_31 ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  copy_operand_info (TYPE_4__*,int,int) ; 
 int /*<<< orphan*/  reset_operand_qualifier (TYPE_4__*,int) ; 

__attribute__((used)) static int
convert_bfm_to_bfc (aarch64_inst *inst)
{
  int64_t immr, imms, val;

  /* Should have been assured by the base opcode value.  */
  assert (inst->operands[1].reg.regno == 0x1f);

  immr = inst->operands[2].imm.value;
  imms = inst->operands[3].imm.value;
  val = inst->operands[2].qualifier == AARCH64_OPND_QLF_imm_0_31 ? 32 : 64;
  if (imms < immr)
    {
      /* Drop XZR from the second operand.  */
      copy_operand_info (inst, 1, 2);
      copy_operand_info (inst, 2, 3);
      inst->operands[3].type = AARCH64_OPND_NIL;

      /* Recalculate the immediates.  */
      inst->operands[1].imm.value = (val - immr) & (val - 1);
      inst->operands[2].imm.value = imms + 1;

      /* The two opcodes have different qualifiers for the operands; reset to
	 help the checking.  */
      reset_operand_qualifier (inst, 1);
      reset_operand_qualifier (inst, 2);
      reset_operand_qualifier (inst, 3);

      return 1;
    }

  return 0;
}