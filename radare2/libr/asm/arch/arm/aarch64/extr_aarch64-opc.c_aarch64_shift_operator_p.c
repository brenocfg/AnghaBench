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
typedef  int /*<<< orphan*/  bfd_boolean ;

/* Variables and functions */
 int AARCH64_MOD_LSL ; 
 int AARCH64_MOD_ROR ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static inline bfd_boolean
aarch64_shift_operator_p (enum aarch64_modifier_kind kind)
{
  return (kind >= AARCH64_MOD_ROR && kind <= AARCH64_MOD_LSL)
    ? TRUE : FALSE;
}