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
struct ssm2602_priv {int /*<<< orphan*/  regmap; int /*<<< orphan*/  sysclk; } ;
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_hw_params {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IFACE_AUDIO_DATA_LEN ; 
 int /*<<< orphan*/  SSM2602_IFACE ; 
 int /*<<< orphan*/  SSM2602_SRATE ; 
 int /*<<< orphan*/  params_rate (struct snd_pcm_hw_params*) ; 
 int params_width (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct ssm2602_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int ssm2602_get_coeff (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ssm2602_hw_params(struct snd_pcm_substream *substream,
	struct snd_pcm_hw_params *params,
	struct snd_soc_dai *dai)
{
	struct snd_soc_component *component = dai->component;
	struct ssm2602_priv *ssm2602 = snd_soc_component_get_drvdata(component);
	int srate = ssm2602_get_coeff(ssm2602->sysclk, params_rate(params));
	unsigned int iface;

	if (srate < 0)
		return srate;

	regmap_write(ssm2602->regmap, SSM2602_SRATE, srate);

	/* bit size */
	switch (params_width(params)) {
	case 16:
		iface = 0x0;
		break;
	case 20:
		iface = 0x4;
		break;
	case 24:
		iface = 0x8;
		break;
	case 32:
		iface = 0xc;
		break;
	default:
		return -EINVAL;
	}
	regmap_update_bits(ssm2602->regmap, SSM2602_IFACE,
		IFACE_AUDIO_DATA_LEN, iface);
	return 0;
}