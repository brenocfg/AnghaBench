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
struct tfa9879_priv {scalar_t__ lsb_justified; } ;
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_hw_params {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int TFA9879_I2S_FS_11025 ; 
 int TFA9879_I2S_FS_12000 ; 
 int TFA9879_I2S_FS_16000 ; 
 int TFA9879_I2S_FS_22050 ; 
 int TFA9879_I2S_FS_24000 ; 
 int TFA9879_I2S_FS_32000 ; 
 int TFA9879_I2S_FS_44100 ; 
 int TFA9879_I2S_FS_48000 ; 
 int TFA9879_I2S_FS_64000 ; 
 int TFA9879_I2S_FS_8000 ; 
 int TFA9879_I2S_FS_88200 ; 
 int TFA9879_I2S_FS_96000 ; 
 int /*<<< orphan*/  TFA9879_I2S_FS_MASK ; 
 int TFA9879_I2S_FS_SHIFT ; 
 int TFA9879_I2S_SET_LSB_J_16 ; 
 int TFA9879_I2S_SET_LSB_J_24 ; 
 int /*<<< orphan*/  TFA9879_I2S_SET_MASK ; 
 int TFA9879_I2S_SET_SHIFT ; 
 int /*<<< orphan*/  TFA9879_SERIAL_INTERFACE_1 ; 
 int params_rate (struct snd_pcm_hw_params*) ; 
 int params_width (struct snd_pcm_hw_params*) ; 
 struct tfa9879_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int tfa9879_hw_params(struct snd_pcm_substream *substream,
			     struct snd_pcm_hw_params *params,
			     struct snd_soc_dai *dai)
{
	struct snd_soc_component *component = dai->component;
	struct tfa9879_priv *tfa9879 = snd_soc_component_get_drvdata(component);
	int fs;
	int i2s_set = 0;

	switch (params_rate(params)) {
	case 8000:
		fs = TFA9879_I2S_FS_8000;
		break;
	case 11025:
		fs = TFA9879_I2S_FS_11025;
		break;
	case 12000:
		fs = TFA9879_I2S_FS_12000;
		break;
	case 16000:
		fs = TFA9879_I2S_FS_16000;
		break;
	case 22050:
		fs = TFA9879_I2S_FS_22050;
		break;
	case 24000:
		fs = TFA9879_I2S_FS_24000;
		break;
	case 32000:
		fs = TFA9879_I2S_FS_32000;
		break;
	case 44100:
		fs = TFA9879_I2S_FS_44100;
		break;
	case 48000:
		fs = TFA9879_I2S_FS_48000;
		break;
	case 64000:
		fs = TFA9879_I2S_FS_64000;
		break;
	case 88200:
		fs = TFA9879_I2S_FS_88200;
		break;
	case 96000:
		fs = TFA9879_I2S_FS_96000;
		break;
	default:
		return -EINVAL;
	}

	switch (params_width(params)) {
	case 16:
		i2s_set = TFA9879_I2S_SET_LSB_J_16;
		break;
	case 24:
		i2s_set = TFA9879_I2S_SET_LSB_J_24;
		break;
	default:
		return -EINVAL;
	}

	if (tfa9879->lsb_justified)
		snd_soc_component_update_bits(component,
					      TFA9879_SERIAL_INTERFACE_1,
					      TFA9879_I2S_SET_MASK,
					      i2s_set << TFA9879_I2S_SET_SHIFT);

	snd_soc_component_update_bits(component, TFA9879_SERIAL_INTERFACE_1,
				      TFA9879_I2S_FS_MASK,
				      fs << TFA9879_I2S_FS_SHIFT);
	return 0;
}