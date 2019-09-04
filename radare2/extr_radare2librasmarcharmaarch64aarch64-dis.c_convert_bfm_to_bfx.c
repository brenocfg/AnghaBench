#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
struct TYPE_8__ {TYPE_2__* operands; } ;
typedef  TYPE_3__ aarch64_inst ;
struct TYPE_6__ {scalar_t__ value; } ;
struct TYPE_7__ {TYPE_1__ imm; } ;

/* Variables and functions */
 int /*<<< orphan*/  reset_operand_qualifier (TYPE_3__*,int) ; 

__attribute__((used)) static int
convert_bfm_to_bfx (aarch64_inst *inst)
{
  int64_t immr, imms;

  immr = inst->operands[2].imm.value;
  imms = inst->operands[3].imm.value;
  if (imms >= immr)
    {
      int64_t lsb = immr;
      inst->operands[2].imm.value = lsb;
      inst->operands[3].imm.value = imms + 1 - lsb;
      /* The two opcodes have different qualifiers for
	 the immediate operands; reset to help the checking.  */
      reset_operand_qualifier (inst, 2);
      reset_operand_qualifier (inst, 3);
      return 1;
    }

  return 0;
}