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
 int NAU8825_CHANRGE_PUMP_EN ; 
 int NAU8825_CLASSG_LDAC_EN ; 
 int NAU8825_CLASSG_RDAC_EN ; 
 int NAU8825_ENABLE_ADC ; 
 int NAU8825_ENABLE_ADC_CLK ; 
 int NAU8825_ENABLE_DACL ; 
 int NAU8825_ENABLE_DACR ; 
 int NAU8825_ENABLE_DAC_CLK ; 
 int NAU8825_HP_BOOST_DIS ; 
 int NAU8825_JAMNODCLOW ; 
 int NAU8825_POWERUP_DRV_IN_L ; 
 int NAU8825_POWERUP_DRV_IN_R ; 
 int NAU8825_POWERUP_HP_DRV_L ; 
 int NAU8825_POWERUP_HP_DRV_R ; 
 int NAU8825_POWERUP_INTEGR_L ; 
 int NAU8825_POWERUP_INTEGR_R ; 
 int NAU8825_RDAC_CLK_EN ; 
 int NAU8825_RDAC_EN ; 
 int NAU8825_RDAC_FS_BCLK_ENB ; 
 int /*<<< orphan*/  NAU8825_REG_BOOST ; 
 int /*<<< orphan*/  NAU8825_REG_CHARGE_PUMP ; 
 int /*<<< orphan*/  NAU8825_REG_CLASSG_CTRL ; 
 int /*<<< orphan*/  NAU8825_REG_ENA_CTRL ; 
 int /*<<< orphan*/  NAU8825_REG_HSD_CTRL ; 
 int /*<<< orphan*/  NAU8825_REG_POWER_UP_CONTROL ; 
 int /*<<< orphan*/  NAU8825_REG_RDAC ; 
 int NAU8825_SPKR_DWN1L ; 
 int NAU8825_SPKR_DWN1R ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void nau8825_xtalk_prepare_dac(struct nau8825 *nau8825)
{
	/* Enable power of DAC path */
	regmap_update_bits(nau8825->regmap, NAU8825_REG_ENA_CTRL,
		NAU8825_ENABLE_DACR | NAU8825_ENABLE_DACL |
		NAU8825_ENABLE_ADC | NAU8825_ENABLE_ADC_CLK |
		NAU8825_ENABLE_DAC_CLK, NAU8825_ENABLE_DACR |
		NAU8825_ENABLE_DACL | NAU8825_ENABLE_ADC |
		NAU8825_ENABLE_ADC_CLK | NAU8825_ENABLE_DAC_CLK);
	/* Prevent startup click by letting charge pump to ramp up and
	 * change bump enable
	 */
	regmap_update_bits(nau8825->regmap, NAU8825_REG_CHARGE_PUMP,
		NAU8825_JAMNODCLOW | NAU8825_CHANRGE_PUMP_EN,
		NAU8825_JAMNODCLOW | NAU8825_CHANRGE_PUMP_EN);
	/* Enable clock sync of DAC and DAC clock */
	regmap_update_bits(nau8825->regmap, NAU8825_REG_RDAC,
		NAU8825_RDAC_EN | NAU8825_RDAC_CLK_EN |
		NAU8825_RDAC_FS_BCLK_ENB,
		NAU8825_RDAC_EN | NAU8825_RDAC_CLK_EN);
	/* Power up output driver with 2 stage */
	regmap_update_bits(nau8825->regmap, NAU8825_REG_POWER_UP_CONTROL,
		NAU8825_POWERUP_INTEGR_R | NAU8825_POWERUP_INTEGR_L |
		NAU8825_POWERUP_DRV_IN_R | NAU8825_POWERUP_DRV_IN_L,
		NAU8825_POWERUP_INTEGR_R | NAU8825_POWERUP_INTEGR_L |
		NAU8825_POWERUP_DRV_IN_R | NAU8825_POWERUP_DRV_IN_L);
	regmap_update_bits(nau8825->regmap, NAU8825_REG_POWER_UP_CONTROL,
		NAU8825_POWERUP_HP_DRV_R | NAU8825_POWERUP_HP_DRV_L,
		NAU8825_POWERUP_HP_DRV_R | NAU8825_POWERUP_HP_DRV_L);
	/* HP outputs not shouted to ground  */
	regmap_update_bits(nau8825->regmap, NAU8825_REG_HSD_CTRL,
		NAU8825_SPKR_DWN1R | NAU8825_SPKR_DWN1L, 0);
	/* Enable HP boost driver */
	regmap_update_bits(nau8825->regmap, NAU8825_REG_BOOST,
		NAU8825_HP_BOOST_DIS, NAU8825_HP_BOOST_DIS);
	/* Enable class G compare path to supply 1.8V or 0.9V. */
	regmap_update_bits(nau8825->regmap, NAU8825_REG_CLASSG_CTRL,
		NAU8825_CLASSG_LDAC_EN | NAU8825_CLASSG_RDAC_EN,
		NAU8825_CLASSG_LDAC_EN | NAU8825_CLASSG_RDAC_EN);
}