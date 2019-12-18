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
struct timer_list {int dummy; } ;
struct ncsi_request {int enabled; scalar_t__ flags; scalar_t__ cmd; scalar_t__ rsp; struct ncsi_dev_priv* ndp; } ;
struct ncsi_package {int dummy; } ;
struct ncsi_dev_priv {int /*<<< orphan*/  lock; } ;
struct TYPE_3__ {int /*<<< orphan*/  channel; } ;
struct TYPE_4__ {TYPE_1__ common; } ;
struct ncsi_cmd_pkt {TYPE_2__ cmd; } ;
struct ncsi_channel {int dummy; } ;

/* Variables and functions */
 scalar_t__ NCSI_REQ_FLAG_NETLINK_DRIVEN ; 
 struct ncsi_request* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ncsi_find_package_and_channel (struct ncsi_dev_priv*,int /*<<< orphan*/ ,struct ncsi_package**,struct ncsi_channel**) ; 
 int /*<<< orphan*/  ncsi_free_request (struct ncsi_request*) ; 
 int /*<<< orphan*/  ncsi_send_netlink_timeout (struct ncsi_request*,struct ncsi_package*,struct ncsi_channel*) ; 
 struct ncsi_request* nr ; 
 scalar_t__ skb_network_header (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  timer ; 

__attribute__((used)) static void ncsi_request_timeout(struct timer_list *t)
{
	struct ncsi_request *nr = from_timer(nr, t, timer);
	struct ncsi_dev_priv *ndp = nr->ndp;
	struct ncsi_cmd_pkt *cmd;
	struct ncsi_package *np;
	struct ncsi_channel *nc;
	unsigned long flags;

	/* If the request already had associated response,
	 * let the response handler to release it.
	 */
	spin_lock_irqsave(&ndp->lock, flags);
	nr->enabled = false;
	if (nr->rsp || !nr->cmd) {
		spin_unlock_irqrestore(&ndp->lock, flags);
		return;
	}
	spin_unlock_irqrestore(&ndp->lock, flags);

	if (nr->flags == NCSI_REQ_FLAG_NETLINK_DRIVEN) {
		if (nr->cmd) {
			/* Find the package */
			cmd = (struct ncsi_cmd_pkt *)
			      skb_network_header(nr->cmd);
			ncsi_find_package_and_channel(ndp,
						      cmd->cmd.common.channel,
						      &np, &nc);
			ncsi_send_netlink_timeout(nr, np, nc);
		}
	}

	/* Release the request */
	ncsi_free_request(nr);
}