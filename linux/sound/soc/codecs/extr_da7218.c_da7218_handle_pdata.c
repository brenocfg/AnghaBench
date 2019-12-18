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
struct da7218_priv {scalar_t__ dev_id; scalar_t__ hp_single_supply; struct da7218_pdata* pdata; } ;
struct da7218_pdata {int micbias1_lvl; int micbias2_lvl; int mic1_amp_in_sel; int mic2_amp_in_sel; int dmic1_data_sel; int dmic1_samplephase; int dmic1_clk_rate; int dmic2_data_sel; int dmic2_samplephase; int dmic2_clk_rate; struct da7218_hpldet_pdata* hpldet_pdata; scalar_t__ hp_diff_single_supply; } ;
struct da7218_hpldet_pdata {int jack_rate; int jack_debounce; int jack_thr; scalar_t__ discharge; scalar_t__ hyst; scalar_t__ comp_inv; } ;

/* Variables and functions */
 scalar_t__ DA7217_DEV_ID ; 
 scalar_t__ DA7218_DEV_ID ; 
 int DA7218_DMIC_1_CLK_RATE_MASK ; 
 int DA7218_DMIC_1_CLK_RATE_SHIFT ; 
 int /*<<< orphan*/  DA7218_DMIC_1_CTRL ; 
 int DA7218_DMIC_1_DATA_SEL_MASK ; 
 int DA7218_DMIC_1_DATA_SEL_SHIFT ; 
 int DA7218_DMIC_1_SAMPLEPHASE_MASK ; 
 int DA7218_DMIC_1_SAMPLEPHASE_SHIFT ; 
 int DA7218_DMIC_2_CLK_RATE_MASK ; 
 int DA7218_DMIC_2_CLK_RATE_SHIFT ; 
 int /*<<< orphan*/  DA7218_DMIC_2_CTRL ; 
 int DA7218_DMIC_2_DATA_SEL_MASK ; 
 int DA7218_DMIC_2_DATA_SEL_SHIFT ; 
 int DA7218_DMIC_2_SAMPLEPHASE_MASK ; 
 int DA7218_DMIC_2_SAMPLEPHASE_SHIFT ; 
#define  DA7218_DMIC_CLK_1_5MHZ 161 
#define  DA7218_DMIC_CLK_3_0MHZ 160 
#define  DA7218_DMIC_DATA_LFALL_RRISE 159 
#define  DA7218_DMIC_DATA_LRISE_RFALL 158 
#define  DA7218_DMIC_SAMPLE_BETWEEN_CLKEDGE 157 
#define  DA7218_DMIC_SAMPLE_ON_CLKEDGE 156 
 int DA7218_HPLDET_COMP_INV_MASK ; 
 int /*<<< orphan*/  DA7218_HPLDET_CTRL ; 
 int DA7218_HPLDET_DISCHARGE_EN_MASK ; 
 int DA7218_HPLDET_HYST_EN_MASK ; 
 int /*<<< orphan*/  DA7218_HPLDET_JACK ; 
#define  DA7218_HPLDET_JACK_DEBOUNCE_2 155 
#define  DA7218_HPLDET_JACK_DEBOUNCE_3 154 
#define  DA7218_HPLDET_JACK_DEBOUNCE_4 153 
 int DA7218_HPLDET_JACK_DEBOUNCE_MASK ; 
#define  DA7218_HPLDET_JACK_DEBOUNCE_OFF 152 
 int DA7218_HPLDET_JACK_DEBOUNCE_SHIFT ; 
#define  DA7218_HPLDET_JACK_RATE_10US 151 
#define  DA7218_HPLDET_JACK_RATE_160US 150 
#define  DA7218_HPLDET_JACK_RATE_20US 149 
#define  DA7218_HPLDET_JACK_RATE_320US 148 
#define  DA7218_HPLDET_JACK_RATE_40US 147 
#define  DA7218_HPLDET_JACK_RATE_5US 146 
#define  DA7218_HPLDET_JACK_RATE_640US 145 
#define  DA7218_HPLDET_JACK_RATE_80US 144 
 int DA7218_HPLDET_JACK_RATE_MASK ; 
 int DA7218_HPLDET_JACK_RATE_SHIFT ; 
#define  DA7218_HPLDET_JACK_THR_84PCT 143 
#define  DA7218_HPLDET_JACK_THR_88PCT 142 
#define  DA7218_HPLDET_JACK_THR_92PCT 141 
#define  DA7218_HPLDET_JACK_THR_96PCT 140 
 int DA7218_HPLDET_JACK_THR_MASK ; 
 int DA7218_HPLDET_JACK_THR_SHIFT ; 
 int DA7218_HP_AMP_SINGLE_SUPPLY_EN_MASK ; 
 int /*<<< orphan*/  DA7218_HP_DIFF_CTRL ; 
 int /*<<< orphan*/  DA7218_HP_DIFF_UNLOCK ; 
 int DA7218_HP_DIFF_UNLOCK_VAL ; 
#define  DA7218_MICBIAS_1_2V 139 
#define  DA7218_MICBIAS_1_6V 138 
#define  DA7218_MICBIAS_1_8V 137 
 int DA7218_MICBIAS_1_LEVEL_SHIFT ; 
 int DA7218_MICBIAS_1_LP_MODE_MASK ; 
#define  DA7218_MICBIAS_2_0V 136 
#define  DA7218_MICBIAS_2_2V 135 
#define  DA7218_MICBIAS_2_4V 134 
#define  DA7218_MICBIAS_2_6V 133 
#define  DA7218_MICBIAS_2_8V 132 
 int DA7218_MICBIAS_2_LEVEL_SHIFT ; 
 int DA7218_MICBIAS_2_LP_MODE_MASK ; 
#define  DA7218_MICBIAS_3_0V 131 
 int /*<<< orphan*/  DA7218_MICBIAS_CTRL ; 
 int /*<<< orphan*/  DA7218_MIC_1_SELECT ; 
 int /*<<< orphan*/  DA7218_MIC_2_SELECT ; 
#define  DA7218_MIC_AMP_IN_SEL_DIFF 130 
#define  DA7218_MIC_AMP_IN_SEL_SE_N 129 
#define  DA7218_MIC_AMP_IN_SEL_SE_P 128 
 struct da7218_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void da7218_handle_pdata(struct snd_soc_component *component)
{
	struct da7218_priv *da7218 = snd_soc_component_get_drvdata(component);
	struct da7218_pdata *pdata = da7218->pdata;

	if (pdata) {
		u8 micbias_lvl = 0, dmic_cfg = 0;

		/* Mic Bias voltages */
		switch (pdata->micbias1_lvl) {
		case DA7218_MICBIAS_1_2V:
			micbias_lvl |= DA7218_MICBIAS_1_LP_MODE_MASK;
			break;
		case DA7218_MICBIAS_1_6V:
		case DA7218_MICBIAS_1_8V:
		case DA7218_MICBIAS_2_0V:
		case DA7218_MICBIAS_2_2V:
		case DA7218_MICBIAS_2_4V:
		case DA7218_MICBIAS_2_6V:
		case DA7218_MICBIAS_2_8V:
		case DA7218_MICBIAS_3_0V:
			micbias_lvl |= (pdata->micbias1_lvl <<
					DA7218_MICBIAS_1_LEVEL_SHIFT);
			break;
		}

		switch (pdata->micbias2_lvl) {
		case DA7218_MICBIAS_1_2V:
			micbias_lvl |= DA7218_MICBIAS_2_LP_MODE_MASK;
			break;
		case DA7218_MICBIAS_1_6V:
		case DA7218_MICBIAS_1_8V:
		case DA7218_MICBIAS_2_0V:
		case DA7218_MICBIAS_2_2V:
		case DA7218_MICBIAS_2_4V:
		case DA7218_MICBIAS_2_6V:
		case DA7218_MICBIAS_2_8V:
		case DA7218_MICBIAS_3_0V:
			micbias_lvl |= (pdata->micbias2_lvl <<
					 DA7218_MICBIAS_2_LEVEL_SHIFT);
			break;
		}

		snd_soc_component_write(component, DA7218_MICBIAS_CTRL, micbias_lvl);

		/* Mic */
		switch (pdata->mic1_amp_in_sel) {
		case DA7218_MIC_AMP_IN_SEL_DIFF:
		case DA7218_MIC_AMP_IN_SEL_SE_P:
		case DA7218_MIC_AMP_IN_SEL_SE_N:
			snd_soc_component_write(component, DA7218_MIC_1_SELECT,
				      pdata->mic1_amp_in_sel);
			break;
		}

		switch (pdata->mic2_amp_in_sel) {
		case DA7218_MIC_AMP_IN_SEL_DIFF:
		case DA7218_MIC_AMP_IN_SEL_SE_P:
		case DA7218_MIC_AMP_IN_SEL_SE_N:
			snd_soc_component_write(component, DA7218_MIC_2_SELECT,
				      pdata->mic2_amp_in_sel);
			break;
		}

		/* DMic */
		switch (pdata->dmic1_data_sel) {
		case DA7218_DMIC_DATA_LFALL_RRISE:
		case DA7218_DMIC_DATA_LRISE_RFALL:
			dmic_cfg |= (pdata->dmic1_data_sel <<
				     DA7218_DMIC_1_DATA_SEL_SHIFT);
			break;
		}

		switch (pdata->dmic1_samplephase) {
		case DA7218_DMIC_SAMPLE_ON_CLKEDGE:
		case DA7218_DMIC_SAMPLE_BETWEEN_CLKEDGE:
			dmic_cfg |= (pdata->dmic1_samplephase <<
				     DA7218_DMIC_1_SAMPLEPHASE_SHIFT);
			break;
		}

		switch (pdata->dmic1_clk_rate) {
		case DA7218_DMIC_CLK_3_0MHZ:
		case DA7218_DMIC_CLK_1_5MHZ:
			dmic_cfg |= (pdata->dmic1_clk_rate <<
				     DA7218_DMIC_1_CLK_RATE_SHIFT);
			break;
		}

		snd_soc_component_update_bits(component, DA7218_DMIC_1_CTRL,
				    DA7218_DMIC_1_DATA_SEL_MASK |
				    DA7218_DMIC_1_SAMPLEPHASE_MASK |
				    DA7218_DMIC_1_CLK_RATE_MASK, dmic_cfg);

		dmic_cfg = 0;
		switch (pdata->dmic2_data_sel) {
		case DA7218_DMIC_DATA_LFALL_RRISE:
		case DA7218_DMIC_DATA_LRISE_RFALL:
			dmic_cfg |= (pdata->dmic2_data_sel <<
				     DA7218_DMIC_2_DATA_SEL_SHIFT);
			break;
		}

		switch (pdata->dmic2_samplephase) {
		case DA7218_DMIC_SAMPLE_ON_CLKEDGE:
		case DA7218_DMIC_SAMPLE_BETWEEN_CLKEDGE:
			dmic_cfg |= (pdata->dmic2_samplephase <<
				     DA7218_DMIC_2_SAMPLEPHASE_SHIFT);
			break;
		}

		switch (pdata->dmic2_clk_rate) {
		case DA7218_DMIC_CLK_3_0MHZ:
		case DA7218_DMIC_CLK_1_5MHZ:
			dmic_cfg |= (pdata->dmic2_clk_rate <<
				     DA7218_DMIC_2_CLK_RATE_SHIFT);
			break;
		}

		snd_soc_component_update_bits(component, DA7218_DMIC_2_CTRL,
				    DA7218_DMIC_2_DATA_SEL_MASK |
				    DA7218_DMIC_2_SAMPLEPHASE_MASK |
				    DA7218_DMIC_2_CLK_RATE_MASK, dmic_cfg);

		/* DA7217 Specific */
		if (da7218->dev_id == DA7217_DEV_ID) {
			da7218->hp_single_supply =
				pdata->hp_diff_single_supply;

			if (da7218->hp_single_supply) {
				snd_soc_component_write(component, DA7218_HP_DIFF_UNLOCK,
					      DA7218_HP_DIFF_UNLOCK_VAL);
				snd_soc_component_update_bits(component, DA7218_HP_DIFF_CTRL,
						    DA7218_HP_AMP_SINGLE_SUPPLY_EN_MASK,
						    DA7218_HP_AMP_SINGLE_SUPPLY_EN_MASK);
			}
		}

		/* DA7218 Specific */
		if ((da7218->dev_id == DA7218_DEV_ID) &&
		    (pdata->hpldet_pdata)) {
			struct da7218_hpldet_pdata *hpldet_pdata =
				pdata->hpldet_pdata;
			u8 hpldet_cfg = 0;

			switch (hpldet_pdata->jack_rate) {
			case DA7218_HPLDET_JACK_RATE_5US:
			case DA7218_HPLDET_JACK_RATE_10US:
			case DA7218_HPLDET_JACK_RATE_20US:
			case DA7218_HPLDET_JACK_RATE_40US:
			case DA7218_HPLDET_JACK_RATE_80US:
			case DA7218_HPLDET_JACK_RATE_160US:
			case DA7218_HPLDET_JACK_RATE_320US:
			case DA7218_HPLDET_JACK_RATE_640US:
				hpldet_cfg |=
					(hpldet_pdata->jack_rate <<
					 DA7218_HPLDET_JACK_RATE_SHIFT);
				break;
			}

			switch (hpldet_pdata->jack_debounce) {
			case DA7218_HPLDET_JACK_DEBOUNCE_OFF:
			case DA7218_HPLDET_JACK_DEBOUNCE_2:
			case DA7218_HPLDET_JACK_DEBOUNCE_3:
			case DA7218_HPLDET_JACK_DEBOUNCE_4:
				hpldet_cfg |=
					(hpldet_pdata->jack_debounce <<
					 DA7218_HPLDET_JACK_DEBOUNCE_SHIFT);
				break;
			}

			switch (hpldet_pdata->jack_thr) {
			case DA7218_HPLDET_JACK_THR_84PCT:
			case DA7218_HPLDET_JACK_THR_88PCT:
			case DA7218_HPLDET_JACK_THR_92PCT:
			case DA7218_HPLDET_JACK_THR_96PCT:
				hpldet_cfg |=
					(hpldet_pdata->jack_thr <<
					 DA7218_HPLDET_JACK_THR_SHIFT);
				break;
			}
			snd_soc_component_update_bits(component, DA7218_HPLDET_JACK,
					    DA7218_HPLDET_JACK_RATE_MASK |
					    DA7218_HPLDET_JACK_DEBOUNCE_MASK |
					    DA7218_HPLDET_JACK_THR_MASK,
					    hpldet_cfg);

			hpldet_cfg = 0;
			if (hpldet_pdata->comp_inv)
				hpldet_cfg |= DA7218_HPLDET_COMP_INV_MASK;

			if (hpldet_pdata->hyst)
				hpldet_cfg |= DA7218_HPLDET_HYST_EN_MASK;

			if (hpldet_pdata->discharge)
				hpldet_cfg |= DA7218_HPLDET_DISCHARGE_EN_MASK;

			snd_soc_component_write(component, DA7218_HPLDET_CTRL, hpldet_cfg);
		}
	}
}