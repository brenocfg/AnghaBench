#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  enum aarch64_opnd { ____Placeholder_aarch64_opnd } aarch64_opnd ;
typedef  enum aarch64_operand_class { ____Placeholder_aarch64_operand_class } aarch64_operand_class ;
struct TYPE_2__ {int op_class; } ;

/* Variables and functions */
 TYPE_1__* aarch64_operands ; 

enum aarch64_operand_class
aarch64_get_operand_class (enum aarch64_opnd type)
{
  return aarch64_operands[type].op_class;
}