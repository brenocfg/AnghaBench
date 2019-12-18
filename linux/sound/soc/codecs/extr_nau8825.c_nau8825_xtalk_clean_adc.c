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
struct nau8825 {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int NAU8825_ADC_VREFSEL_MASK ; 
 int NAU8825_POWERUP_ADCL ; 
 int /*<<< orphan*/  NAU8825_REG_ANALOG_ADC_2 ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nau8825_xtalk_clean_adc(struct nau8825 *nau8825)
{
	/* Power down left ADC and restore voltage to Vmid */
	regmap_update_bits(nau8825->regmap, NAU8825_REG_ANALOG_ADC_2,
		NAU8825_POWERUP_ADCL | NAU8825_ADC_VREFSEL_MASK, 0);
}