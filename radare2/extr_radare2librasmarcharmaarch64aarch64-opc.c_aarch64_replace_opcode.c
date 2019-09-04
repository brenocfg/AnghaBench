#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__* operands; int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ const aarch64_opcode ;
struct TYPE_9__ {TYPE_1__* operands; TYPE_2__ const* opcode; } ;
typedef  TYPE_3__ aarch64_inst ;
struct TYPE_7__ {scalar_t__ type; } ;

/* Variables and functions */
 int AARCH64_MAX_OPND_NUM ; 
 scalar_t__ AARCH64_OPND_NIL ; 
 int /*<<< orphan*/  DEBUG_TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

const aarch64_opcode*
aarch64_replace_opcode (aarch64_inst *inst, const aarch64_opcode *opcode)
{
  int i;
  const aarch64_opcode *old = inst->opcode;

  inst->opcode = opcode;

  /* Update the operand types.  */
  for (i = 0; i < AARCH64_MAX_OPND_NUM; ++i)
    {
      inst->operands[i].type = opcode->operands[i];
      if (opcode->operands[i] == AARCH64_OPND_NIL)
	break;
    }

  DEBUG_TRACE ("replace %s with %s", old->name, opcode->name);

  return old;
}