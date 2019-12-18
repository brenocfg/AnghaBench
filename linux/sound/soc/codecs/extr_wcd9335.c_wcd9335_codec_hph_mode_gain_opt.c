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
struct wcd9335_codec {int hph_l_gain; int hph_r_gain; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  WCD9335_ANA_HPH ; 
 int /*<<< orphan*/  WCD9335_HPH_L_EN ; 
 int /*<<< orphan*/  WCD9335_HPH_R_EN ; 
 struct wcd9335_codec* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void wcd9335_codec_hph_mode_gain_opt(struct snd_soc_component *component,
					    u8 gain)
{
	struct wcd9335_codec *wcd = dev_get_drvdata(component->dev);
	u8 hph_l_en, hph_r_en;
	u8 l_val, r_val;
	u8 hph_pa_status;
	bool is_hphl_pa, is_hphr_pa;

	hph_pa_status = snd_soc_component_read32(component, WCD9335_ANA_HPH);
	is_hphl_pa = hph_pa_status >> 7;
	is_hphr_pa = (hph_pa_status & 0x40) >> 6;

	hph_l_en = snd_soc_component_read32(component, WCD9335_HPH_L_EN);
	hph_r_en = snd_soc_component_read32(component, WCD9335_HPH_R_EN);

	l_val = (hph_l_en & 0xC0) | 0x20 | gain;
	r_val = (hph_r_en & 0xC0) | 0x20 | gain;

	/*
	 * Set HPH_L & HPH_R gain source selection to REGISTER
	 * for better click and pop only if corresponding PAs are
	 * not enabled. Also cache the values of the HPHL/R
	 * PA gains to be applied after PAs are enabled
	 */
	if ((l_val != hph_l_en) && !is_hphl_pa) {
		snd_soc_component_write(component, WCD9335_HPH_L_EN, l_val);
		wcd->hph_l_gain = hph_l_en & 0x1F;
	}

	if ((r_val != hph_r_en) && !is_hphr_pa) {
		snd_soc_component_write(component, WCD9335_HPH_R_EN, r_val);
		wcd->hph_r_gain = hph_r_en & 0x1F;
	}
}