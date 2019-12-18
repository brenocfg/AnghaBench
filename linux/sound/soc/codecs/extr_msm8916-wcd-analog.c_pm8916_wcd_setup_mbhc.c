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
typedef  int u32 ;
struct snd_soc_component {int dummy; } ;
struct pm8916_wcd_analog_priv {int mbhc_btn0_released; int detect_accessory_type; scalar_t__ mbhc_btn_enabled; scalar_t__ gnd_jack_type_normally_open; scalar_t__ hphl_jack_type_normally_open; struct snd_soc_component* component; } ;

/* Variables and functions */
 int CDC_A_GND_PLUG_TYPE_NO ; 
 int CDC_A_HPHL_PLUG_TYPE_NO ; 
 int /*<<< orphan*/  CDC_A_MBHC_DBNC_TIMER ; 
 int CDC_A_MBHC_DBNC_TIMER_BTN_DBNC_T_16MS ; 
 int CDC_A_MBHC_DBNC_TIMER_INSREM_DBNC_T_256_MS ; 
 int /*<<< orphan*/  CDC_A_MBHC_DET_CTL_1 ; 
 int /*<<< orphan*/  CDC_A_MBHC_DET_CTL_2 ; 
 int CDC_A_MBHC_DET_CTL_HPHL_100K_TO_GND_EN ; 
 int CDC_A_MBHC_DET_CTL_HS_L_DET_COMPA_CTRL_V0P9_VDD ; 
 int CDC_A_MBHC_DET_CTL_HS_L_DET_PULL_UP_CTRL_I_3P0 ; 
 int CDC_A_MBHC_DET_CTL_L_DET_EN ; 
 int CDC_A_MBHC_DET_CTL_MBHC_BIAS_EN ; 
 int CDC_A_MBHC_DET_CTL_MECH_DET_TYPE_INSERTION ; 
 int CDC_A_MBHC_DET_CTL_MIC_CLAMP_CTL_AUTO ; 
 int /*<<< orphan*/  CDC_A_MICB_2_EN ; 
 int CDC_A_MICB_2_EN_ENABLE ; 
 int /*<<< orphan*/  CDC_D_CDC_DIG_CLK_CTL ; 
 int /*<<< orphan*/  CDC_D_INT_EN_CLR ; 
 int /*<<< orphan*/  CDC_D_INT_EN_SET ; 
 int DIG_CLK_CTL_D_MBHC_CLK_EN ; 
 int DIG_CLK_CTL_D_MBHC_CLK_EN_MASK ; 
 int MBHC_BUTTON_PRESS_DET ; 
 int MBHC_BUTTON_RELEASE_DET ; 
 int MBHC_SWITCH_INT ; 
 int /*<<< orphan*/  pm8916_mbhc_configure_bias (struct pm8916_wcd_analog_priv*,int) ; 
 int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void pm8916_wcd_setup_mbhc(struct pm8916_wcd_analog_priv *wcd)
{
	struct snd_soc_component *component = wcd->component;
	bool micbias_enabled = false;
	u32 plug_type = 0;
	u32 int_en_mask;

	snd_soc_component_write(component, CDC_A_MBHC_DET_CTL_1,
		      CDC_A_MBHC_DET_CTL_L_DET_EN |
		      CDC_A_MBHC_DET_CTL_MECH_DET_TYPE_INSERTION |
		      CDC_A_MBHC_DET_CTL_MIC_CLAMP_CTL_AUTO |
		      CDC_A_MBHC_DET_CTL_MBHC_BIAS_EN);

	if (wcd->hphl_jack_type_normally_open)
		plug_type |= CDC_A_HPHL_PLUG_TYPE_NO;

	if (wcd->gnd_jack_type_normally_open)
		plug_type |= CDC_A_GND_PLUG_TYPE_NO;

	snd_soc_component_write(component, CDC_A_MBHC_DET_CTL_2,
		      CDC_A_MBHC_DET_CTL_HS_L_DET_PULL_UP_CTRL_I_3P0 |
		      CDC_A_MBHC_DET_CTL_HS_L_DET_COMPA_CTRL_V0P9_VDD |
		      plug_type |
		      CDC_A_MBHC_DET_CTL_HPHL_100K_TO_GND_EN);


	snd_soc_component_write(component, CDC_A_MBHC_DBNC_TIMER,
		      CDC_A_MBHC_DBNC_TIMER_INSREM_DBNC_T_256_MS |
		      CDC_A_MBHC_DBNC_TIMER_BTN_DBNC_T_16MS);

	/* enable MBHC clock */
	snd_soc_component_update_bits(component, CDC_D_CDC_DIG_CLK_CTL,
			    DIG_CLK_CTL_D_MBHC_CLK_EN_MASK,
			    DIG_CLK_CTL_D_MBHC_CLK_EN);

	if (snd_soc_component_read32(component, CDC_A_MICB_2_EN) & CDC_A_MICB_2_EN_ENABLE)
		micbias_enabled = true;

	pm8916_mbhc_configure_bias(wcd, micbias_enabled);

	int_en_mask = MBHC_SWITCH_INT;
	if (wcd->mbhc_btn_enabled)
		int_en_mask |= MBHC_BUTTON_PRESS_DET | MBHC_BUTTON_RELEASE_DET;

	snd_soc_component_update_bits(component, CDC_D_INT_EN_CLR, int_en_mask, 0);
	snd_soc_component_update_bits(component, CDC_D_INT_EN_SET, int_en_mask, int_en_mask);
	wcd->mbhc_btn0_released = false;
	wcd->detect_accessory_type = true;
}