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
struct nau8824 {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int NAU8824_IRQ_EJECT_EN ; 
 int NAU8824_IRQ_INSERT_EN ; 
 int NAU8824_JD_SLEEP_MODE ; 
 int /*<<< orphan*/  NAU8824_REG_ENA_CTRL ; 
 int /*<<< orphan*/  NAU8824_REG_INTERRUPT_SETTING ; 
 int /*<<< orphan*/  NAU8824_REG_INTERRUPT_SETTING_1 ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int nau8824_setup_irq(struct nau8824 *nau8824)
{
	/* Disable interruption before codec initiation done */
	regmap_update_bits(nau8824->regmap, NAU8824_REG_ENA_CTRL,
		NAU8824_JD_SLEEP_MODE, NAU8824_JD_SLEEP_MODE);
	regmap_update_bits(nau8824->regmap,
		NAU8824_REG_INTERRUPT_SETTING, 0x3ff, 0x3ff);
	regmap_update_bits(nau8824->regmap, NAU8824_REG_INTERRUPT_SETTING_1,
		NAU8824_IRQ_EJECT_EN | NAU8824_IRQ_INSERT_EN, 0);

	return 0;
}