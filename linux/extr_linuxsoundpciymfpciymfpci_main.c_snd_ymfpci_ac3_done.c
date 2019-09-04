#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * area; } ;
struct snd_ymfpci {TYPE_1__ ac3_tmp_base; int /*<<< orphan*/  reg_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  YDSXGR_MAPOFEFFECT ; 
 int /*<<< orphan*/  snd_dma_free_pages (TYPE_1__*) ; 
 int snd_ymfpci_readl (struct snd_ymfpci*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ymfpci_writel (struct snd_ymfpci*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_ymfpci_ac3_done(struct snd_ymfpci *chip)
{
	spin_lock_irq(&chip->reg_lock);
	snd_ymfpci_writel(chip, YDSXGR_MAPOFEFFECT,
			  snd_ymfpci_readl(chip, YDSXGR_MAPOFEFFECT) & ~(3 << 3));
	spin_unlock_irq(&chip->reg_lock);
	// snd_ymfpci_irq_wait(chip);
	if (chip->ac3_tmp_base.area) {
		snd_dma_free_pages(&chip->ac3_tmp_base);
		chip->ac3_tmp_base.area = NULL;
	}
	return 0;
}