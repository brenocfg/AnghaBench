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
struct arizona_pdata {int* spk_mute; int* spk_fmt; unsigned int* dmic_ref; int* inmode; scalar_t__* out_mono; } ;
struct arizona {int type; int /*<<< orphan*/  regmap; int /*<<< orphan*/  notifier; struct arizona_pdata pdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARIZONA_ADC_DIGITAL_VOLUME_1L ; 
 int /*<<< orphan*/  ARIZONA_ADC_DIGITAL_VOLUME_1R ; 
 scalar_t__ ARIZONA_IN1L_CONTROL ; 
 unsigned int ARIZONA_IN1L_SRC_SE_MASK ; 
 unsigned int ARIZONA_IN1L_SRC_SE_SHIFT ; 
 unsigned int ARIZONA_IN1R_SRC_SE_MASK ; 
 unsigned int ARIZONA_IN1R_SRC_SE_SHIFT ; 
 unsigned int ARIZONA_IN1_DMIC_SUP_MASK ; 
 unsigned int ARIZONA_IN1_DMIC_SUP_SHIFT ; 
 unsigned int ARIZONA_IN1_MODE_MASK ; 
 int ARIZONA_IN1_MODE_SHIFT ; 
 unsigned int ARIZONA_IN1_SINGLE_ENDED_MASK ; 
 int ARIZONA_IN1_SINGLE_ENDED_SHIFT ; 
 int ARIZONA_INMODE_DMIC ; 
 unsigned int ARIZONA_INMODE_SE ; 
 int ARIZONA_MAX_INPUT ; 
 int ARIZONA_MAX_OUTPUT ; 
 int ARIZONA_MAX_PDM_SPK ; 
 unsigned int ARIZONA_OUT1_MONO ; 
 scalar_t__ ARIZONA_OUTPUT_PATH_CONFIG_1L ; 
 scalar_t__ ARIZONA_PDM_SPK1_CTRL_1 ; 
 scalar_t__ ARIZONA_PDM_SPK1_CTRL_2 ; 
 unsigned int ARIZONA_SPK1_FMT_MASK ; 
 unsigned int ARIZONA_SPK1_MUTE_ENDIAN_MASK ; 
 unsigned int ARIZONA_SPK1_MUTE_SEQ1_MASK ; 
 int /*<<< orphan*/  BLOCKING_INIT_NOTIFIER_HEAD (int /*<<< orphan*/ *) ; 
#define  WM1814 129 
#define  WM8998 128 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,scalar_t__,unsigned int,unsigned int) ; 

int arizona_init_common(struct arizona *arizona)
{
	struct arizona_pdata *pdata = &arizona->pdata;
	unsigned int val, mask;
	int i;

	BLOCKING_INIT_NOTIFIER_HEAD(&arizona->notifier);

	for (i = 0; i < ARIZONA_MAX_OUTPUT; ++i) {
		/* Default is 0 so noop with defaults */
		if (pdata->out_mono[i])
			val = ARIZONA_OUT1_MONO;
		else
			val = 0;

		regmap_update_bits(arizona->regmap,
				   ARIZONA_OUTPUT_PATH_CONFIG_1L + (i * 8),
				   ARIZONA_OUT1_MONO, val);
	}

	for (i = 0; i < ARIZONA_MAX_PDM_SPK; i++) {
		if (pdata->spk_mute[i])
			regmap_update_bits(arizona->regmap,
					   ARIZONA_PDM_SPK1_CTRL_1 + (i * 2),
					   ARIZONA_SPK1_MUTE_ENDIAN_MASK |
					   ARIZONA_SPK1_MUTE_SEQ1_MASK,
					   pdata->spk_mute[i]);

		if (pdata->spk_fmt[i])
			regmap_update_bits(arizona->regmap,
					   ARIZONA_PDM_SPK1_CTRL_2 + (i * 2),
					   ARIZONA_SPK1_FMT_MASK,
					   pdata->spk_fmt[i]);
	}

	for (i = 0; i < ARIZONA_MAX_INPUT; i++) {
		/* Default for both is 0 so noop with defaults */
		val = pdata->dmic_ref[i] << ARIZONA_IN1_DMIC_SUP_SHIFT;
		if (pdata->inmode[i] & ARIZONA_INMODE_DMIC)
			val |= 1 << ARIZONA_IN1_MODE_SHIFT;

		switch (arizona->type) {
		case WM8998:
		case WM1814:
			regmap_update_bits(arizona->regmap,
				ARIZONA_ADC_DIGITAL_VOLUME_1L + (i * 8),
				ARIZONA_IN1L_SRC_SE_MASK,
				(pdata->inmode[i] & ARIZONA_INMODE_SE)
					<< ARIZONA_IN1L_SRC_SE_SHIFT);

			regmap_update_bits(arizona->regmap,
				ARIZONA_ADC_DIGITAL_VOLUME_1R + (i * 8),
				ARIZONA_IN1R_SRC_SE_MASK,
				(pdata->inmode[i] & ARIZONA_INMODE_SE)
					<< ARIZONA_IN1R_SRC_SE_SHIFT);

			mask = ARIZONA_IN1_DMIC_SUP_MASK |
			       ARIZONA_IN1_MODE_MASK;
			break;
		default:
			if (pdata->inmode[i] & ARIZONA_INMODE_SE)
				val |= 1 << ARIZONA_IN1_SINGLE_ENDED_SHIFT;

			mask = ARIZONA_IN1_DMIC_SUP_MASK |
			       ARIZONA_IN1_MODE_MASK |
			       ARIZONA_IN1_SINGLE_ENDED_MASK;
			break;
		}

		regmap_update_bits(arizona->regmap,
				   ARIZONA_IN1L_CONTROL + (i * 8),
				   mask, val);
	}

	return 0;
}