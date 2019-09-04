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
typedef  int int64_t ;
struct TYPE_7__ {TYPE_2__* operands; } ;
typedef  TYPE_3__ aarch64_inst ;
struct TYPE_5__ {int value; } ;
struct TYPE_6__ {scalar_t__ qualifier; int /*<<< orphan*/  type; TYPE_1__ imm; } ;

/* Variables and functions */
 int /*<<< orphan*/  AARCH64_OPND_NIL ; 
 scalar_t__ AARCH64_OPND_QLF_imm_0_31 ; 

__attribute__((used)) static int
convert_bfm_to_sr (aarch64_inst *inst)
{
  int64_t imms, val;

  imms = inst->operands[3].imm.value;
  val = inst->operands[2].qualifier == AARCH64_OPND_QLF_imm_0_31 ? 31 : 63;
  if (imms == val)
    {
      inst->operands[3].type = AARCH64_OPND_NIL;
      return 1;
    }

  return 0;
}