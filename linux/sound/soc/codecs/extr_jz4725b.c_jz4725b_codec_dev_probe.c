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
struct regmap {int dummy; } ;
struct jz_icdc {int /*<<< orphan*/  clk; struct regmap* regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  JZ4725B_CODEC_REG_AICR ; 
 int /*<<< orphan*/  JZ4725B_CODEC_REG_CCR1 ; 
 int REG_AICR_CONFIG1_OFFSET ; 
 int REG_CCR1_CONFIG4_OFFSET ; 
 int /*<<< orphan*/  clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_write (struct regmap*,int /*<<< orphan*/ ,int) ; 
 struct jz_icdc* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int jz4725b_codec_dev_probe(struct snd_soc_component *component)
{
	struct jz_icdc *icdc = snd_soc_component_get_drvdata(component);
	struct regmap *map = icdc->regmap;

	clk_prepare_enable(icdc->clk);

	/* Write CONFIGn (n=1 to 8) bits.
	 * The value 0x0f is specified in the datasheet as a requirement.
	 */
	regmap_write(map, JZ4725B_CODEC_REG_AICR,
		     0xf << REG_AICR_CONFIG1_OFFSET);
	regmap_write(map, JZ4725B_CODEC_REG_CCR1,
		     0x0 << REG_CCR1_CONFIG4_OFFSET);

	return 0;
}