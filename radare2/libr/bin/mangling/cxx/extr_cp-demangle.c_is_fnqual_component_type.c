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
typedef  enum demangle_component_type { ____Placeholder_demangle_component_type } demangle_component_type ;

/* Variables and functions */

__attribute__((used)) static int
is_fnqual_component_type (enum demangle_component_type type)
{
  switch (type)
    {
    FNQUAL_COMPONENT_CASE:
      return 1;
    default:
      break;
    }
  return 0;
}