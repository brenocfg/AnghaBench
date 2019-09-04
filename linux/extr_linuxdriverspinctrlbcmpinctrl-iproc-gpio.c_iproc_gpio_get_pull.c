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
struct iproc_gpio {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPROC_GPIO_PAD_RES_OFFSET ; 
 int /*<<< orphan*/  IPROC_GPIO_RES_EN_OFFSET ; 
 int iproc_get_bit (struct iproc_gpio*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void iproc_gpio_get_pull(struct iproc_gpio *chip, unsigned gpio,
				 bool *disable, bool *pull_up)
{
	unsigned long flags;

	raw_spin_lock_irqsave(&chip->lock, flags);
	*disable = !iproc_get_bit(chip, IPROC_GPIO_RES_EN_OFFSET, gpio);
	*pull_up = iproc_get_bit(chip, IPROC_GPIO_PAD_RES_OFFSET, gpio);
	raw_spin_unlock_irqrestore(&chip->lock, flags);
}