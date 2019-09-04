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

/* Variables and functions */
 int EINVAL ; 
 int PCM_INF2_18WL ; 
 int /*<<< orphan*/  PM860X_I2S_IFACE_2 ; 
 int /*<<< orphan*/  PM860X_I2S_IFACE_4 ; 
 int params_rate (struct snd_pcm_hw_params*) ; 
 int params_width (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,unsigned char) ; 

__attribute__((used)) static int pm860x_i2s_hw_params(struct snd_pcm_substream *substream,
				struct snd_pcm_hw_params *params,
				struct snd_soc_dai *dai)
{
	struct snd_soc_component *component = dai->component;
	unsigned char inf;

	/* bit size */
	switch (params_width(params)) {
	case 16:
		inf = 0;
		break;
	case 18:
		inf = PCM_INF2_18WL;
		break;
	default:
		return -EINVAL;
	}
	snd_soc_component_update_bits(component, PM860X_I2S_IFACE_2, PCM_INF2_18WL, inf);

	/* sample rate */
	switch (params_rate(params)) {
	case 8000:
		inf = 0;
		break;
	case 11025:
		inf = 1;
		break;
	case 16000:
		inf = 3;
		break;
	case 22050:
		inf = 4;
		break;
	case 32000:
		inf = 6;
		break;
	case 44100:
		inf = 7;
		break;
	case 48000:
		inf = 8;
		break;
	default:
		return -EINVAL;
	}
	snd_soc_component_update_bits(component, PM860X_I2S_IFACE_4, 0xf, inf);

	return 0;
}