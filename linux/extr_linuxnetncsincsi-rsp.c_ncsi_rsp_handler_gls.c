#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  channel; } ;
struct TYPE_5__ {TYPE_1__ common; } ;
struct ncsi_rsp_gls_pkt {int /*<<< orphan*/  oem_status; int /*<<< orphan*/  other; int /*<<< orphan*/  status; TYPE_2__ rsp; } ;
struct ncsi_request {int flags; int /*<<< orphan*/  rsp; struct ncsi_dev_priv* ndp; } ;
struct ncsi_dev_priv {int dummy; } ;
struct ncsi_channel_mode {void** data; } ;
struct TYPE_6__ {int /*<<< orphan*/  state; } ;
struct ncsi_channel {int /*<<< orphan*/  lock; TYPE_3__ monitor; struct ncsi_channel_mode* modes; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  NCSI_CHANNEL_MONITOR_START ; 
 size_t NCSI_MODE_LINK ; 
 int NCSI_REQ_FLAG_EVENT_DRIVEN ; 
 int /*<<< orphan*/  ncsi_find_package_and_channel (struct ncsi_dev_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ncsi_channel**) ; 
 void* ntohl (int /*<<< orphan*/ ) ; 
 scalar_t__ skb_network_header (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int ncsi_rsp_handler_gls(struct ncsi_request *nr)
{
	struct ncsi_rsp_gls_pkt *rsp;
	struct ncsi_dev_priv *ndp = nr->ndp;
	struct ncsi_channel *nc;
	struct ncsi_channel_mode *ncm;
	unsigned long flags;

	/* Find the package and channel */
	rsp = (struct ncsi_rsp_gls_pkt *)skb_network_header(nr->rsp);
	ncsi_find_package_and_channel(ndp, rsp->rsp.common.channel,
				      NULL, &nc);
	if (!nc)
		return -ENODEV;

	ncm = &nc->modes[NCSI_MODE_LINK];
	ncm->data[2] = ntohl(rsp->status);
	ncm->data[3] = ntohl(rsp->other);
	ncm->data[4] = ntohl(rsp->oem_status);

	if (nr->flags & NCSI_REQ_FLAG_EVENT_DRIVEN)
		return 0;

	/* Reset the channel monitor if it has been enabled */
	spin_lock_irqsave(&nc->lock, flags);
	nc->monitor.state = NCSI_CHANNEL_MONITOR_START;
	spin_unlock_irqrestore(&nc->lock, flags);

	return 0;
}