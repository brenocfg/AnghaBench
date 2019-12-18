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
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int TWL6040_HSDACMODE ; 
 int TWL6040_HSDRVMODE ; 
 int /*<<< orphan*/  TWL6040_REG_HSLCTL ; 
 int /*<<< orphan*/  TWL6040_REG_HSRCTL ; 
 int twl6040_read (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  twl6040_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int headset_power_mode(struct snd_soc_component *component, int high_perf)
{
	int hslctl, hsrctl;
	int mask = TWL6040_HSDRVMODE | TWL6040_HSDACMODE;

	hslctl = twl6040_read(component, TWL6040_REG_HSLCTL);
	hsrctl = twl6040_read(component, TWL6040_REG_HSRCTL);

	if (high_perf) {
		hslctl &= ~mask;
		hsrctl &= ~mask;
	} else {
		hslctl |= mask;
		hsrctl |= mask;
	}

	twl6040_write(component, TWL6040_REG_HSLCTL, hslctl);
	twl6040_write(component, TWL6040_REG_HSRCTL, hsrctl);

	return 0;
}