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
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  size_t aarch64_opnd_qualifier_t ;
struct TYPE_2__ {scalar_t__ kind; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ OQK_VALUE_IN_RANGE ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_1__* aarch64_opnd_qualifiers ; 

__attribute__((used)) static inline bfd_boolean
qualifier_value_in_range_constraint_p (aarch64_opnd_qualifier_t qualifier)
{
  return (aarch64_opnd_qualifiers[qualifier].kind == OQK_VALUE_IN_RANGE)
    ? TRUE : FALSE;
}