#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct snd_soc_dai {int /*<<< orphan*/  dev; struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct TYPE_2__ {struct snd_soc_component* component; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SNDRV_PCM_FORMAT_S16_LE 131 
#define  SNDRV_PCM_FORMAT_S20_3LE 130 
#define  SNDRV_PCM_FORMAT_S24_LE 129 
#define  SNDRV_PCM_FORMAT_S32_LE 128 
 int /*<<< orphan*/  TAS5713_SERIAL_DATA_INTERFACE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int params_format (struct snd_pcm_hw_params*) ; 
 TYPE_1__* priv_data ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int tas5713_hw_params(struct snd_pcm_substream *substream,
			    struct snd_pcm_hw_params *params,
			    struct snd_soc_dai *dai)
{
	u16 blen = 0x00;

	struct snd_soc_component *component = dai->component;
	priv_data->component = component;

	switch (params_format(params)) {
	case SNDRV_PCM_FORMAT_S16_LE:
		blen = 0x03;
		break;
	case SNDRV_PCM_FORMAT_S20_3LE:
		blen = 0x1;
		break;
	case SNDRV_PCM_FORMAT_S24_LE:
		blen = 0x04;
		break;
	case SNDRV_PCM_FORMAT_S32_LE:
		blen = 0x05;
		break;
	default:
		dev_err(dai->dev, "Unsupported word length: %u\n",
			params_format(params));
		return -EINVAL;
	}

	// set word length
	snd_soc_component_update_bits(component, TAS5713_SERIAL_DATA_INTERFACE, 0x7, blen);

	return 0;
}