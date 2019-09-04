#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct ncsi_dev_priv {int flags; int /*<<< orphan*/  lock; int /*<<< orphan*/  channel_queue; TYPE_2__ ndev; } ;
struct ncsi_channel_mode {unsigned long* data; } ;
struct ncsi_channel {int state; int /*<<< orphan*/  link; int /*<<< orphan*/  lock; int /*<<< orphan*/  id; struct ncsi_channel_mode* modes; } ;
struct TYPE_3__ {int /*<<< orphan*/  channel; } ;
struct ncsi_aen_pkt_hdr {TYPE_1__ common; } ;
struct ncsi_aen_lsc_pkt {int /*<<< orphan*/  oem_status; int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int ENODEV ; 
 int NCSI_CHANNEL_ACTIVE ; 
 int NCSI_CHANNEL_INACTIVE ; 
 int NCSI_DEV_HWA ; 
 int NCSI_DEV_RESHUFFLE ; 
 size_t NCSI_MODE_LINK ; 
 int /*<<< orphan*/  list_add_tail_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ncsi_find_package_and_channel (struct ncsi_dev_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ncsi_channel**) ; 
 int ncsi_process_next_channel (struct ncsi_dev_priv*) ; 
 int /*<<< orphan*/  ncsi_stop_channel_monitor (struct ncsi_channel*) ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*) ; 
 void* ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int ncsi_aen_handler_lsc(struct ncsi_dev_priv *ndp,
				struct ncsi_aen_pkt_hdr *h)
{
	struct ncsi_aen_lsc_pkt *lsc;
	struct ncsi_channel *nc;
	struct ncsi_channel_mode *ncm;
	bool chained;
	int state;
	unsigned long old_data, data;
	unsigned long flags;

	/* Find the NCSI channel */
	ncsi_find_package_and_channel(ndp, h->common.channel, NULL, &nc);
	if (!nc)
		return -ENODEV;

	/* Update the link status */
	lsc = (struct ncsi_aen_lsc_pkt *)h;

	spin_lock_irqsave(&nc->lock, flags);
	ncm = &nc->modes[NCSI_MODE_LINK];
	old_data = ncm->data[2];
	data = ntohl(lsc->status);
	ncm->data[2] = data;
	ncm->data[4] = ntohl(lsc->oem_status);

	netdev_dbg(ndp->ndev.dev, "NCSI: LSC AEN - channel %u state %s\n",
		   nc->id, data & 0x1 ? "up" : "down");

	chained = !list_empty(&nc->link);
	state = nc->state;
	spin_unlock_irqrestore(&nc->lock, flags);

	if (!((old_data ^ data) & 0x1) || chained)
		return 0;
	if (!(state == NCSI_CHANNEL_INACTIVE && (data & 0x1)) &&
	    !(state == NCSI_CHANNEL_ACTIVE && !(data & 0x1)))
		return 0;

	if (!(ndp->flags & NCSI_DEV_HWA) &&
	    state == NCSI_CHANNEL_ACTIVE)
		ndp->flags |= NCSI_DEV_RESHUFFLE;

	ncsi_stop_channel_monitor(nc);
	spin_lock_irqsave(&ndp->lock, flags);
	list_add_tail_rcu(&nc->link, &ndp->channel_queue);
	spin_unlock_irqrestore(&ndp->lock, flags);

	return ncsi_process_next_channel(ndp);
}