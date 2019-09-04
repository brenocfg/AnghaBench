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
struct pistachio_internal_dac {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  PISTACHIO_INTERNAL_DAC_CTRL ; 
 int /*<<< orphan*/  PISTACHIO_INTERNAL_DAC_CTRL_PWRDN_MASK ; 
 int /*<<< orphan*/  PISTACHIO_INTERNAL_DAC_PWR ; 
 int /*<<< orphan*/  pistachio_internal_dac_reg_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pistachio_internal_dac_pwr_off(struct pistachio_internal_dac *dac)
{
	regmap_update_bits(dac->regmap, PISTACHIO_INTERNAL_DAC_CTRL,
		PISTACHIO_INTERNAL_DAC_CTRL_PWRDN_MASK,
		PISTACHIO_INTERNAL_DAC_CTRL_PWRDN_MASK);

	pistachio_internal_dac_reg_writel(dac->regmap, 0,
					PISTACHIO_INTERNAL_DAC_PWR);
}