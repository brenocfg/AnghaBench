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
struct cs35l33_private {unsigned int mclk_int; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS35L33_CLK_CTL ; 
 int /*<<< orphan*/  CS35L33_MCLKDIV2 ; 
#define  CS35L33_MCLK_11289 133 
#define  CS35L33_MCLK_12 132 
#define  CS35L33_MCLK_12288 131 
#define  CS35L33_MCLK_5644 130 
#define  CS35L33_MCLK_6 129 
#define  CS35L33_MCLK_6144 128 
 int EINVAL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cs35l33_private* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int cs35l33_component_set_sysclk(struct snd_soc_component *component,
		int clk_id, int source, unsigned int freq, int dir)
{
	struct cs35l33_private *cs35l33 = snd_soc_component_get_drvdata(component);

	switch (freq) {
	case CS35L33_MCLK_5644:
	case CS35L33_MCLK_6:
	case CS35L33_MCLK_6144:
		regmap_update_bits(cs35l33->regmap, CS35L33_CLK_CTL,
			CS35L33_MCLKDIV2, 0);
		cs35l33->mclk_int = freq;
		break;
	case CS35L33_MCLK_11289:
	case CS35L33_MCLK_12:
	case CS35L33_MCLK_12288:
		regmap_update_bits(cs35l33->regmap, CS35L33_CLK_CTL,
			CS35L33_MCLKDIV2, CS35L33_MCLKDIV2);
		cs35l33->mclk_int = freq/2;
		break;
	default:
		cs35l33->mclk_int = 0;
		return -EINVAL;
	}

	dev_dbg(component->dev, "external mclk freq=%d, internal mclk freq=%d\n",
		freq, cs35l33->mclk_int);

	return 0;
}