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
struct TYPE_2__ {int data1; } ;

/* Variables and functions */
 scalar_t__ TRUE ; 
 TYPE_1__* aarch64_opnd_qualifiers ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ qualifier_value_in_range_constraint_p (size_t) ; 

__attribute__((used)) static int
get_upper_bound (aarch64_opnd_qualifier_t qualifier)
{
  assert (qualifier_value_in_range_constraint_p (qualifier) == TRUE);
  return aarch64_opnd_qualifiers[qualifier].data1;
}