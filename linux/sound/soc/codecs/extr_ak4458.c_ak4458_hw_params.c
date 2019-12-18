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
typedef  int u8 ;
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct ak4458_priv {int fs; int fmt; int /*<<< orphan*/  slot_width; } ;

/* Variables and functions */
 int /*<<< orphan*/  AK4458_00_CONTROL1 ; 
 int AK4458_DIF_16BIT_LSB ; 
 int AK4458_DIF_24BIT_I2S ; 
 int AK4458_DIF_32BIT_I2S ; 
 int AK4458_DIF_32BIT_LSB ; 
 int AK4458_DIF_32BIT_MSB ; 
 int AK4458_DIF_MASK ; 
 int EINVAL ; 
#define  SND_SOC_DAIFMT_DSP_B 131 
#define  SND_SOC_DAIFMT_I2S 130 
#define  SND_SOC_DAIFMT_LEFT_J 129 
#define  SND_SOC_DAIFMT_RIGHT_J 128 
 int /*<<< orphan*/  ak4458_rstn_control (struct snd_soc_component*,int) ; 
 int max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  params_physical_width (struct snd_pcm_hw_params*) ; 
 int params_rate (struct snd_pcm_hw_params*) ; 
 struct ak4458_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int ak4458_hw_params(struct snd_pcm_substream *substream,
			    struct snd_pcm_hw_params *params,
			    struct snd_soc_dai *dai)
{
	struct snd_soc_component *component = dai->component;
	struct ak4458_priv *ak4458 = snd_soc_component_get_drvdata(component);
	int pcm_width = max(params_physical_width(params), ak4458->slot_width);
	int nfs1;
	u8 format;

	nfs1 = params_rate(params);
	ak4458->fs = nfs1;

	/* Master Clock Frequency Auto Setting Mode Enable */
	snd_soc_component_update_bits(component, AK4458_00_CONTROL1, 0x80, 0x80);

	switch (pcm_width) {
	case 16:
		if (ak4458->fmt == SND_SOC_DAIFMT_I2S)
			format = AK4458_DIF_24BIT_I2S;
		else
			format = AK4458_DIF_16BIT_LSB;
		break;
	case 32:
		switch (ak4458->fmt) {
		case SND_SOC_DAIFMT_I2S:
			format = AK4458_DIF_32BIT_I2S;
			break;
		case SND_SOC_DAIFMT_LEFT_J:
			format = AK4458_DIF_32BIT_MSB;
			break;
		case SND_SOC_DAIFMT_RIGHT_J:
			format = AK4458_DIF_32BIT_LSB;
			break;
		case SND_SOC_DAIFMT_DSP_B:
			format = AK4458_DIF_32BIT_MSB;
			break;
		default:
			return -EINVAL;
		}
		break;
	default:
		return -EINVAL;
	}

	snd_soc_component_update_bits(component, AK4458_00_CONTROL1,
			    AK4458_DIF_MASK, format);

	ak4458_rstn_control(component, 0);
	ak4458_rstn_control(component, 1);

	return 0;
}