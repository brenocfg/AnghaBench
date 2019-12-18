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
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct ak4104_private {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  AK4104_REG_CHN_STATUS (int) ; 
 int EINVAL ; 
 int IEC958_AES0_CON_NOT_COPYRIGHT ; 
 int IEC958_AES3_CON_FS_176400 ; 
 int IEC958_AES3_CON_FS_192000 ; 
 int IEC958_AES3_CON_FS_22050 ; 
 int IEC958_AES3_CON_FS_24000 ; 
 int IEC958_AES3_CON_FS_32000 ; 
 int IEC958_AES3_CON_FS_44100 ; 
 int IEC958_AES3_CON_FS_48000 ; 
 int IEC958_AES3_CON_FS_88200 ; 
 int IEC958_AES3_CON_FS_96000 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int params_rate (struct snd_pcm_hw_params*) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct ak4104_private* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int ak4104_hw_params(struct snd_pcm_substream *substream,
			    struct snd_pcm_hw_params *params,
			    struct snd_soc_dai *dai)
{
	struct snd_soc_component *component = dai->component;
	struct ak4104_private *ak4104 = snd_soc_component_get_drvdata(component);
	int ret, val = 0;

	/* set the IEC958 bits: consumer mode, no copyright bit */
	val |= IEC958_AES0_CON_NOT_COPYRIGHT;
	regmap_write(ak4104->regmap, AK4104_REG_CHN_STATUS(0), val);

	val = 0;

	switch (params_rate(params)) {
	case 22050:
		val |= IEC958_AES3_CON_FS_22050;
		break;
	case 24000:
		val |= IEC958_AES3_CON_FS_24000;
		break;
	case 32000:
		val |= IEC958_AES3_CON_FS_32000;
		break;
	case 44100:
		val |= IEC958_AES3_CON_FS_44100;
		break;
	case 48000:
		val |= IEC958_AES3_CON_FS_48000;
		break;
	case 88200:
		val |= IEC958_AES3_CON_FS_88200;
		break;
	case 96000:
		val |= IEC958_AES3_CON_FS_96000;
		break;
	case 176400:
		val |= IEC958_AES3_CON_FS_176400;
		break;
	case 192000:
		val |= IEC958_AES3_CON_FS_192000;
		break;
	default:
		dev_err(component->dev, "unsupported sampling rate\n");
		return -EINVAL;
	}

	ret = regmap_write(ak4104->regmap, AK4104_REG_CHN_STATUS(3), val);
	if (ret < 0)
		return ret;

	return 0;
}