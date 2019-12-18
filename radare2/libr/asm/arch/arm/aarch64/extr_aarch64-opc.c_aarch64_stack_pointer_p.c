#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int regno; } ;
struct TYPE_5__ {TYPE_1__ reg; scalar_t__ type; } ;
typedef  TYPE_2__ aarch64_opnd_info ;

/* Variables and functions */
 scalar_t__ AARCH64_OPND_CLASS_INT_REG ; 
 scalar_t__ aarch64_get_operand_class (scalar_t__) ; 
 scalar_t__ aarch64_operands ; 
 scalar_t__ operand_maybe_stack_pointer (scalar_t__) ; 

int
aarch64_stack_pointer_p (const aarch64_opnd_info *operand)
{
  return ((aarch64_get_operand_class (operand->type)
	   == AARCH64_OPND_CLASS_INT_REG)
	  && operand_maybe_stack_pointer (aarch64_operands + operand->type)
	  && operand->reg.regno == 31);
}