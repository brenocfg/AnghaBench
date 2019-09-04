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
struct acpi_buffer {int length; void* pointer; } ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_PROCESSOR_AGGREGATOR_NOTIFY ; 
 int /*<<< orphan*/  acpi_evaluate_ost (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct acpi_buffer*) ; 
 int acpi_pad_pur (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ xen_acpi_pad_idle_cpus (int) ; 
 int xen_acpi_pad_idle_cpus_num () ; 
 int /*<<< orphan*/  xen_cpu_lock ; 

__attribute__((used)) static void acpi_pad_handle_notify(acpi_handle handle)
{
	int idle_nums;
	struct acpi_buffer param = {
		.length = 4,
		.pointer = (void *)&idle_nums,
	};


	mutex_lock(&xen_cpu_lock);
	idle_nums = acpi_pad_pur(handle);
	if (idle_nums < 0) {
		mutex_unlock(&xen_cpu_lock);
		return;
	}

	idle_nums = xen_acpi_pad_idle_cpus(idle_nums)
		    ?: xen_acpi_pad_idle_cpus_num();
	if (idle_nums >= 0)
		acpi_evaluate_ost(handle, ACPI_PROCESSOR_AGGREGATOR_NOTIFY,
				  0, &param);
	mutex_unlock(&xen_cpu_lock);
}