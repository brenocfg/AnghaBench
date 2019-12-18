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
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 unsigned int MADERA_AIF1RX_BCPF_MASK ; 
 unsigned int MADERA_AIF1TX_SLOT_LEN_MASK ; 
 unsigned int MADERA_AIF1TX_WL_MASK ; 
 unsigned int MADERA_AIF1_BCLK_FREQ_MASK ; 
 scalar_t__ MADERA_AIF_BCLK_CTRL ; 
 scalar_t__ MADERA_AIF_FRAME_CTRL_1 ; 
 scalar_t__ MADERA_AIF_RX_BCLK_RATE ; 
 int snd_soc_component_read (struct snd_soc_component*,scalar_t__,unsigned int*) ; 

__attribute__((used)) static int madera_aif_cfg_changed(struct snd_soc_component *component,
				  int base, int bclk, int lrclk, int frame)
{
	unsigned int val;
	int ret;

	ret = snd_soc_component_read(component, base + MADERA_AIF_BCLK_CTRL,
				     &val);
	if (ret)
		return ret;
	if (bclk != (val & MADERA_AIF1_BCLK_FREQ_MASK))
		return 1;

	ret = snd_soc_component_read(component, base + MADERA_AIF_RX_BCLK_RATE,
				     &val);
	if (ret)
		return ret;
	if (lrclk != (val & MADERA_AIF1RX_BCPF_MASK))
		return 1;

	ret = snd_soc_component_read(component, base + MADERA_AIF_FRAME_CTRL_1,
				     &val);
	if (ret)
		return ret;
	if (frame != (val & (MADERA_AIF1TX_WL_MASK |
			     MADERA_AIF1TX_SLOT_LEN_MASK)))
		return 1;

	return 0;
}