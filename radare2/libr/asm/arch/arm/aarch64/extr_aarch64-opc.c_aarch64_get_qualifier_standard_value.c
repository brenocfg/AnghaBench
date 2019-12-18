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
typedef  size_t aarch64_opnd_qualifier_t ;
typedef  int /*<<< orphan*/  aarch64_insn ;
struct TYPE_2__ {int /*<<< orphan*/  data2; } ;

/* Variables and functions */
 scalar_t__ TRUE ; 
 TYPE_1__* aarch64_opnd_qualifiers ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ operand_variant_qualifier_p (size_t) ; 

aarch64_insn
aarch64_get_qualifier_standard_value (aarch64_opnd_qualifier_t qualifier)
{
  assert (operand_variant_qualifier_p (qualifier) == TRUE);
  return aarch64_opnd_qualifiers[qualifier].data2;
}