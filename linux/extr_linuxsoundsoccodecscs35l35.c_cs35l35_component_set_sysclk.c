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
struct cs35l35_private {unsigned int sysclk; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS35L35_CLK_CTL1 ; 
 int /*<<< orphan*/  CS35L35_CLK_SOURCE_MASK ; 
 int CS35L35_CLK_SOURCE_MCLK ; 
 int CS35L35_CLK_SOURCE_PDM ; 
 int CS35L35_CLK_SOURCE_SCLK ; 
 int CS35L35_CLK_SOURCE_SHIFT ; 
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct cs35l35_private* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int cs35l35_component_set_sysclk(struct snd_soc_component *component,
				int clk_id, int source, unsigned int freq,
				int dir)
{
	struct cs35l35_private *cs35l35 = snd_soc_component_get_drvdata(component);
	int clksrc;
	int ret = 0;

	switch (clk_id) {
	case 0:
		clksrc = CS35L35_CLK_SOURCE_MCLK;
		break;
	case 1:
		clksrc = CS35L35_CLK_SOURCE_SCLK;
		break;
	case 2:
		clksrc = CS35L35_CLK_SOURCE_PDM;
		break;
	default:
		dev_err(component->dev, "Invalid CLK Source\n");
		return -EINVAL;
	}

	switch (freq) {
	case 5644800:
	case 6144000:
	case 11289600:
	case 12000000:
	case 12288000:
	case 13000000:
	case 22579200:
	case 24000000:
	case 24576000:
	case 26000000:
		cs35l35->sysclk = freq;
		break;
	default:
		dev_err(component->dev, "Invalid CLK Frequency Input : %d\n", freq);
		return -EINVAL;
	}

	ret = regmap_update_bits(cs35l35->regmap, CS35L35_CLK_CTL1,
				CS35L35_CLK_SOURCE_MASK,
				clksrc << CS35L35_CLK_SOURCE_SHIFT);
	if (ret != 0) {
		dev_err(component->dev, "Failed to set sysclk %d\n", ret);
		return ret;
	}

	return ret;
}