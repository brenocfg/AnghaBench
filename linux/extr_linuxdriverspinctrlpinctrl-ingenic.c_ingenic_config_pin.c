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
typedef  int /*<<< orphan*/  u8 ;
struct ingenic_pinctrl {int /*<<< orphan*/  map; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (unsigned int) ; 
 unsigned int PINS_PER_GPIO_CHIP ; 
 scalar_t__ REG_CLEAR (int /*<<< orphan*/ ) ; 
 scalar_t__ REG_SET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void ingenic_config_pin(struct ingenic_pinctrl *jzpc,
		unsigned int pin, u8 reg, bool set)
{
	unsigned int idx = pin % PINS_PER_GPIO_CHIP;
	unsigned int offt = pin / PINS_PER_GPIO_CHIP;

	regmap_write(jzpc->map, offt * 0x100 +
			(set ? REG_SET(reg) : REG_CLEAR(reg)), BIT(idx));
}