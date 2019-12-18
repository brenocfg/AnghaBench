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
typedef  int uint32_t ;
struct snd_soc_dai {int /*<<< orphan*/  component; } ;
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct jz4740_codec {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  JZ4740_CODEC_2_SAMPLE_RATE_MASK ; 
 int JZ4740_CODEC_2_SAMPLE_RATE_OFFSET ; 
 int /*<<< orphan*/  JZ4740_REG_CODEC_2 ; 
 int params_rate (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct jz4740_codec* snd_soc_component_get_drvdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int jz4740_codec_hw_params(struct snd_pcm_substream *substream,
	struct snd_pcm_hw_params *params, struct snd_soc_dai *dai)
{
	struct jz4740_codec *jz4740_codec = snd_soc_component_get_drvdata(dai->component);
	uint32_t val;

	switch (params_rate(params)) {
	case 8000:
		val = 0;
		break;
	case 11025:
		val = 1;
		break;
	case 12000:
		val = 2;
		break;
	case 16000:
		val = 3;
		break;
	case 22050:
		val = 4;
		break;
	case 24000:
		val = 5;
		break;
	case 32000:
		val = 6;
		break;
	case 44100:
		val = 7;
		break;
	case 48000:
		val = 8;
		break;
	default:
		return -EINVAL;
	}

	val <<= JZ4740_CODEC_2_SAMPLE_RATE_OFFSET;

	regmap_update_bits(jz4740_codec->regmap, JZ4740_REG_CODEC_2,
				JZ4740_CODEC_2_SAMPLE_RATE_MASK, val);

	return 0;
}