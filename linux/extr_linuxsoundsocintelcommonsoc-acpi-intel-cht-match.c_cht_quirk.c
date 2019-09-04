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
struct snd_soc_acpi_mach {int dummy; } ;

/* Variables and functions */
 scalar_t__ CHT_SURFACE_MACH ; 
 scalar_t__ cht_machine_id ; 
 struct snd_soc_acpi_mach cht_surface_mach ; 
 int /*<<< orphan*/  cht_table ; 
 int /*<<< orphan*/  dmi_check_system (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct snd_soc_acpi_mach *cht_quirk(void *arg)
{
	struct snd_soc_acpi_mach *mach = arg;

	dmi_check_system(cht_table);

	if (cht_machine_id == CHT_SURFACE_MACH)
		return &cht_surface_mach;
	else
		return mach;
}