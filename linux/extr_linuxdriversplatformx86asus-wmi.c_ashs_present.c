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

/* Variables and functions */
 scalar_t__ acpi_dev_found (scalar_t__) ; 
 scalar_t__* ashs_ids ; 

__attribute__((used)) static bool ashs_present(void)
{
	int i = 0;
	while (ashs_ids[i]) {
		if (acpi_dev_found(ashs_ids[i++]))
			return true;
	}
	return false;
}