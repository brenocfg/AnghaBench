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
typedef  scalar_t__ u16 ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 scalar_t__ SND_SOC_DAPM_EVENT_OFF (int) ; 
 scalar_t__ SND_SOC_DAPM_EVENT_ON (int) ; 
 scalar_t__ WCD9335_CDC_RX1_RX_PATH_CFG0 ; 
 scalar_t__ WCD9335_CDC_RX1_RX_PATH_CTL ; 
 scalar_t__ WCD9335_CDC_RX1_RX_PATH_SEC3 ; 
 scalar_t__ WCD9335_CDC_RX2_RX_PATH_CFG0 ; 
 scalar_t__ WCD9335_CDC_RX2_RX_PATH_CTL ; 
 scalar_t__ WCD9335_CDC_RX2_RX_PATH_SEC3 ; 
 int /*<<< orphan*/  WCD9335_CDC_RX_PATH_CFG_HD2_DISABLE ; 
 int /*<<< orphan*/  WCD9335_CDC_RX_PATH_CFG_HD2_ENABLE ; 
 int /*<<< orphan*/  WCD9335_CDC_RX_PATH_CFG_HD2_EN_MASK ; 
 int /*<<< orphan*/  WCD9335_CDC_RX_PATH_SEC_HD2_ALPHA_0P0000 ; 
 int /*<<< orphan*/  WCD9335_CDC_RX_PATH_SEC_HD2_ALPHA_0P2500 ; 
 int /*<<< orphan*/  WCD9335_CDC_RX_PATH_SEC_HD2_ALPHA_MASK ; 
 int /*<<< orphan*/  WCD9335_CDC_RX_PATH_SEC_HD2_SCALE_1 ; 
 int /*<<< orphan*/  WCD9335_CDC_RX_PATH_SEC_HD2_SCALE_2 ; 
 int /*<<< orphan*/  WCD9335_CDC_RX_PATH_SEC_HD2_SCALE_MASK ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wcd9335_codec_hd2_control(struct snd_soc_component *component,
				    u16 prim_int_reg, int event)
{
	u16 hd2_scale_reg;
	u16 hd2_enable_reg = 0;

	if (prim_int_reg == WCD9335_CDC_RX1_RX_PATH_CTL) {
		hd2_scale_reg = WCD9335_CDC_RX1_RX_PATH_SEC3;
		hd2_enable_reg = WCD9335_CDC_RX1_RX_PATH_CFG0;
	}
	if (prim_int_reg == WCD9335_CDC_RX2_RX_PATH_CTL) {
		hd2_scale_reg = WCD9335_CDC_RX2_RX_PATH_SEC3;
		hd2_enable_reg = WCD9335_CDC_RX2_RX_PATH_CFG0;
	}

	if (hd2_enable_reg && SND_SOC_DAPM_EVENT_ON(event)) {
		snd_soc_component_update_bits(component, hd2_scale_reg,
				WCD9335_CDC_RX_PATH_SEC_HD2_ALPHA_MASK,
				WCD9335_CDC_RX_PATH_SEC_HD2_ALPHA_0P2500);
		snd_soc_component_update_bits(component, hd2_scale_reg,
				WCD9335_CDC_RX_PATH_SEC_HD2_SCALE_MASK,
				WCD9335_CDC_RX_PATH_SEC_HD2_SCALE_2);
		snd_soc_component_update_bits(component, hd2_enable_reg,
				WCD9335_CDC_RX_PATH_CFG_HD2_EN_MASK,
				WCD9335_CDC_RX_PATH_CFG_HD2_ENABLE);
	}

	if (hd2_enable_reg && SND_SOC_DAPM_EVENT_OFF(event)) {
		snd_soc_component_update_bits(component, hd2_enable_reg,
					WCD9335_CDC_RX_PATH_CFG_HD2_EN_MASK,
					WCD9335_CDC_RX_PATH_CFG_HD2_DISABLE);
		snd_soc_component_update_bits(component, hd2_scale_reg,
					WCD9335_CDC_RX_PATH_SEC_HD2_SCALE_MASK,
					WCD9335_CDC_RX_PATH_SEC_HD2_SCALE_1);
		snd_soc_component_update_bits(component, hd2_scale_reg,
				WCD9335_CDC_RX_PATH_SEC_HD2_ALPHA_MASK,
				WCD9335_CDC_RX_PATH_SEC_HD2_ALPHA_0P0000);
	}
}