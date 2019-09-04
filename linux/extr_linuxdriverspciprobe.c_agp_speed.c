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
typedef  enum pci_bus_speed { ____Placeholder_pci_bus_speed } pci_bus_speed ;

/* Variables and functions */
 int* agp_speeds ; 

__attribute__((used)) static enum pci_bus_speed agp_speed(int agp3, int agpstat)
{
	int index = 0;

	if (agpstat & 4)
		index = 3;
	else if (agpstat & 2)
		index = 2;
	else if (agpstat & 1)
		index = 1;
	else
		goto out;

	if (agp3) {
		index += 2;
		if (index == 5)
			index = 0;
	}

 out:
	return agp_speeds[index];
}