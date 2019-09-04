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
typedef  int u8 ;
struct snd_soc_dapm_context {int dummy; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int TWL6040_HSDACMODE ; 
 int /*<<< orphan*/  TWL6040_REG_HSLCTL ; 
 struct snd_soc_dapm_context* snd_soc_component_get_dapm (struct snd_soc_component*) ; 
 scalar_t__ snd_soc_dapm_get_pin_status (struct snd_soc_dapm_context*,char*) ; 
 int twl6040_read (struct snd_soc_component*,int /*<<< orphan*/ ) ; 

int twl6040_get_dl1_gain(struct snd_soc_component *component)
{
	struct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);

	if (snd_soc_dapm_get_pin_status(dapm, "EP"))
		return -1; /* -1dB */

	if (snd_soc_dapm_get_pin_status(dapm, "HSOR") ||
		snd_soc_dapm_get_pin_status(dapm, "HSOL")) {

		u8 val = twl6040_read(component, TWL6040_REG_HSLCTL);
		if (val & TWL6040_HSDACMODE)
			/* HSDACL in LP mode */
			return -8; /* -8dB */
		else
			/* HSDACL in HP mode */
			return -1; /* -1dB */
	}
	return 0; /* 0dB */
}