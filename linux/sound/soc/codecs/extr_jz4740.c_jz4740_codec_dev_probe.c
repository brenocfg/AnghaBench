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
struct jz4740_codec {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  JZ4740_CODEC_1_SW2_ENABLE ; 
 int /*<<< orphan*/  JZ4740_REG_CODEC_1 ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct jz4740_codec* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int jz4740_codec_dev_probe(struct snd_soc_component *component)
{
	struct jz4740_codec *jz4740_codec = snd_soc_component_get_drvdata(component);

	regmap_update_bits(jz4740_codec->regmap, JZ4740_REG_CODEC_1,
			JZ4740_CODEC_1_SW2_ENABLE, JZ4740_CODEC_1_SW2_ENABLE);

	return 0;
}