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
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct cs35l34_private {unsigned int mclk_int; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
#define  CS35L34_MCLK_11289 133 
#define  CS35L34_MCLK_12 132 
#define  CS35L34_MCLK_12288 131 
#define  CS35L34_MCLK_5644 130 
#define  CS35L34_MCLK_6 129 
#define  CS35L34_MCLK_6144 128 
 int /*<<< orphan*/  CS35L34_MCLK_CTL ; 
 unsigned int CS35L34_MCLK_DIV ; 
 unsigned int CS35L34_MCLK_RATE_5P6448 ; 
 unsigned int CS35L34_MCLK_RATE_6P0000 ; 
 unsigned int CS35L34_MCLK_RATE_6P1440 ; 
 unsigned int CS35L34_MCLK_RATE_MASK ; 
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 struct cs35l34_private* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int cs35l34_dai_set_sysclk(struct snd_soc_dai *dai,
				int clk_id, unsigned int freq, int dir)
{
	struct snd_soc_component *component = dai->component;
	struct cs35l34_private *cs35l34 = snd_soc_component_get_drvdata(component);
	unsigned int value;

	switch (freq) {
	case CS35L34_MCLK_5644:
		value = CS35L34_MCLK_RATE_5P6448;
		cs35l34->mclk_int = freq;
	break;
	case CS35L34_MCLK_6:
		value = CS35L34_MCLK_RATE_6P0000;
		cs35l34->mclk_int = freq;
	break;
	case CS35L34_MCLK_6144:
		value = CS35L34_MCLK_RATE_6P1440;
		cs35l34->mclk_int = freq;
	break;
	case CS35L34_MCLK_11289:
		value = CS35L34_MCLK_DIV | CS35L34_MCLK_RATE_5P6448;
		cs35l34->mclk_int = freq / 2;
	break;
	case CS35L34_MCLK_12:
		value = CS35L34_MCLK_DIV | CS35L34_MCLK_RATE_6P0000;
		cs35l34->mclk_int = freq / 2;
	break;
	case CS35L34_MCLK_12288:
		value = CS35L34_MCLK_DIV | CS35L34_MCLK_RATE_6P1440;
		cs35l34->mclk_int = freq / 2;
	break;
	default:
		dev_err(component->dev, "ERROR: Invalid Frequency %d\n", freq);
		cs35l34->mclk_int = 0;
		return -EINVAL;
	}
	regmap_update_bits(cs35l34->regmap, CS35L34_MCLK_CTL,
			CS35L34_MCLK_DIV | CS35L34_MCLK_RATE_MASK, value);
	return 0;
}