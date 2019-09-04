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
struct bcm2835_pinctrl {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int GPIO_REG_OFFSET (unsigned int) ; 
 int /*<<< orphan*/  GPIO_REG_SHIFT (unsigned int) ; 
 int /*<<< orphan*/  bcm2835_gpio_wr (struct bcm2835_pinctrl*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void bcm2835_gpio_set_bit(struct bcm2835_pinctrl *pc,
		unsigned reg, unsigned bit)
{
	reg += GPIO_REG_OFFSET(bit) * 4;
	bcm2835_gpio_wr(pc, reg, BIT(GPIO_REG_SHIFT(bit)));
}