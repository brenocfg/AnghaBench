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
typedef  unsigned int u8 ;
struct twl6040_data {unsigned int* dl12_cache; } ;
struct twl6040 {int dummy; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 unsigned int EIO ; 
 unsigned int TWL6040_CACHEREGNUM ; 
#define  TWL6040_REG_EARCTL 132 
#define  TWL6040_REG_HFLCTL 131 
#define  TWL6040_REG_HFRCTL 130 
#define  TWL6040_REG_HSLCTL 129 
#define  TWL6040_REG_HSRCTL 128 
 struct twl6040_data* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 struct twl6040* to_twl6040 (struct snd_soc_component*) ; 
 unsigned int twl6040_reg_read (struct twl6040*,unsigned int) ; 

__attribute__((used)) static unsigned int twl6040_read(struct snd_soc_component *component, unsigned int reg)
{
	struct twl6040_data *priv = snd_soc_component_get_drvdata(component);
	struct twl6040 *twl6040 = to_twl6040(component);
	u8 value;

	if (reg >= TWL6040_CACHEREGNUM)
		return -EIO;

	switch (reg) {
	case TWL6040_REG_HSLCTL:
	case TWL6040_REG_HSRCTL:
	case TWL6040_REG_EARCTL:
	case TWL6040_REG_HFLCTL:
	case TWL6040_REG_HFRCTL:
		value = priv->dl12_cache[reg - TWL6040_REG_HSLCTL];
		break;
	default:
		value = twl6040_reg_read(twl6040, reg);
		break;
	}

	return value;
}