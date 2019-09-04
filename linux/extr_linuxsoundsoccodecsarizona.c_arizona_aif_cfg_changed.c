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
 int ARIZONA_AIF1TX_BCPF_MASK ; 
 int ARIZONA_AIF1TX_SLOT_LEN_MASK ; 
 int ARIZONA_AIF1TX_WL_MASK ; 
 int ARIZONA_AIF1_BCLK_FREQ_MASK ; 
 scalar_t__ ARIZONA_AIF_BCLK_CTRL ; 
 scalar_t__ ARIZONA_AIF_FRAME_CTRL_1 ; 
 scalar_t__ ARIZONA_AIF_TX_BCLK_RATE ; 
 int snd_soc_component_read32 (struct snd_soc_component*,scalar_t__) ; 

__attribute__((used)) static bool arizona_aif_cfg_changed(struct snd_soc_component *component,
				    int base, int bclk, int lrclk, int frame)
{
	int val;

	val = snd_soc_component_read32(component, base + ARIZONA_AIF_BCLK_CTRL);
	if (bclk != (val & ARIZONA_AIF1_BCLK_FREQ_MASK))
		return true;

	val = snd_soc_component_read32(component, base + ARIZONA_AIF_TX_BCLK_RATE);
	if (lrclk != (val & ARIZONA_AIF1TX_BCPF_MASK))
		return true;

	val = snd_soc_component_read32(component, base + ARIZONA_AIF_FRAME_CTRL_1);
	if (frame != (val & (ARIZONA_AIF1TX_WL_MASK |
			     ARIZONA_AIF1TX_SLOT_LEN_MASK)))
		return true;

	return false;
}