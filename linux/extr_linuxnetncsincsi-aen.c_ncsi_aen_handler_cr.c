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
struct ncsi_dev_priv {int /*<<< orphan*/  lock; int /*<<< orphan*/  channel_queue; } ;
struct ncsi_channel {scalar_t__ state; int /*<<< orphan*/  link; int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  channel; } ;
struct ncsi_aen_pkt_hdr {TYPE_1__ common; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ NCSI_CHANNEL_ACTIVE ; 
 scalar_t__ NCSI_CHANNEL_INACTIVE ; 
 scalar_t__ NCSI_CHANNEL_INVISIBLE ; 
 int /*<<< orphan*/  list_add_tail_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ncsi_find_package_and_channel (struct ncsi_dev_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ncsi_channel**) ; 
 int ncsi_process_next_channel (struct ncsi_dev_priv*) ; 
 int /*<<< orphan*/  ncsi_stop_channel_monitor (struct ncsi_channel*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int ncsi_aen_handler_cr(struct ncsi_dev_priv *ndp,
			       struct ncsi_aen_pkt_hdr *h)
{
	struct ncsi_channel *nc;
	unsigned long flags;

	/* Find the NCSI channel */
	ncsi_find_package_and_channel(ndp, h->common.channel, NULL, &nc);
	if (!nc)
		return -ENODEV;

	spin_lock_irqsave(&nc->lock, flags);
	if (!list_empty(&nc->link) ||
	    nc->state != NCSI_CHANNEL_ACTIVE) {
		spin_unlock_irqrestore(&nc->lock, flags);
		return 0;
	}
	spin_unlock_irqrestore(&nc->lock, flags);

	ncsi_stop_channel_monitor(nc);
	spin_lock_irqsave(&nc->lock, flags);
	nc->state = NCSI_CHANNEL_INVISIBLE;
	spin_unlock_irqrestore(&nc->lock, flags);

	spin_lock_irqsave(&ndp->lock, flags);
	nc->state = NCSI_CHANNEL_INACTIVE;
	list_add_tail_rcu(&nc->link, &ndp->channel_queue);
	spin_unlock_irqrestore(&ndp->lock, flags);

	return ncsi_process_next_channel(ndp);
}