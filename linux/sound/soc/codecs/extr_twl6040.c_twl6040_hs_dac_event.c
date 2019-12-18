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
typedef  int /*<<< orphan*/  u8 ;
struct snd_soc_dapm_widget {int /*<<< orphan*/  dapm; } ;
struct snd_soc_component {int dummy; } ;
struct snd_kcontrol {int dummy; } ;

/* Variables and functions */
 scalar_t__ SND_SOC_DAPM_EVENT_ON (int) ; 
 int /*<<< orphan*/  TWL6040_HSDACENA ; 
 int /*<<< orphan*/  TWL6040_REG_HSLCTL ; 
 int /*<<< orphan*/  TWL6040_REG_HSRCTL ; 
 int /*<<< orphan*/  msleep (int) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  twl6040_read (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  twl6040_write (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int twl6040_hs_dac_event(struct snd_soc_dapm_widget *w,
			struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	u8 hslctl, hsrctl;

	/*
	 * Workaround for Headset DC offset caused pop noise:
	 * Both HS DAC need to be turned on (before the HS driver) and off at
	 * the same time.
	 */
	hslctl = twl6040_read(component, TWL6040_REG_HSLCTL);
	hsrctl = twl6040_read(component, TWL6040_REG_HSRCTL);
	if (SND_SOC_DAPM_EVENT_ON(event)) {
		hslctl |= TWL6040_HSDACENA;
		hsrctl |= TWL6040_HSDACENA;
	} else {
		hslctl &= ~TWL6040_HSDACENA;
		hsrctl &= ~TWL6040_HSDACENA;
	}
	twl6040_write(component, TWL6040_REG_HSLCTL, hslctl);
	twl6040_write(component, TWL6040_REG_HSRCTL, hsrctl);

	msleep(1);
	return 0;
}