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
struct wm_hubs_data {int lineout1_se; int lineout2_se; int micb1_delay; int micb2_delay; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WM8993_ADDITIONAL_CONTROL ; 
 int /*<<< orphan*/  WM8993_ANTIPOP1 ; 
 int WM8993_JD_SCTHR_MASK ; 
 int WM8993_JD_SCTHR_SHIFT ; 
 int WM8993_JD_THR_MASK ; 
 int WM8993_JD_THR_SHIFT ; 
 int WM8993_LINEOUT1_FB ; 
 int WM8993_LINEOUT1_MODE ; 
 int WM8993_LINEOUT2_FB ; 
 int WM8993_LINEOUT2_MODE ; 
 int WM8993_LINEOUT_VMID_BUF_ENA ; 
 int /*<<< orphan*/  WM8993_LINE_MIXER1 ; 
 int /*<<< orphan*/  WM8993_LINE_MIXER2 ; 
 int WM8993_MICB1_LVL ; 
 int WM8993_MICB2_LVL ; 
 int WM8993_MICB2_LVL_SHIFT ; 
 int /*<<< orphan*/  WM8993_MICBIAS ; 
 struct wm_hubs_data* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 

int wm_hubs_handle_analogue_pdata(struct snd_soc_component *component,
				  int lineout1_diff, int lineout2_diff,
				  int lineout1fb, int lineout2fb,
				  int jd_scthr, int jd_thr,
				  int micbias1_delay, int micbias2_delay,
				  int micbias1_lvl, int micbias2_lvl)
{
	struct wm_hubs_data *hubs = snd_soc_component_get_drvdata(component);

	hubs->lineout1_se = !lineout1_diff;
	hubs->lineout2_se = !lineout2_diff;
	hubs->micb1_delay = micbias1_delay;
	hubs->micb2_delay = micbias2_delay;

	if (!lineout1_diff)
		snd_soc_component_update_bits(component, WM8993_LINE_MIXER1,
				    WM8993_LINEOUT1_MODE,
				    WM8993_LINEOUT1_MODE);
	if (!lineout2_diff)
		snd_soc_component_update_bits(component, WM8993_LINE_MIXER2,
				    WM8993_LINEOUT2_MODE,
				    WM8993_LINEOUT2_MODE);

	if (!lineout1_diff && !lineout2_diff)
		snd_soc_component_update_bits(component, WM8993_ANTIPOP1,
				    WM8993_LINEOUT_VMID_BUF_ENA,
				    WM8993_LINEOUT_VMID_BUF_ENA);

	if (lineout1fb)
		snd_soc_component_update_bits(component, WM8993_ADDITIONAL_CONTROL,
				    WM8993_LINEOUT1_FB, WM8993_LINEOUT1_FB);

	if (lineout2fb)
		snd_soc_component_update_bits(component, WM8993_ADDITIONAL_CONTROL,
				    WM8993_LINEOUT2_FB, WM8993_LINEOUT2_FB);

	snd_soc_component_update_bits(component, WM8993_MICBIAS,
			    WM8993_JD_SCTHR_MASK | WM8993_JD_THR_MASK |
			    WM8993_MICB1_LVL | WM8993_MICB2_LVL,
			    jd_scthr << WM8993_JD_SCTHR_SHIFT |
			    jd_thr << WM8993_JD_THR_SHIFT |
			    micbias1_lvl |
			    micbias2_lvl << WM8993_MICB2_LVL_SHIFT);

	return 0;
}