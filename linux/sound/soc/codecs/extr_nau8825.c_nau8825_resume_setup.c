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
struct nau8825 {struct regmap* regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  NAU8825_CLK_DIS ; 
 int NAU8825_IRQ_EJECT_DIS ; 
 int NAU8825_IRQ_EJECT_EN ; 
 int NAU8825_IRQ_HEADSET_COMPLETE_EN ; 
 int NAU8825_IRQ_INSERT_DIS ; 
 int NAU8825_IRQ_INSERT_EN ; 
 int NAU8825_IRQ_OUTPUT_EN ; 
 int NAU8825_JACK_DET_DB_BYPASS ; 
 int /*<<< orphan*/  NAU8825_REG_INTERRUPT_DIS_CTRL ; 
 int /*<<< orphan*/  NAU8825_REG_INTERRUPT_MASK ; 
 int /*<<< orphan*/  NAU8825_REG_JACK_DET_CTRL ; 
 int /*<<< orphan*/  nau8825_configure_sysclk (struct nau8825*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nau8825_int_status_clear_all (struct regmap*) ; 
 int /*<<< orphan*/  regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int nau8825_resume_setup(struct nau8825 *nau8825)
{
	struct regmap *regmap = nau8825->regmap;

	/* Close clock when jack type detection at manual mode */
	nau8825_configure_sysclk(nau8825, NAU8825_CLK_DIS, 0);

	/* Clear all interruption status */
	nau8825_int_status_clear_all(regmap);

	/* Enable both insertion and ejection interruptions, and then
	 * bypass de-bounce circuit.
	 */
	regmap_update_bits(regmap, NAU8825_REG_INTERRUPT_MASK,
		NAU8825_IRQ_OUTPUT_EN | NAU8825_IRQ_HEADSET_COMPLETE_EN |
		NAU8825_IRQ_EJECT_EN | NAU8825_IRQ_INSERT_EN,
		NAU8825_IRQ_OUTPUT_EN | NAU8825_IRQ_HEADSET_COMPLETE_EN);
	regmap_update_bits(regmap, NAU8825_REG_JACK_DET_CTRL,
		NAU8825_JACK_DET_DB_BYPASS, NAU8825_JACK_DET_DB_BYPASS);
	regmap_update_bits(regmap, NAU8825_REG_INTERRUPT_DIS_CTRL,
		NAU8825_IRQ_INSERT_DIS | NAU8825_IRQ_EJECT_DIS, 0);

	return 0;
}