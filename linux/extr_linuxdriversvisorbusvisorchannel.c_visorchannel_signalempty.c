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
typedef  int /*<<< orphan*/  u32 ;
struct visorchannel {int /*<<< orphan*/  remove_lock; int /*<<< orphan*/  needs_lock; } ;

/* Variables and functions */
 int queue_empty (struct visorchannel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

bool visorchannel_signalempty(struct visorchannel *channel, u32 queue)
{
	bool rc;
	unsigned long flags;

	if (!channel->needs_lock)
		return queue_empty(channel, queue);
	spin_lock_irqsave(&channel->remove_lock, flags);
	rc = queue_empty(channel, queue);
	spin_unlock_irqrestore(&channel->remove_lock, flags);
	return rc;
}