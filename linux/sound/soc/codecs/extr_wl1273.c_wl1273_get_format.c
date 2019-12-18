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
struct wl1273_priv {int mode; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int SND_SOC_DAIFMT_CBM_CFM ; 
 unsigned int SND_SOC_DAIFMT_DSP_A ; 
 unsigned int SND_SOC_DAIFMT_I2S ; 
 unsigned int SND_SOC_DAIFMT_IB_NF ; 
 unsigned int SND_SOC_DAIFMT_NB_NF ; 
#define  WL1273_MODE_BT 130 
#define  WL1273_MODE_FM_RX 129 
#define  WL1273_MODE_FM_TX 128 
 struct wl1273_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

int wl1273_get_format(struct snd_soc_component *component, unsigned int *fmt)
{
	struct wl1273_priv *wl1273;

	if (component == NULL || fmt == NULL)
		return -EINVAL;

	wl1273 = snd_soc_component_get_drvdata(component);

	switch (wl1273->mode) {
	case WL1273_MODE_FM_RX:
	case WL1273_MODE_FM_TX:
		*fmt =	SND_SOC_DAIFMT_I2S |
			SND_SOC_DAIFMT_NB_NF |
			SND_SOC_DAIFMT_CBM_CFM;

		break;
	case WL1273_MODE_BT:
		*fmt =	SND_SOC_DAIFMT_DSP_A |
			SND_SOC_DAIFMT_IB_NF |
			SND_SOC_DAIFMT_CBM_CFM;

		break;
	default:
		return -EINVAL;
	}

	return 0;
}