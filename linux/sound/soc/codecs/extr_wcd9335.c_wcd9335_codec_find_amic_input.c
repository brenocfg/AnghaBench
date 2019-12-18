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
 int WCD9335_CDC_TX_INP_MUX_ADC_MUX0_CFG0 ; 
 int WCD9335_CDC_TX_INP_MUX_ADC_MUX0_CFG1 ; 
 int WCD9335_CDC_TX_INP_MUX_ADC_MUX4_CFG0 ; 
 int WCD9335_CDC_TX_INP_MUX_SEL_AMIC ; 
 int WCD9335_INVALID_ADC_MUX ; 
 int WCD9335_MAX_VALID_ADC_MUX ; 
 int snd_soc_component_read32 (struct snd_soc_component*,int) ; 

__attribute__((used)) static int wcd9335_codec_find_amic_input(struct snd_soc_component *comp,
					 int adc_mux_n)
{
	int mux_sel, reg, mreg;

	if (adc_mux_n < 0 || adc_mux_n > WCD9335_MAX_VALID_ADC_MUX ||
	    adc_mux_n == WCD9335_INVALID_ADC_MUX)
		return 0;

	/* Check whether adc mux input is AMIC or DMIC */
	if (adc_mux_n < 4) {
		reg = WCD9335_CDC_TX_INP_MUX_ADC_MUX0_CFG1 + 2 * adc_mux_n;
		mreg = WCD9335_CDC_TX_INP_MUX_ADC_MUX0_CFG0 + 2 * adc_mux_n;
		mux_sel = snd_soc_component_read32(comp, reg) & 0x3;
	} else {
		reg = WCD9335_CDC_TX_INP_MUX_ADC_MUX4_CFG0 + adc_mux_n - 4;
		mreg = reg;
		mux_sel = snd_soc_component_read32(comp, reg) >> 6;
	}

	if (mux_sel != WCD9335_CDC_TX_INP_MUX_SEL_AMIC)
		return 0;

	return snd_soc_component_read32(comp, mreg) & 0x07;
}