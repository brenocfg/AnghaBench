#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_11__ {TYPE_4__* operands; TYPE_1__* opcode; } ;
typedef  TYPE_5__ aarch64_inst ;
struct TYPE_9__ {int /*<<< orphan*/  amount; int /*<<< orphan*/  kind; } ;
struct TYPE_8__ {int /*<<< orphan*/  value; } ;
struct TYPE_10__ {scalar_t__ qualifier; TYPE_3__ shifter; TYPE_2__ imm; int /*<<< orphan*/  type; } ;
struct TYPE_7__ {scalar_t__ op; } ;

/* Variables and functions */
 int /*<<< orphan*/  AARCH64_MOD_NONE ; 
 int /*<<< orphan*/  AARCH64_OPND_IMM_MOV ; 
 scalar_t__ AARCH64_OPND_QLF_W ; 
 scalar_t__ OP_MOVN ; 
 scalar_t__ aarch64_wide_constant_p (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
convert_movewide_to_mov (aarch64_inst *inst)
{
  uint64_t value = inst->operands[1].imm.value;
  /* MOVZ/MOVN #0 have a shift amount other than LSL #0.  */
  if (value == 0 && inst->operands[1].shifter.amount != 0)
    return 0;
  inst->operands[1].type = AARCH64_OPND_IMM_MOV;
  inst->operands[1].shifter.kind = AARCH64_MOD_NONE;
  value <<= inst->operands[1].shifter.amount;
  /* As an alias convertor, it has to be clear that the INST->OPCODE
     is the opcode of the real instruction.  */
  if (inst->opcode->op == OP_MOVN)
    {
      int is32 = inst->operands[0].qualifier == AARCH64_OPND_QLF_W;
      value = ~value;
      /* A MOVN has an immediate that could be encoded by MOVZ.  */
      if (aarch64_wide_constant_p (value, is32, NULL))
	return 0;
    }
  inst->operands[1].imm.value = value;
  inst->operands[1].shifter.amount = 0;
  return 1;
}