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
struct regmap {int dummy; } ;
struct nau8824 {int sar_voltage; int sar_compare_time; int sar_sampling_time; int sar_threshold_num; int sar_hysteresis; int key_debounce; int* sar_threshold; struct regmap* regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  NAU8824_HYSTERESIS_MASK ; 
 int NAU8824_HYSTERESIS_SFT ; 
 int /*<<< orphan*/  NAU8824_LEVELS_NR_MASK ; 
 int NAU8824_LEVELS_NR_SFT ; 
 int /*<<< orphan*/  NAU8824_REG_SAR_ADC ; 
 int /*<<< orphan*/  NAU8824_REG_VDET_COEFFICIENT ; 
 int /*<<< orphan*/  NAU8824_REG_VDET_THRESHOLD_1 ; 
 int /*<<< orphan*/  NAU8824_REG_VDET_THRESHOLD_2 ; 
 int /*<<< orphan*/  NAU8824_REG_VDET_THRESHOLD_3 ; 
 int /*<<< orphan*/  NAU8824_REG_VDET_THRESHOLD_4 ; 
 int /*<<< orphan*/  NAU8824_SAR_COMPARE_TIME_MASK ; 
 int NAU8824_SAR_COMPARE_TIME_SFT ; 
 int /*<<< orphan*/  NAU8824_SAR_SAMPLING_TIME_MASK ; 
 int NAU8824_SAR_SAMPLING_TIME_SFT ; 
 int /*<<< orphan*/  NAU8824_SAR_TRACKING_GAIN_MASK ; 
 int NAU8824_SAR_TRACKING_GAIN_SFT ; 
 int /*<<< orphan*/  NAU8824_SHORTKEY_DEBOUNCE_MASK ; 
 int NAU8824_SHORTKEY_DEBOUNCE_SFT ; 
 int /*<<< orphan*/  regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  regmap_write (struct regmap*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void nau8824_setup_buttons(struct nau8824 *nau8824)
{
	struct regmap *regmap = nau8824->regmap;

	regmap_update_bits(regmap, NAU8824_REG_SAR_ADC,
		NAU8824_SAR_TRACKING_GAIN_MASK,
		nau8824->sar_voltage << NAU8824_SAR_TRACKING_GAIN_SFT);
	regmap_update_bits(regmap, NAU8824_REG_SAR_ADC,
		NAU8824_SAR_COMPARE_TIME_MASK,
		nau8824->sar_compare_time << NAU8824_SAR_COMPARE_TIME_SFT);
	regmap_update_bits(regmap, NAU8824_REG_SAR_ADC,
		NAU8824_SAR_SAMPLING_TIME_MASK,
		nau8824->sar_sampling_time << NAU8824_SAR_SAMPLING_TIME_SFT);

	regmap_update_bits(regmap, NAU8824_REG_VDET_COEFFICIENT,
		NAU8824_LEVELS_NR_MASK,
		(nau8824->sar_threshold_num - 1) << NAU8824_LEVELS_NR_SFT);
	regmap_update_bits(regmap, NAU8824_REG_VDET_COEFFICIENT,
		NAU8824_HYSTERESIS_MASK,
		nau8824->sar_hysteresis << NAU8824_HYSTERESIS_SFT);
	regmap_update_bits(regmap, NAU8824_REG_VDET_COEFFICIENT,
		NAU8824_SHORTKEY_DEBOUNCE_MASK,
		nau8824->key_debounce << NAU8824_SHORTKEY_DEBOUNCE_SFT);

	regmap_write(regmap, NAU8824_REG_VDET_THRESHOLD_1,
		(nau8824->sar_threshold[0] << 8) | nau8824->sar_threshold[1]);
	regmap_write(regmap, NAU8824_REG_VDET_THRESHOLD_2,
		(nau8824->sar_threshold[2] << 8) | nau8824->sar_threshold[3]);
	regmap_write(regmap, NAU8824_REG_VDET_THRESHOLD_3,
		(nau8824->sar_threshold[4] << 8) | nau8824->sar_threshold[5]);
	regmap_write(regmap, NAU8824_REG_VDET_THRESHOLD_4,
		(nau8824->sar_threshold[6] << 8) | nau8824->sar_threshold[7]);
}