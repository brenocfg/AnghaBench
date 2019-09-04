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
typedef  int /*<<< orphan*/  u32 ;
struct atlas7_gpio_chip {struct atlas7_gpio_bank* banks; } ;
struct atlas7_gpio_bank {int dummy; } ;

/* Variables and functions */
 size_t GPIO_TO_BANK (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct
atlas7_gpio_bank *atlas7_gpio_to_bank(struct atlas7_gpio_chip *a7gc, u32 gpio)
{
	return &a7gc->banks[GPIO_TO_BANK(gpio)];
}