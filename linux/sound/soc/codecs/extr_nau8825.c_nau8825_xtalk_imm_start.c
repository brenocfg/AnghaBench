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
struct nau8825 {int xtalk_state; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int NAU8825_ADC_DIG_VOL_MASK ; 
 int NAU8825_BIAS_HPL_IMP ; 
 int NAU8825_BIAS_HPR_IMP ; 
 int NAU8825_BIAS_TESTDACL_EN ; 
 int NAU8825_BIAS_TESTDACR_EN ; 
 int NAU8825_IMM_EN ; 
 int /*<<< orphan*/  NAU8825_REG_ADC_DGAIN_CTRL ; 
 int /*<<< orphan*/  NAU8825_REG_BIAS_ADJ ; 
 int /*<<< orphan*/  NAU8825_REG_IMM_MODE_CTRL ; 
#define  NAU8825_XTALK_HPL_R2L 129 
#define  NAU8825_XTALK_HPR_R2L 128 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void nau8825_xtalk_imm_start(struct nau8825 *nau8825, int vol)
{
	/* Apply ADC volume for better cross talk performance */
	regmap_update_bits(nau8825->regmap, NAU8825_REG_ADC_DGAIN_CTRL,
				NAU8825_ADC_DIG_VOL_MASK, vol);
	/* Disables JKTIP(HPL) DAC channel for right to left measurement.
	 * Do it before sending signal in order to erase pop noise.
	 */
	regmap_update_bits(nau8825->regmap, NAU8825_REG_BIAS_ADJ,
		NAU8825_BIAS_TESTDACR_EN | NAU8825_BIAS_TESTDACL_EN,
		NAU8825_BIAS_TESTDACL_EN);
	switch (nau8825->xtalk_state) {
	case NAU8825_XTALK_HPR_R2L:
		/* Enable right headphone impedance */
		regmap_update_bits(nau8825->regmap, NAU8825_REG_BIAS_ADJ,
			NAU8825_BIAS_HPR_IMP | NAU8825_BIAS_HPL_IMP,
			NAU8825_BIAS_HPR_IMP);
		break;
	case NAU8825_XTALK_HPL_R2L:
		/* Enable left headphone impedance */
		regmap_update_bits(nau8825->regmap, NAU8825_REG_BIAS_ADJ,
			NAU8825_BIAS_HPR_IMP | NAU8825_BIAS_HPL_IMP,
			NAU8825_BIAS_HPL_IMP);
		break;
	default:
		break;
	}
	msleep(100);
	/* Impedance measurement mode enable */
	regmap_update_bits(nau8825->regmap, NAU8825_REG_IMM_MODE_CTRL,
				NAU8825_IMM_EN, NAU8825_IMM_EN);
}