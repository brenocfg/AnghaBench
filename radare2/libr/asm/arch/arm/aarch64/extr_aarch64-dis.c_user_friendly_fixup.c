#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_3__* operands; TYPE_1__* opcode; } ;
typedef  TYPE_4__ aarch64_inst ;
struct TYPE_7__ {int value; } ;
struct TYPE_8__ {int /*<<< orphan*/  qualifier; TYPE_2__ imm; } ;
struct TYPE_6__ {int iclass; } ;

/* Variables and functions */
 int /*<<< orphan*/  AARCH64_OPND_QLF_W ; 
#define  testbranch 128 

__attribute__((used)) static void
user_friendly_fixup (aarch64_inst *inst)
{
  switch (inst->opcode->iclass)
    {
    case testbranch:
      /* TBNZ Xn|Wn, #uimm6, label
	 Test and Branch Not Zero: conditionally jumps to label if bit number
	 uimm6 in register Xn is not zero.  The bit number implies the width of
	 the register, which may be written and should be disassembled as Wn if
	 uimm is less than 32. Limited to a branch offset range of +/- 32KiB.
	 */
      if (inst->operands[1].imm.value < 32)
	inst->operands[0].qualifier = AARCH64_OPND_QLF_W;
      break;
    default: break;
    }
}