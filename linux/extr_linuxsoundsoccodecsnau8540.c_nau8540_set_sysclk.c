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
struct nau8540 {int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int EINVAL ; 
#define  NAU8540_CLK_DIS 130 
#define  NAU8540_CLK_INTERNAL 129 
#define  NAU8540_CLK_MCLK 128 
 int /*<<< orphan*/  NAU8540_CLK_SRC_MASK ; 
 int /*<<< orphan*/  NAU8540_CLK_SRC_MCLK ; 
 int /*<<< orphan*/  NAU8540_CLK_SRC_VCO ; 
 int /*<<< orphan*/  NAU8540_DCO_EN ; 
 int /*<<< orphan*/  NAU8540_REG_CLOCK_SRC ; 
 int /*<<< orphan*/  NAU8540_REG_FLL6 ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nau8540* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int nau8540_set_sysclk(struct snd_soc_component *component,
	int clk_id, int source, unsigned int freq, int dir)
{
	struct nau8540 *nau8540 = snd_soc_component_get_drvdata(component);

	switch (clk_id) {
	case NAU8540_CLK_DIS:
	case NAU8540_CLK_MCLK:
		regmap_update_bits(nau8540->regmap, NAU8540_REG_CLOCK_SRC,
			NAU8540_CLK_SRC_MASK, NAU8540_CLK_SRC_MCLK);
		regmap_update_bits(nau8540->regmap, NAU8540_REG_FLL6,
			NAU8540_DCO_EN, 0);
		break;

	case NAU8540_CLK_INTERNAL:
		regmap_update_bits(nau8540->regmap, NAU8540_REG_FLL6,
			NAU8540_DCO_EN, NAU8540_DCO_EN);
		regmap_update_bits(nau8540->regmap, NAU8540_REG_CLOCK_SRC,
			NAU8540_CLK_SRC_MASK, NAU8540_CLK_SRC_VCO);
		break;

	default:
		dev_err(nau8540->dev, "Invalid clock id (%d)\n", clk_id);
		return -EINVAL;
	}

	dev_dbg(nau8540->dev, "Sysclk is %dHz and clock id is %d\n",
		freq, clk_id);

	return 0;
}