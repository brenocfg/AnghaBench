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
 scalar_t__ BYT_THINKPAD_10 ; 
 scalar_t__ byt_machine_id ; 
 int /*<<< orphan*/  byt_table ; 
 struct snd_soc_acpi_mach byt_thinkpad_10 ; 
 int /*<<< orphan*/  dmi_check_system (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct snd_soc_acpi_mach *byt_quirk(void *arg)
{
	struct snd_soc_acpi_mach *mach = arg;

	dmi_check_system(byt_table);

	if (byt_machine_id == BYT_THINKPAD_10)
		return &byt_thinkpad_10;
	else
		return mach;
}