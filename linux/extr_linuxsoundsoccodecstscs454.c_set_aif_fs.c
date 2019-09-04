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
struct snd_soc_component {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int FM_I2SMRATE_I2SMBM ; 
 int FM_I2SMRATE_I2SMBR ; 
 unsigned int FV_I2SMBM_0PT25 ; 
 unsigned int FV_I2SMBM_0PT5 ; 
 unsigned int FV_I2SMBM_1 ; 
 unsigned int FV_I2SMBM_2 ; 
 unsigned int FV_I2SMBR_32 ; 
 unsigned int FV_I2SMBR_44PT1 ; 
 unsigned int FV_I2SMBR_48 ; 
 unsigned int R_I2S1MRATE ; 
 unsigned int R_I2S2MRATE ; 
 unsigned int R_I2S3MRATE ; 
#define  TSCS454_DAI1_ID 130 
#define  TSCS454_DAI2_ID 129 
#define  TSCS454_DAI3_ID 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int snd_soc_component_update_bits (struct snd_soc_component*,unsigned int,int,unsigned int) ; 

__attribute__((used)) static int set_aif_fs(struct snd_soc_component *component,
		unsigned int id,
		unsigned int rate)
{
	unsigned int reg;
	unsigned int br;
	unsigned int bm;
	int ret;

	switch (rate) {
	case 8000:
		br = FV_I2SMBR_32;
		bm = FV_I2SMBM_0PT25;
		break;
	case 16000:
		br = FV_I2SMBR_32;
		bm = FV_I2SMBM_0PT5;
		break;
	case 24000:
		br = FV_I2SMBR_48;
		bm = FV_I2SMBM_0PT5;
		break;
	case 32000:
		br = FV_I2SMBR_32;
		bm = FV_I2SMBM_1;
		break;
	case 48000:
		br = FV_I2SMBR_48;
		bm = FV_I2SMBM_1;
		break;
	case 96000:
		br = FV_I2SMBR_48;
		bm = FV_I2SMBM_2;
		break;
	case 11025:
		br = FV_I2SMBR_44PT1;
		bm = FV_I2SMBM_0PT25;
		break;
	case 22050:
		br = FV_I2SMBR_44PT1;
		bm = FV_I2SMBM_0PT5;
		break;
	case 44100:
		br = FV_I2SMBR_44PT1;
		bm = FV_I2SMBM_1;
		break;
	case 88200:
		br = FV_I2SMBR_44PT1;
		bm = FV_I2SMBM_2;
		break;
	default:
		ret = -EINVAL;
		dev_err(component->dev, "Unsupported sample rate (%d)\n", ret);
		return ret;
	}

	switch (id) {
	case TSCS454_DAI1_ID:
		reg = R_I2S1MRATE;
		break;
	case TSCS454_DAI2_ID:
		reg = R_I2S2MRATE;
		break;
	case TSCS454_DAI3_ID:
		reg = R_I2S3MRATE;
		break;
	default:
		ret = -EINVAL;
		dev_err(component->dev, "DAI ID not recognized (%d)\n", ret);
		return ret;
	}

	ret = snd_soc_component_update_bits(component, reg,
			FM_I2SMRATE_I2SMBR | FM_I2SMRATE_I2SMBM, br|bm);
	if (ret < 0) {
		dev_err(component->dev,
				"Failed to update register (%d)\n", ret);
		return ret;
	}

	return 0;
}