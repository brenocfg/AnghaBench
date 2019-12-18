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
struct gpio_latch_chip {int /*<<< orphan*/ * gpios; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int gpio_direction_input (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_latch_lock (struct gpio_latch_chip*,int) ; 
 int /*<<< orphan*/  gpio_latch_unlock (struct gpio_latch_chip*,int) ; 
 struct gpio_latch_chip* to_gpio_latch_chip (struct gpio_chip*) ; 

__attribute__((used)) static int
gpio_latch_direction_input(struct gpio_chip *gc, unsigned offset)
{
	struct gpio_latch_chip *glc = to_gpio_latch_chip(gc);
	int ret;

	gpio_latch_lock(glc, false);
	ret = gpio_direction_input(glc->gpios[offset]);
	gpio_latch_unlock(glc, false);

	return ret;
}