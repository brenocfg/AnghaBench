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
struct snd_ymfpci {int active_bank; int /*<<< orphan*/  reg_lock; int /*<<< orphan*/  start_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  YDSXGR_CTRLSELECT ; 
 int /*<<< orphan*/  YDSXGR_MODE ; 
 int snd_ymfpci_readl (struct snd_ymfpci*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ymfpci_writel (struct snd_ymfpci*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void snd_ymfpci_hw_start(struct snd_ymfpci *chip)
{
	unsigned long flags;

	spin_lock_irqsave(&chip->reg_lock, flags);
	if (chip->start_count++ > 0)
		goto __end;
	snd_ymfpci_writel(chip, YDSXGR_MODE,
			  snd_ymfpci_readl(chip, YDSXGR_MODE) | 3);
	chip->active_bank = snd_ymfpci_readl(chip, YDSXGR_CTRLSELECT) & 1;
      __end:
      	spin_unlock_irqrestore(&chip->reg_lock, flags);
}