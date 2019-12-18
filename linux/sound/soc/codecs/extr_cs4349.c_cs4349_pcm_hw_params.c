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
struct snd_soc_component {int dummy; } ;
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct cs4349_private {int mode; int /*<<< orphan*/  rate; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS4349_MODE ; 
 int DIF_I2S ; 
 int DIF_LEFT_JST ; 
 int /*<<< orphan*/  DIF_MASK ; 
 int DIF_RGHT_JST16 ; 
 int DIF_RGHT_JST24 ; 
 int EINVAL ; 
 int /*<<< orphan*/  MODE_FORMAT (int) ; 
#define  SND_SOC_DAIFMT_I2S 130 
#define  SND_SOC_DAIFMT_LEFT_J 129 
#define  SND_SOC_DAIFMT_RIGHT_J 128 
 int /*<<< orphan*/  params_rate (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  params_width (struct snd_pcm_hw_params*) ; 
 struct cs4349_private* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cs4349_pcm_hw_params(struct snd_pcm_substream *substream,
			    struct snd_pcm_hw_params *params,
			    struct snd_soc_dai *dai)
{
	struct snd_soc_component *component = dai->component;
	struct cs4349_private *cs4349 = snd_soc_component_get_drvdata(component);
	int fmt, ret;

	cs4349->rate = params_rate(params);

	switch (cs4349->mode) {
	case SND_SOC_DAIFMT_I2S:
		fmt = DIF_I2S;
		break;
	case SND_SOC_DAIFMT_LEFT_J:
		fmt = DIF_LEFT_JST;
		break;
	case SND_SOC_DAIFMT_RIGHT_J:
		switch (params_width(params)) {
		case 16:
			fmt = DIF_RGHT_JST16;
			break;
		case 24:
			fmt = DIF_RGHT_JST24;
			break;
		default:
			return -EINVAL;
		}
		break;
	default:
		return -EINVAL;
	}

	ret = snd_soc_component_update_bits(component, CS4349_MODE, DIF_MASK,
				  MODE_FORMAT(fmt));
	if (ret < 0)
		return ret;

	return 0;
}