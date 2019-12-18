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
typedef  int /*<<< orphan*/  wait_queue_entry_t ;
struct snd_ymfpci {int /*<<< orphan*/  interrupt_sleep; int /*<<< orphan*/  interrupt_sleep_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  YDSXGR_MODE ; 
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  init_waitqueue_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_timeout_uninterruptible (int /*<<< orphan*/ ) ; 
 int snd_ymfpci_readl (struct snd_ymfpci*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void snd_ymfpci_irq_wait(struct snd_ymfpci *chip)
{
	wait_queue_entry_t wait;
	int loops = 4;

	while (loops-- > 0) {
		if ((snd_ymfpci_readl(chip, YDSXGR_MODE) & 3) == 0)
		 	continue;
		init_waitqueue_entry(&wait, current);
		add_wait_queue(&chip->interrupt_sleep, &wait);
		atomic_inc(&chip->interrupt_sleep_count);
		schedule_timeout_uninterruptible(msecs_to_jiffies(50));
		remove_wait_queue(&chip->interrupt_sleep, &wait);
	}
}