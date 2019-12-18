#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  enum aarch64_modifier_kind { ____Placeholder_aarch64_modifier_kind } aarch64_modifier_kind ;
typedef  scalar_t__ bfd_boolean ;
typedef  int aarch64_insn ;

/* Variables and functions */
 int AARCH64_MOD_LSL ; 
 int AARCH64_MOD_UXTB ; 
 scalar_t__ TRUE ; 

enum aarch64_modifier_kind
aarch64_get_operand_modifier_from_value (aarch64_insn value,
					 bfd_boolean extend_p)
{
  if (extend_p == TRUE)
    return AARCH64_MOD_UXTB + value;
  else
    return AARCH64_MOD_LSL - value;
}