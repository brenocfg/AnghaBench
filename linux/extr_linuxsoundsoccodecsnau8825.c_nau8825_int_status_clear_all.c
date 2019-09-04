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

/* Variables and functions */
 int NAU8825_REG_DATA_LEN ; 
 int /*<<< orphan*/  NAU8825_REG_INT_CLR_KEY_STATUS ; 
 int /*<<< orphan*/  NAU8825_REG_IRQ_STATUS ; 
 int /*<<< orphan*/  regmap_read (struct regmap*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  regmap_write (struct regmap*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void nau8825_int_status_clear_all(struct regmap *regmap)
{
	int active_irq, clear_irq, i;

	/* Reset the intrruption status from rightmost bit if the corres-
	 * ponding irq event occurs.
	 */
	regmap_read(regmap, NAU8825_REG_IRQ_STATUS, &active_irq);
	for (i = 0; i < NAU8825_REG_DATA_LEN; i++) {
		clear_irq = (0x1 << i);
		if (active_irq & clear_irq)
			regmap_write(regmap,
				NAU8825_REG_INT_CLR_KEY_STATUS, clear_irq);
	}
}