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
typedef  int u32 ;
struct nmk_gpio_chip {int rwimsc; int fwimsc; scalar_t__ addr; int /*<<< orphan*/  (* set_ioforce ) (int) ;} ;

/* Variables and functions */
 int BIT (unsigned int) ; 
 scalar_t__ NMK_GPIO_FWIMSC ; 
 scalar_t__ NMK_GPIO_RWIMSC ; 
 int /*<<< orphan*/  __nmk_gpio_set_mode (struct nmk_gpio_chip*,unsigned int,int) ; 
 int /*<<< orphan*/  stub1 (int) ; 
 int /*<<< orphan*/  stub2 (int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void __nmk_gpio_set_mode_safe(struct nmk_gpio_chip *nmk_chip,
				     unsigned offset, int gpio_mode,
				     bool glitch)
{
	u32 rwimsc = nmk_chip->rwimsc;
	u32 fwimsc = nmk_chip->fwimsc;

	if (glitch && nmk_chip->set_ioforce) {
		u32 bit = BIT(offset);

		/* Prevent spurious wakeups */
		writel(rwimsc & ~bit, nmk_chip->addr + NMK_GPIO_RWIMSC);
		writel(fwimsc & ~bit, nmk_chip->addr + NMK_GPIO_FWIMSC);

		nmk_chip->set_ioforce(true);
	}

	__nmk_gpio_set_mode(nmk_chip, offset, gpio_mode);

	if (glitch && nmk_chip->set_ioforce) {
		nmk_chip->set_ioforce(false);

		writel(rwimsc, nmk_chip->addr + NMK_GPIO_RWIMSC);
		writel(fwimsc, nmk_chip->addr + NMK_GPIO_FWIMSC);
	}
}