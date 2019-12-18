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
typedef  enum aarch64_modifier_kind { ____Placeholder_aarch64_modifier_kind } aarch64_modifier_kind ;
typedef  int /*<<< orphan*/  aarch64_insn ;
struct TYPE_2__ {int /*<<< orphan*/  value; } ;

/* Variables and functions */
 TYPE_1__* aarch64_operand_modifiers ; 

aarch64_insn
aarch64_get_operand_modifier_value (enum aarch64_modifier_kind kind)
{
  return aarch64_operand_modifiers[kind].value;
}