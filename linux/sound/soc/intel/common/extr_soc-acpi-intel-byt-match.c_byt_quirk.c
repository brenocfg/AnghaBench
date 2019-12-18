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
#define  BYT_AEGEX_10 130 
#define  BYT_POV_P1006W 129 
#define  BYT_THINKPAD_10 128 
 int byt_machine_id ; 
 struct snd_soc_acpi_mach byt_pov_p1006w ; 
 int /*<<< orphan*/  byt_table ; 
 struct snd_soc_acpi_mach byt_thinkpad_10 ; 
 int /*<<< orphan*/  dmi_check_system (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct snd_soc_acpi_mach *byt_quirk(void *arg)
{
	struct snd_soc_acpi_mach *mach = arg;

	dmi_check_system(byt_table);

	switch (byt_machine_id) {
	case BYT_THINKPAD_10:
	case BYT_AEGEX_10:
		return &byt_thinkpad_10;
	case BYT_POV_P1006W:
		return &byt_pov_p1006w;
	default:
		return mach;
	}
}