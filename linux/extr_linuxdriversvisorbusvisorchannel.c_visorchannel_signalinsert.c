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
struct visorchannel {int /*<<< orphan*/  insert_lock; scalar_t__ needs_lock; } ;

/* Variables and functions */
 int signalinsert_inner (struct visorchannel*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int visorchannel_signalinsert(struct visorchannel *channel, u32 queue,
			      void *msg)
{
	int rc;
	unsigned long flags;

	if (channel->needs_lock) {
		spin_lock_irqsave(&channel->insert_lock, flags);
		rc = signalinsert_inner(channel, queue, msg);
		spin_unlock_irqrestore(&channel->insert_lock, flags);
	} else {
		rc = signalinsert_inner(channel, queue, msg);
	}

	return rc;
}