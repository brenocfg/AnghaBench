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
struct TYPE_2__ {int /*<<< orphan*/  head; } ;
struct sata_oxnas_host_priv {int /*<<< orphan*/  core_lock; TYPE_1__ fast_wait_queue; } ;
struct ata_host {struct sata_oxnas_host_priv* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int sata_core_has_fast_waiters(struct ata_host *ah)
{
	int has_waiters;
	unsigned long flags;
	struct sata_oxnas_host_priv *hd = ah->private_data;

	spin_lock_irqsave(&hd->core_lock, flags);
	has_waiters = !list_empty(&hd->fast_wait_queue.head);
	spin_unlock_irqrestore(&hd->core_lock, flags);

	return has_waiters;
}