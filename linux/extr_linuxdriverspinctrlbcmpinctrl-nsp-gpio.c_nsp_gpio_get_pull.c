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
struct nsp_gpio {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  IO_CTRL ; 
 int /*<<< orphan*/  NSP_PULL_DOWN_EN ; 
 int /*<<< orphan*/  NSP_PULL_UP_EN ; 
 int nsp_get_bit (struct nsp_gpio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void nsp_gpio_get_pull(struct nsp_gpio *chip, unsigned gpio,
			      bool *pull_up, bool *pull_down)
{
	unsigned long flags;

	raw_spin_lock_irqsave(&chip->lock, flags);
	*pull_up = nsp_get_bit(chip, IO_CTRL, NSP_PULL_UP_EN, gpio);
	*pull_down = nsp_get_bit(chip, IO_CTRL, NSP_PULL_DOWN_EN, gpio);
	raw_spin_unlock_irqrestore(&chip->lock, flags);
}