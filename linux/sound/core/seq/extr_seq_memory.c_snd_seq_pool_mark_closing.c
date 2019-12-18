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
struct snd_seq_pool {int closing; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 scalar_t__ snd_BUG_ON (int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void snd_seq_pool_mark_closing(struct snd_seq_pool *pool)
{
	unsigned long flags;

	if (snd_BUG_ON(!pool))
		return;
	spin_lock_irqsave(&pool->lock, flags);
	pool->closing = 1;
	spin_unlock_irqrestore(&pool->lock, flags);
}