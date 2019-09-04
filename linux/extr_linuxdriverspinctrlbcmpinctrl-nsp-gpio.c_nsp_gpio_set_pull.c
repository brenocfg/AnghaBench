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
struct nsp_gpio {int /*<<< orphan*/  dev; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  IO_CTRL ; 
 int /*<<< orphan*/  NSP_PULL_DOWN_EN ; 
 int /*<<< orphan*/  NSP_PULL_UP_EN ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int,int,int) ; 
 int /*<<< orphan*/  nsp_set_bit (struct nsp_gpio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int nsp_gpio_set_pull(struct nsp_gpio *chip, unsigned gpio,
			     bool pull_up, bool pull_down)
{
	unsigned long flags;

	raw_spin_lock_irqsave(&chip->lock, flags);
	nsp_set_bit(chip, IO_CTRL, NSP_PULL_DOWN_EN, gpio, pull_down);
	nsp_set_bit(chip, IO_CTRL, NSP_PULL_UP_EN, gpio, pull_up);
	raw_spin_unlock_irqrestore(&chip->lock, flags);

	dev_dbg(chip->dev, "gpio:%u set pullup:%d pulldown: %d\n",
		gpio, pull_up, pull_down);
	return 0;
}