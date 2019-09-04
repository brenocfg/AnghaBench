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
struct twl6040_data {int dl1_unmuted; int dl2_unmuted; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
#define  TWL6040_REG_EARCTL 132 
#define  TWL6040_REG_HFLCTL 131 
#define  TWL6040_REG_HFRCTL 130 
#define  TWL6040_REG_HSLCTL 129 
#define  TWL6040_REG_HSRCTL 128 
 struct twl6040_data* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static bool twl6040_can_write_to_chip(struct snd_soc_component *component,
				  unsigned int reg)
{
	struct twl6040_data *priv = snd_soc_component_get_drvdata(component);

	switch (reg) {
	case TWL6040_REG_HSLCTL:
	case TWL6040_REG_HSRCTL:
	case TWL6040_REG_EARCTL:
		/* DL1 path */
		return priv->dl1_unmuted;
	case TWL6040_REG_HFLCTL:
	case TWL6040_REG_HFRCTL:
		return priv->dl2_unmuted;
	default:
		return true;
	}
}