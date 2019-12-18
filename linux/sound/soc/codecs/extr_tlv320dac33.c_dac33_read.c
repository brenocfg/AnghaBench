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
struct tlv320dac33_priv {int /*<<< orphan*/  i2c; scalar_t__ chip_power; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int dac33_read_reg_cache (struct snd_soc_component*,unsigned int) ; 
 int /*<<< orphan*/  dac33_write_reg_cache (struct snd_soc_component*,unsigned int,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int i2c_smbus_read_byte_data (int /*<<< orphan*/ ,int) ; 
 struct tlv320dac33_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int dac33_read(struct snd_soc_component *component, unsigned int reg,
		      u8 *value)
{
	struct tlv320dac33_priv *dac33 = snd_soc_component_get_drvdata(component);
	int val, ret = 0;

	*value = reg & 0xff;

	/* If powered off, return the cached value */
	if (dac33->chip_power) {
		val = i2c_smbus_read_byte_data(dac33->i2c, value[0]);
		if (val < 0) {
			dev_err(component->dev, "Read failed (%d)\n", val);
			value[0] = dac33_read_reg_cache(component, reg);
			ret = val;
		} else {
			value[0] = val;
			dac33_write_reg_cache(component, reg, val);
		}
	} else {
		value[0] = dac33_read_reg_cache(component, reg);
	}

	return ret;
}