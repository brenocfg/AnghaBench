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
struct snd_ymfpci {scalar_t__ start_count; int /*<<< orphan*/  reg_lock; int /*<<< orphan*/  interrupt_sleep; int /*<<< orphan*/  interrupt_sleep_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  YDSXGR_MODE ; 
 int /*<<< orphan*/  YDSXGR_STATUS ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int snd_ymfpci_readl (struct snd_ymfpci*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ymfpci_writel (struct snd_ymfpci*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void snd_ymfpci_hw_stop(struct snd_ymfpci *chip)
{
	unsigned long flags;
	long timeout = 1000;

	spin_lock_irqsave(&chip->reg_lock, flags);
	if (--chip->start_count > 0)
		goto __end;
	snd_ymfpci_writel(chip, YDSXGR_MODE,
			  snd_ymfpci_readl(chip, YDSXGR_MODE) & ~3);
	while (timeout-- > 0) {
		if ((snd_ymfpci_readl(chip, YDSXGR_STATUS) & 2) == 0)
			break;
	}
	if (atomic_read(&chip->interrupt_sleep_count)) {
		atomic_set(&chip->interrupt_sleep_count, 0);
		wake_up(&chip->interrupt_sleep);
	}
      __end:
      	spin_unlock_irqrestore(&chip->reg_lock, flags);
}