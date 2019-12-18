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
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct rt5677_priv {int /*<<< orphan*/  dsp_cmd_lock; int /*<<< orphan*/  regmap_physical; struct snd_soc_component* component; } ;

/* Variables and functions */
 int /*<<< orphan*/  RT5677_DSP_I2C_ADDR_LSB ; 
 int /*<<< orphan*/  RT5677_DSP_I2C_ADDR_MSB ; 
 int /*<<< orphan*/  RT5677_DSP_I2C_DATA_LSB ; 
 int /*<<< orphan*/  RT5677_DSP_I2C_DATA_MSB ; 
 int /*<<< orphan*/  RT5677_DSP_I2C_OP_CODE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int rt5677_dsp_mode_i2c_read_addr(
	struct rt5677_priv *rt5677, unsigned int addr, unsigned int *value)
{
	struct snd_soc_component *component = rt5677->component;
	int ret;
	unsigned int msb, lsb;

	mutex_lock(&rt5677->dsp_cmd_lock);

	ret = regmap_write(rt5677->regmap_physical, RT5677_DSP_I2C_ADDR_MSB,
		addr >> 16);
	if (ret < 0) {
		dev_err(component->dev, "Failed to set addr msb value: %d\n", ret);
		goto err;
	}

	ret = regmap_write(rt5677->regmap_physical, RT5677_DSP_I2C_ADDR_LSB,
		addr & 0xffff);
	if (ret < 0) {
		dev_err(component->dev, "Failed to set addr lsb value: %d\n", ret);
		goto err;
	}

	ret = regmap_write(rt5677->regmap_physical, RT5677_DSP_I2C_OP_CODE,
		0x0002);
	if (ret < 0) {
		dev_err(component->dev, "Failed to set op code value: %d\n", ret);
		goto err;
	}

	regmap_read(rt5677->regmap_physical, RT5677_DSP_I2C_DATA_MSB, &msb);
	regmap_read(rt5677->regmap_physical, RT5677_DSP_I2C_DATA_LSB, &lsb);
	*value = (msb << 16) | lsb;

err:
	mutex_unlock(&rt5677->dsp_cmd_lock);

	return ret;
}