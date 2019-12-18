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
struct dmi_system_id {scalar_t__ driver_data; } ;

/* Variables and functions */
 unsigned long APL_RVP ; 
 int /*<<< orphan*/  apl_table ; 
 struct dmi_system_id* dmi_first_match (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct snd_soc_acpi_mach *apl_quirk(void *arg)
{
	struct snd_soc_acpi_mach *mach = arg;
	const struct dmi_system_id *dmi_id;
	unsigned long apl_machine_id;

	dmi_id = dmi_first_match(apl_table);
	if (dmi_id) {
		apl_machine_id = (unsigned long)dmi_id->driver_data;
		if (apl_machine_id == APL_RVP)
			return NULL;
	}

	return mach;
}