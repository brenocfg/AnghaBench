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
 int /*<<< orphan*/  NAU8825_CLK_INTERNAL ; 
 int NAU8825_I2S_BLK_DIV_MASK ; 
 int NAU8825_I2S_LRC_DIV_MASK ; 
 int NAU8825_I2S_MS_MASK ; 
 int NAU8825_I2S_MS_SLAVE ; 
 int NAU8825_IRQ_RMS_EN ; 
 int /*<<< orphan*/  NAU8825_REG_I2S_PCM_CTRL2 ; 
 int /*<<< orphan*/  NAU8825_REG_IMM_MODE_CTRL ; 
 int /*<<< orphan*/  NAU8825_REG_INTERRUPT_MASK ; 
 int /*<<< orphan*/  nau8825_configure_sysclk (struct nau8825*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nau8825_xtalk_clean_adc (struct nau8825*) ; 
 int /*<<< orphan*/  nau8825_xtalk_clean_dac (struct nau8825*) ; 
 int /*<<< orphan*/  nau8825_xtalk_restore (struct nau8825*,int) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nau8825_xtalk_clean(struct nau8825 *nau8825, bool cause_cancel)
{
	/* Enable internal VCO needed for interruptions */
	nau8825_configure_sysclk(nau8825, NAU8825_CLK_INTERNAL, 0);
	nau8825_xtalk_clean_dac(nau8825);
	nau8825_xtalk_clean_adc(nau8825);
	/* Clear cross talk parameters and disable */
	regmap_write(nau8825->regmap, NAU8825_REG_IMM_MODE_CTRL, 0);
	/* RMS intrruption disable */
	regmap_update_bits(nau8825->regmap, NAU8825_REG_INTERRUPT_MASK,
		NAU8825_IRQ_RMS_EN, NAU8825_IRQ_RMS_EN);
	/* Recover default value for IIS */
	regmap_update_bits(nau8825->regmap, NAU8825_REG_I2S_PCM_CTRL2,
		NAU8825_I2S_MS_MASK | NAU8825_I2S_LRC_DIV_MASK |
		NAU8825_I2S_BLK_DIV_MASK, NAU8825_I2S_MS_SLAVE);
	/* Restore value of specific register for cross talk */
	nau8825_xtalk_restore(nau8825, cause_cancel);
}