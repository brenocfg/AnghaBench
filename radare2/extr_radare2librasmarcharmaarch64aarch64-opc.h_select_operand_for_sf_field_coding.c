#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * operands; } ;
typedef  TYPE_1__ aarch64_opcode ;

/* Variables and functions */
 scalar_t__ AARCH64_OPND_CLASS_INT_REG ; 
 scalar_t__ aarch64_get_operand_class (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
select_operand_for_sf_field_coding (const aarch64_opcode *opcode)
{
  int idx = -1;
  if (aarch64_get_operand_class (opcode->operands[0])
      == AARCH64_OPND_CLASS_INT_REG)
    /* normal case.  */
    idx = 0;
  else if (aarch64_get_operand_class (opcode->operands[1])
	   == AARCH64_OPND_CLASS_INT_REG)
    /* e.g. float2fix.  */
    idx = 1;
  else
    { assert (0); abort (); }
  return idx;
}