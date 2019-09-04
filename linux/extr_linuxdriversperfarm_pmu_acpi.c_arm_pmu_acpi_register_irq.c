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
struct acpi_madt_generic_interrupt {int performance_interrupt; int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ACTIVE_HIGH ; 
 int ACPI_EDGE_SENSITIVE ; 
 int ACPI_LEVEL_SENSITIVE ; 
 int ACPI_MADT_PERFORMANCE_IRQ_MODE ; 
 int EINVAL ; 
 scalar_t__ WARN_ON (int) ; 
 struct acpi_madt_generic_interrupt* acpi_cpu_get_madt_gicc (int) ; 
 int acpi_register_gsi (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int arm_pmu_acpi_register_irq(int cpu)
{
	struct acpi_madt_generic_interrupt *gicc;
	int gsi, trigger;

	gicc = acpi_cpu_get_madt_gicc(cpu);
	if (WARN_ON(!gicc))
		return -EINVAL;

	gsi = gicc->performance_interrupt;

	/*
	 * Per the ACPI spec, the MADT cannot describe a PMU that doesn't
	 * have an interrupt. QEMU advertises this by using a GSI of zero,
	 * which is not known to be valid on any hardware despite being
	 * valid per the spec. Take the pragmatic approach and reject a
	 * GSI of zero for now.
	 */
	if (!gsi)
		return 0;

	if (gicc->flags & ACPI_MADT_PERFORMANCE_IRQ_MODE)
		trigger = ACPI_EDGE_SENSITIVE;
	else
		trigger = ACPI_LEVEL_SENSITIVE;

	/*
	 * Helpfully, the MADT GICC doesn't have a polarity flag for the
	 * "performance interrupt". Luckily, on compliant GICs the polarity is
	 * a fixed value in HW (for both SPIs and PPIs) that we cannot change
	 * from SW.
	 *
	 * Here we pass in ACPI_ACTIVE_HIGH to keep the core code happy. This
	 * may not match the real polarity, but that should not matter.
	 *
	 * Other interrupt controllers are not supported with ACPI.
	 */
	return acpi_register_gsi(NULL, gsi, trigger, ACPI_ACTIVE_HIGH);
}