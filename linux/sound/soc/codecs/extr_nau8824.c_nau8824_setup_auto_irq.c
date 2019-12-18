#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct regmap {int dummy; } ;
struct nau8824 {TYPE_1__* dapm; struct regmap* regmap; } ;
struct TYPE_2__ {scalar_t__ bias_level; } ;

/* Variables and functions */
 int /*<<< orphan*/  NAU8824_CLK_INTERNAL ; 
 int NAU8824_IRQ_EJECT_DIS ; 
 int NAU8824_IRQ_EJECT_EN ; 
 int NAU8824_IRQ_INSERT_EN ; 
 int NAU8824_JD_SLEEP_MODE ; 
 int /*<<< orphan*/  NAU8824_REG_ENA_CTRL ; 
 int /*<<< orphan*/  NAU8824_REG_INTERRUPT_SETTING ; 
 int /*<<< orphan*/  NAU8824_REG_INTERRUPT_SETTING_1 ; 
 scalar_t__ SND_SOC_BIAS_PREPARE ; 
 int /*<<< orphan*/  nau8824_config_sysclk (struct nau8824*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void nau8824_setup_auto_irq(struct nau8824 *nau8824)
{
	struct regmap *regmap = nau8824->regmap;

	/* Enable jack ejection interruption. */
	regmap_update_bits(regmap, NAU8824_REG_INTERRUPT_SETTING_1,
		NAU8824_IRQ_INSERT_EN | NAU8824_IRQ_EJECT_EN,
		NAU8824_IRQ_EJECT_EN);
	regmap_update_bits(regmap, NAU8824_REG_INTERRUPT_SETTING,
		NAU8824_IRQ_EJECT_DIS, 0);
	/* Enable internal VCO needed for interruptions */
	if (nau8824->dapm->bias_level < SND_SOC_BIAS_PREPARE)
		nau8824_config_sysclk(nau8824, NAU8824_CLK_INTERNAL, 0);
	regmap_update_bits(regmap, NAU8824_REG_ENA_CTRL,
		NAU8824_JD_SLEEP_MODE, 0);
}