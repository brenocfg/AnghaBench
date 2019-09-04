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
typedef  unsigned int u16 ;
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_hw_params {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int ISABELLE_AIF_LENGTH_20 ; 
 unsigned int ISABELLE_AIF_LENGTH_32 ; 
 int /*<<< orphan*/  ISABELLE_AIF_LENGTH_MASK ; 
 unsigned int ISABELLE_FS_RATE_11 ; 
 unsigned int ISABELLE_FS_RATE_12 ; 
 unsigned int ISABELLE_FS_RATE_16 ; 
 unsigned int ISABELLE_FS_RATE_22 ; 
 unsigned int ISABELLE_FS_RATE_24 ; 
 unsigned int ISABELLE_FS_RATE_32 ; 
 unsigned int ISABELLE_FS_RATE_44 ; 
 unsigned int ISABELLE_FS_RATE_48 ; 
 unsigned int ISABELLE_FS_RATE_8 ; 
 int /*<<< orphan*/  ISABELLE_FS_RATE_CFG_REG ; 
 int /*<<< orphan*/  ISABELLE_FS_RATE_MASK ; 
 int /*<<< orphan*/  ISABELLE_INTF_CFG_REG ; 
 int params_rate (struct snd_pcm_hw_params*) ; 
 int params_width (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int isabelle_hw_params(struct snd_pcm_substream *substream,
			      struct snd_pcm_hw_params *params,
			      struct snd_soc_dai *dai)
{
	struct snd_soc_component *component = dai->component;
	u16 aif = 0;
	unsigned int fs_val = 0;

	switch (params_rate(params)) {
	case 8000:
		fs_val = ISABELLE_FS_RATE_8;
		break;
	case 11025:
		fs_val = ISABELLE_FS_RATE_11;
		break;
	case 12000:
		fs_val = ISABELLE_FS_RATE_12;
		break;
	case 16000:
		fs_val = ISABELLE_FS_RATE_16;
		break;
	case 22050:
		fs_val = ISABELLE_FS_RATE_22;
		break;
	case 24000:
		fs_val = ISABELLE_FS_RATE_24;
		break;
	case 32000:
		fs_val = ISABELLE_FS_RATE_32;
		break;
	case 44100:
		fs_val = ISABELLE_FS_RATE_44;
		break;
	case 48000:
		fs_val = ISABELLE_FS_RATE_48;
		break;
	default:
		return -EINVAL;
	}

	snd_soc_component_update_bits(component, ISABELLE_FS_RATE_CFG_REG,
			ISABELLE_FS_RATE_MASK, fs_val);

	/* bit size */
	switch (params_width(params)) {
	case 20:
		aif |= ISABELLE_AIF_LENGTH_20;
		break;
	case 32:
		aif |= ISABELLE_AIF_LENGTH_32;
		break;
	default:
		return -EINVAL;
	}

	snd_soc_component_update_bits(component, ISABELLE_INTF_CFG_REG,
			ISABELLE_AIF_LENGTH_MASK, aif);

	return 0;
}