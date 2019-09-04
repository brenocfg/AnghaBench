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
 int /*<<< orphan*/  AC97_GPIO_CFG ; 
 int /*<<< orphan*/  AC97_GPIO_PULL ; 
 unsigned short snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,unsigned short) ; 

__attribute__((used)) static int rear_amp_power(struct snd_soc_component *component, int power)
{
	unsigned short reg;

	if (power) {
		reg = snd_soc_component_read32(component, AC97_GPIO_CFG);
		snd_soc_component_write(component, AC97_GPIO_CFG, reg | 0x0100);
		reg = snd_soc_component_read32(component, AC97_GPIO_PULL);
		snd_soc_component_write(component, AC97_GPIO_PULL, reg | (1<<15));
	} else {
		reg = snd_soc_component_read32(component, AC97_GPIO_CFG);
		snd_soc_component_write(component, AC97_GPIO_CFG, reg & ~0x0100);
		reg = snd_soc_component_read32(component, AC97_GPIO_PULL);
		snd_soc_component_write(component, AC97_GPIO_PULL, reg & ~(1<<15));
	}

	return 0;
}