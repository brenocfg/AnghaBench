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
typedef  int u32 ;
struct topstar_laptop {int dummy; } ;
struct acpi_device {int dummy; } ;

/* Variables and functions */
 struct topstar_laptop* acpi_driver_data (struct acpi_device*) ; 
 int /*<<< orphan*/  topstar_input_notify (struct topstar_laptop*,int) ; 

__attribute__((used)) static void topstar_acpi_notify(struct acpi_device *device, u32 event)
{
	struct topstar_laptop *topstar = acpi_driver_data(device);
	static bool dup_evnt[2];
	bool *dup;

	/* 0x83 and 0x84 key events comes duplicated... */
	if (event == 0x83 || event == 0x84) {
		dup = &dup_evnt[event - 0x83];
		if (*dup) {
			*dup = false;
			return;
		}
		*dup = true;
	}

	topstar_input_notify(topstar, event);
}