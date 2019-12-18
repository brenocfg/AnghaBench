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
struct TYPE_2__ {char const* desc; } ;

/* Variables and functions */
 TYPE_1__* aarch64_operands ; 

const char *
aarch64_get_operand_desc (enum aarch64_opnd type)
{
  return aarch64_operands[type].desc;
}