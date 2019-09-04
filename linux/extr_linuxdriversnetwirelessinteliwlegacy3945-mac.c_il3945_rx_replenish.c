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
struct il_priv {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  il3945_rx_allocate (struct il_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  il3945_rx_queue_restock (struct il_priv*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void
il3945_rx_replenish(void *data)
{
	struct il_priv *il = data;
	unsigned long flags;

	il3945_rx_allocate(il, GFP_KERNEL);

	spin_lock_irqsave(&il->lock, flags);
	il3945_rx_queue_restock(il);
	spin_unlock_irqrestore(&il->lock, flags);
}