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
struct jz4740_codec {struct regmap* regmap; } ;
typedef  enum snd_soc_bias_level { ____Placeholder_snd_soc_bias_level } snd_soc_bias_level ;

/* Variables and functions */
 unsigned int JZ4740_CODEC_1_HEADPHONE_POWERDOWN_M ; 
 unsigned int JZ4740_CODEC_1_SUSPEND ; 
 unsigned int JZ4740_CODEC_1_VREF_AMP_DISABLE ; 
 unsigned int JZ4740_CODEC_1_VREF_DISABLE ; 
 int /*<<< orphan*/  JZ4740_REG_CODEC_1 ; 
#define  SND_SOC_BIAS_OFF 131 
#define  SND_SOC_BIAS_ON 130 
#define  SND_SOC_BIAS_PREPARE 129 
#define  SND_SOC_BIAS_STANDBY 128 
 int /*<<< orphan*/  jz4740_codec_wakeup (struct regmap*) ; 
 int /*<<< orphan*/  regcache_mark_dirty (struct regmap*) ; 
 int /*<<< orphan*/  regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int snd_soc_component_get_bias_level (struct snd_soc_component*) ; 
 struct jz4740_codec* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int jz4740_codec_set_bias_level(struct snd_soc_component *component,
	enum snd_soc_bias_level level)
{
	struct jz4740_codec *jz4740_codec = snd_soc_component_get_drvdata(component);
	struct regmap *regmap = jz4740_codec->regmap;
	unsigned int mask;
	unsigned int value;

	switch (level) {
	case SND_SOC_BIAS_ON:
		break;
	case SND_SOC_BIAS_PREPARE:
		mask = JZ4740_CODEC_1_VREF_DISABLE |
				JZ4740_CODEC_1_VREF_AMP_DISABLE |
				JZ4740_CODEC_1_HEADPHONE_POWERDOWN_M;
		value = 0;

		regmap_update_bits(regmap, JZ4740_REG_CODEC_1, mask, value);
		break;
	case SND_SOC_BIAS_STANDBY:
		/* The only way to clear the suspend flag is to reset the codec */
		if (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF)
			jz4740_codec_wakeup(regmap);

		mask = JZ4740_CODEC_1_VREF_DISABLE |
			JZ4740_CODEC_1_VREF_AMP_DISABLE |
			JZ4740_CODEC_1_HEADPHONE_POWERDOWN_M;
		value = JZ4740_CODEC_1_VREF_DISABLE |
			JZ4740_CODEC_1_VREF_AMP_DISABLE |
			JZ4740_CODEC_1_HEADPHONE_POWERDOWN_M;

		regmap_update_bits(regmap, JZ4740_REG_CODEC_1, mask, value);
		break;
	case SND_SOC_BIAS_OFF:
		mask = JZ4740_CODEC_1_SUSPEND;
		value = JZ4740_CODEC_1_SUSPEND;

		regmap_update_bits(regmap, JZ4740_REG_CODEC_1, mask, value);
		regcache_mark_dirty(regmap);
		break;
	default:
		break;
	}

	return 0;
}