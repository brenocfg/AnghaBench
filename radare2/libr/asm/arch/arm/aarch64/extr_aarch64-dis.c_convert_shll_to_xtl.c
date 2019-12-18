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
struct TYPE_7__ {TYPE_2__* operands; } ;
typedef  TYPE_3__ aarch64_inst ;
struct TYPE_5__ {scalar_t__ value; } ;
struct TYPE_6__ {int /*<<< orphan*/  type; TYPE_1__ imm; } ;

/* Variables and functions */
 int /*<<< orphan*/  AARCH64_OPND_NIL ; 

__attribute__((used)) static int
convert_shll_to_xtl (aarch64_inst *inst)
{
  if (inst->operands[2].imm.value == 0)
    {
      inst->operands[2].type = AARCH64_OPND_NIL;
      return 1;
    }
  return 0;
}