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
struct ncsi_dev_priv {TYPE_2__ ndev; } ;
struct ncsi_channel_mode {int* data; } ;
struct ncsi_channel {int /*<<< orphan*/  id; int /*<<< orphan*/  lock; struct ncsi_channel_mode* modes; } ;
struct TYPE_3__ {int /*<<< orphan*/  channel; } ;
struct ncsi_aen_pkt_hdr {TYPE_1__ common; } ;
struct ncsi_aen_hncdsc_pkt {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int ENODEV ; 
 size_t NCSI_MODE_LINK ; 
 int /*<<< orphan*/  ncsi_find_package_and_channel (struct ncsi_dev_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ncsi_channel**) ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 
 int ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int ncsi_aen_handler_hncdsc(struct ncsi_dev_priv *ndp,
				   struct ncsi_aen_pkt_hdr *h)
{
	struct ncsi_channel *nc;
	struct ncsi_channel_mode *ncm;
	struct ncsi_aen_hncdsc_pkt *hncdsc;
	unsigned long flags;

	/* Find the NCSI channel */
	ncsi_find_package_and_channel(ndp, h->common.channel, NULL, &nc);
	if (!nc)
		return -ENODEV;

	spin_lock_irqsave(&nc->lock, flags);
	ncm = &nc->modes[NCSI_MODE_LINK];
	hncdsc = (struct ncsi_aen_hncdsc_pkt *)h;
	ncm->data[3] = ntohl(hncdsc->status);
	spin_unlock_irqrestore(&nc->lock, flags);
	netdev_dbg(ndp->ndev.dev,
		   "NCSI: host driver %srunning on channel %u\n",
		   ncm->data[3] & 0x1 ? "" : "not ", nc->id);

	return 0;
}