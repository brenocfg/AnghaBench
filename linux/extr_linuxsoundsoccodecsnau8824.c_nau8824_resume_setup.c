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
struct nau8824 {int /*<<< orphan*/  regmap; scalar_t__ irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  NAU8824_CLK_DIS ; 
 int NAU8824_IRQ_EJECT_DIS ; 
 int NAU8824_IRQ_EJECT_EN ; 
 int NAU8824_IRQ_INSERT_DIS ; 
 int NAU8824_IRQ_INSERT_EN ; 
 int NAU8824_JD_SLEEP_MODE ; 
 int /*<<< orphan*/  NAU8824_REG_ENA_CTRL ; 
 int /*<<< orphan*/  NAU8824_REG_INTERRUPT_SETTING ; 
 int /*<<< orphan*/  NAU8824_REG_INTERRUPT_SETTING_1 ; 
 int /*<<< orphan*/  nau8824_config_sysclk (struct nau8824*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nau8824_int_status_clear_all (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void nau8824_resume_setup(struct nau8824 *nau8824)
{
	nau8824_config_sysclk(nau8824, NAU8824_CLK_DIS, 0);
	if (nau8824->irq) {
		/* Clear all interruption status */
		nau8824_int_status_clear_all(nau8824->regmap);
		/* Enable jack detection at sleep mode, insertion detection,
		 * and ejection detection.
		 */
		regmap_update_bits(nau8824->regmap, NAU8824_REG_ENA_CTRL,
			NAU8824_JD_SLEEP_MODE, NAU8824_JD_SLEEP_MODE);
		regmap_update_bits(nau8824->regmap,
			NAU8824_REG_INTERRUPT_SETTING_1,
			NAU8824_IRQ_EJECT_EN | NAU8824_IRQ_INSERT_EN,
			NAU8824_IRQ_EJECT_EN | NAU8824_IRQ_INSERT_EN);
		regmap_update_bits(nau8824->regmap,
			NAU8824_REG_INTERRUPT_SETTING,
			NAU8824_IRQ_EJECT_DIS | NAU8824_IRQ_INSERT_DIS, 0);
	}
}