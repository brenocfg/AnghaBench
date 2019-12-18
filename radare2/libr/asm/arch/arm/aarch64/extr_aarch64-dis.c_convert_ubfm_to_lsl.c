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
typedef  scalar_t__ int64_t ;
struct TYPE_7__ {TYPE_2__* operands; } ;
typedef  TYPE_3__ aarch64_inst ;
struct TYPE_5__ {scalar_t__ value; } ;
struct TYPE_6__ {scalar_t__ qualifier; TYPE_1__ imm; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  AARCH64_OPND_NIL ; 
 scalar_t__ AARCH64_OPND_QLF_imm_0_31 ; 

__attribute__((used)) static int
convert_ubfm_to_lsl (aarch64_inst *inst)
{
  int64_t immr = inst->operands[2].imm.value;
  int64_t imms = inst->operands[3].imm.value;
  int64_t val
    = inst->operands[2].qualifier == AARCH64_OPND_QLF_imm_0_31 ? 31 : 63;

  if ((immr == 0 && imms == val) || immr == imms + 1)
    {
      inst->operands[3].type = AARCH64_OPND_NIL;
      inst->operands[2].imm.value = val - imms;
      return 1;
    }

  return 0;
}