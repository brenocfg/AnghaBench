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
struct snd_soc_component {int dummy; } ;
struct da7219_priv {struct da7219_pdata* pdata; struct da7219_aad_priv* aad; } ;
struct da7219_pdata {struct da7219_aad_pdata* aad_pdata; } ;
struct da7219_aad_priv {int micbias_pulse_lvl; int btn_cfg; int /*<<< orphan*/  micbias_pulse_time; int /*<<< orphan*/  irq; } ;
struct da7219_aad_pdata {int micbias_pulse_lvl; int btn_cfg; int mic_det_thr; int jack_ins_deb; int jack_det_rate; int jack_rem_deb; int btn_avg; int adc_1bit_rpt; int /*<<< orphan*/  c_mic_btn_thr; int /*<<< orphan*/  b_c_btn_thr; int /*<<< orphan*/  d_b_btn_thr; int /*<<< orphan*/  a_d_btn_thr; int /*<<< orphan*/  micbias_pulse_time; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
#define  DA7219_AAD_ADC_1BIT_RPT_1 164 
#define  DA7219_AAD_ADC_1BIT_RPT_2 163 
#define  DA7219_AAD_ADC_1BIT_RPT_4 162 
#define  DA7219_AAD_ADC_1BIT_RPT_8 161 
#define  DA7219_AAD_BTN_AVG_1 160 
#define  DA7219_AAD_BTN_AVG_2 159 
#define  DA7219_AAD_BTN_AVG_4 158 
#define  DA7219_AAD_BTN_AVG_8 157 
#define  DA7219_AAD_BTN_CFG_100MS 156 
#define  DA7219_AAD_BTN_CFG_10MS 155 
#define  DA7219_AAD_BTN_CFG_200MS 154 
#define  DA7219_AAD_BTN_CFG_2MS 153 
#define  DA7219_AAD_BTN_CFG_500MS 152 
#define  DA7219_AAD_BTN_CFG_50MS 151 
#define  DA7219_AAD_BTN_CFG_5MS 150 
#define  DA7219_AAD_JACK_DET_RATE_128_256MS 149 
#define  DA7219_AAD_JACK_DET_RATE_256_512MS 148 
#define  DA7219_AAD_JACK_DET_RATE_32_64MS 147 
#define  DA7219_AAD_JACK_DET_RATE_64_128MS 146 
#define  DA7219_AAD_JACK_INS_DEB_100MS 145 
#define  DA7219_AAD_JACK_INS_DEB_10MS 144 
#define  DA7219_AAD_JACK_INS_DEB_1S 143 
#define  DA7219_AAD_JACK_INS_DEB_200MS 142 
#define  DA7219_AAD_JACK_INS_DEB_20MS 141 
#define  DA7219_AAD_JACK_INS_DEB_500MS 140 
#define  DA7219_AAD_JACK_INS_DEB_50MS 139 
#define  DA7219_AAD_JACK_INS_DEB_5MS 138 
#define  DA7219_AAD_JACK_REM_DEB_10MS 137 
#define  DA7219_AAD_JACK_REM_DEB_1MS 136 
#define  DA7219_AAD_JACK_REM_DEB_20MS 135 
#define  DA7219_AAD_JACK_REM_DEB_5MS 134 
#define  DA7219_AAD_MICBIAS_PULSE_LVL_2_8V 133 
#define  DA7219_AAD_MICBIAS_PULSE_LVL_2_9V 132 
#define  DA7219_AAD_MIC_DET_THR_1000_OHMS 131 
#define  DA7219_AAD_MIC_DET_THR_200_OHMS 130 
#define  DA7219_AAD_MIC_DET_THR_500_OHMS 129 
#define  DA7219_AAD_MIC_DET_THR_750_OHMS 128 
 int /*<<< orphan*/  DA7219_ACCDET_CONFIG_1 ; 
 int /*<<< orphan*/  DA7219_ACCDET_CONFIG_2 ; 
 int /*<<< orphan*/  DA7219_ACCDET_CONFIG_3 ; 
 int /*<<< orphan*/  DA7219_ACCDET_CONFIG_4 ; 
 int /*<<< orphan*/  DA7219_ACCDET_CONFIG_5 ; 
 int /*<<< orphan*/  DA7219_ACCDET_CONFIG_6 ; 
 int /*<<< orphan*/  DA7219_ACCDET_CONFIG_7 ; 
 int DA7219_ADC_1_BIT_REPEAT_MASK ; 
 int DA7219_ADC_1_BIT_REPEAT_SHIFT ; 
 int DA7219_BUTTON_AVERAGE_MASK ; 
 int DA7219_BUTTON_AVERAGE_SHIFT ; 
 int DA7219_BUTTON_CONFIG_SHIFT ; 
 int DA7219_JACKDET_DEBOUNCE_MASK ; 
 int DA7219_JACKDET_DEBOUNCE_SHIFT ; 
 int DA7219_JACKDET_REM_DEB_MASK ; 
 int DA7219_JACKDET_REM_DEB_SHIFT ; 
 int DA7219_JACK_DETECT_RATE_MASK ; 
 int DA7219_JACK_DETECT_RATE_SHIFT ; 
 int DA7219_MICBIAS1_LEVEL_SHIFT ; 
 int DA7219_MIC_DET_THRESH_MASK ; 
 int DA7219_MIC_DET_THRESH_SHIFT ; 
 struct da7219_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void da7219_aad_handle_pdata(struct snd_soc_component *component)
{
	struct da7219_priv *da7219 = snd_soc_component_get_drvdata(component);
	struct da7219_aad_priv *da7219_aad = da7219->aad;
	struct da7219_pdata *pdata = da7219->pdata;

	if ((pdata) && (pdata->aad_pdata)) {
		struct da7219_aad_pdata *aad_pdata = pdata->aad_pdata;
		u8 cfg, mask;

		da7219_aad->irq = aad_pdata->irq;

		switch (aad_pdata->micbias_pulse_lvl) {
		case DA7219_AAD_MICBIAS_PULSE_LVL_2_8V:
		case DA7219_AAD_MICBIAS_PULSE_LVL_2_9V:
			da7219_aad->micbias_pulse_lvl =
				(aad_pdata->micbias_pulse_lvl <<
				 DA7219_MICBIAS1_LEVEL_SHIFT);
			break;
		default:
			break;
		}

		da7219_aad->micbias_pulse_time = aad_pdata->micbias_pulse_time;

		switch (aad_pdata->btn_cfg) {
		case DA7219_AAD_BTN_CFG_2MS:
		case DA7219_AAD_BTN_CFG_5MS:
		case DA7219_AAD_BTN_CFG_10MS:
		case DA7219_AAD_BTN_CFG_50MS:
		case DA7219_AAD_BTN_CFG_100MS:
		case DA7219_AAD_BTN_CFG_200MS:
		case DA7219_AAD_BTN_CFG_500MS:
			da7219_aad->btn_cfg  = (aad_pdata->btn_cfg <<
						DA7219_BUTTON_CONFIG_SHIFT);
		}

		cfg = 0;
		mask = 0;
		switch (aad_pdata->mic_det_thr) {
		case DA7219_AAD_MIC_DET_THR_200_OHMS:
		case DA7219_AAD_MIC_DET_THR_500_OHMS:
		case DA7219_AAD_MIC_DET_THR_750_OHMS:
		case DA7219_AAD_MIC_DET_THR_1000_OHMS:
			cfg |= (aad_pdata->mic_det_thr <<
				DA7219_MIC_DET_THRESH_SHIFT);
			mask |= DA7219_MIC_DET_THRESH_MASK;
		}
		snd_soc_component_update_bits(component, DA7219_ACCDET_CONFIG_1, mask, cfg);

		cfg = 0;
		mask = 0;
		switch (aad_pdata->jack_ins_deb) {
		case DA7219_AAD_JACK_INS_DEB_5MS:
		case DA7219_AAD_JACK_INS_DEB_10MS:
		case DA7219_AAD_JACK_INS_DEB_20MS:
		case DA7219_AAD_JACK_INS_DEB_50MS:
		case DA7219_AAD_JACK_INS_DEB_100MS:
		case DA7219_AAD_JACK_INS_DEB_200MS:
		case DA7219_AAD_JACK_INS_DEB_500MS:
		case DA7219_AAD_JACK_INS_DEB_1S:
			cfg |= (aad_pdata->jack_ins_deb <<
				DA7219_JACKDET_DEBOUNCE_SHIFT);
			mask |= DA7219_JACKDET_DEBOUNCE_MASK;
		}
		switch (aad_pdata->jack_det_rate) {
		case DA7219_AAD_JACK_DET_RATE_32_64MS:
		case DA7219_AAD_JACK_DET_RATE_64_128MS:
		case DA7219_AAD_JACK_DET_RATE_128_256MS:
		case DA7219_AAD_JACK_DET_RATE_256_512MS:
			cfg |= (aad_pdata->jack_det_rate <<
				DA7219_JACK_DETECT_RATE_SHIFT);
			mask |= DA7219_JACK_DETECT_RATE_MASK;
		}
		switch (aad_pdata->jack_rem_deb) {
		case DA7219_AAD_JACK_REM_DEB_1MS:
		case DA7219_AAD_JACK_REM_DEB_5MS:
		case DA7219_AAD_JACK_REM_DEB_10MS:
		case DA7219_AAD_JACK_REM_DEB_20MS:
			cfg |= (aad_pdata->jack_rem_deb <<
				DA7219_JACKDET_REM_DEB_SHIFT);
			mask |= DA7219_JACKDET_REM_DEB_MASK;
		}
		snd_soc_component_update_bits(component, DA7219_ACCDET_CONFIG_2, mask, cfg);

		snd_soc_component_write(component, DA7219_ACCDET_CONFIG_3,
			      aad_pdata->a_d_btn_thr);
		snd_soc_component_write(component, DA7219_ACCDET_CONFIG_4,
			      aad_pdata->d_b_btn_thr);
		snd_soc_component_write(component, DA7219_ACCDET_CONFIG_5,
			      aad_pdata->b_c_btn_thr);
		snd_soc_component_write(component, DA7219_ACCDET_CONFIG_6,
			      aad_pdata->c_mic_btn_thr);

		cfg = 0;
		mask = 0;
		switch (aad_pdata->btn_avg) {
		case DA7219_AAD_BTN_AVG_1:
		case DA7219_AAD_BTN_AVG_2:
		case DA7219_AAD_BTN_AVG_4:
		case DA7219_AAD_BTN_AVG_8:
			cfg |= (aad_pdata->btn_avg <<
				DA7219_BUTTON_AVERAGE_SHIFT);
			mask |= DA7219_BUTTON_AVERAGE_MASK;
		}
		switch (aad_pdata->adc_1bit_rpt) {
		case DA7219_AAD_ADC_1BIT_RPT_1:
		case DA7219_AAD_ADC_1BIT_RPT_2:
		case DA7219_AAD_ADC_1BIT_RPT_4:
		case DA7219_AAD_ADC_1BIT_RPT_8:
			cfg |= (aad_pdata->adc_1bit_rpt <<
			       DA7219_ADC_1_BIT_REPEAT_SHIFT);
			mask |= DA7219_ADC_1_BIT_REPEAT_MASK;
		}
		snd_soc_component_update_bits(component, DA7219_ACCDET_CONFIG_7, mask, cfg);
	}
}