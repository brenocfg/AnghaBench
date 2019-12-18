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
struct twl4030_priv {unsigned int* ctl_cache; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 unsigned int EIO ; 
 unsigned int TWL4030_CACHEREGNUM ; 
 int /*<<< orphan*/  TWL4030_MODULE_AUDIO_VOICE ; 
#define  TWL4030_REG_EAR_CTL 133 
#define  TWL4030_REG_HS_GAIN_SET 132 
#define  TWL4030_REG_PRECKL_CTL 131 
#define  TWL4030_REG_PRECKR_CTL 130 
#define  TWL4030_REG_PREDL_CTL 129 
#define  TWL4030_REG_PREDR_CTL 128 
 struct twl4030_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  twl_i2c_read_u8 (int /*<<< orphan*/ ,unsigned int*,unsigned int) ; 

__attribute__((used)) static unsigned int twl4030_read(struct snd_soc_component *component, unsigned int reg)
{
	struct twl4030_priv *twl4030 = snd_soc_component_get_drvdata(component);
	u8 value = 0;

	if (reg >= TWL4030_CACHEREGNUM)
		return -EIO;

	switch (reg) {
	case TWL4030_REG_EAR_CTL:
	case TWL4030_REG_PREDL_CTL:
	case TWL4030_REG_PREDR_CTL:
	case TWL4030_REG_PRECKL_CTL:
	case TWL4030_REG_PRECKR_CTL:
	case TWL4030_REG_HS_GAIN_SET:
		value = twl4030->ctl_cache[reg - TWL4030_REG_EAR_CTL];
		break;
	default:
		twl_i2c_read_u8(TWL4030_MODULE_AUDIO_VOICE, &value, reg);
		break;
	}

	return value;
}