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
struct sk_buff {int dummy; } ;
struct ncsi_request {int enabled; int used; int flags; struct sk_buff* rsp; struct sk_buff* cmd; int /*<<< orphan*/  timer; struct ncsi_dev_priv* ndp; } ;
struct ncsi_dev_priv {scalar_t__ pending_req_num; int /*<<< orphan*/  work; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int NCSI_REQ_FLAG_EVENT_DRIVEN ; 
 int /*<<< orphan*/  consume_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void ncsi_free_request(struct ncsi_request *nr)
{
	struct ncsi_dev_priv *ndp = nr->ndp;
	struct sk_buff *cmd, *rsp;
	unsigned long flags;
	bool driven;

	if (nr->enabled) {
		nr->enabled = false;
		del_timer_sync(&nr->timer);
	}

	spin_lock_irqsave(&ndp->lock, flags);
	cmd = nr->cmd;
	rsp = nr->rsp;
	nr->cmd = NULL;
	nr->rsp = NULL;
	nr->used = false;
	driven = !!(nr->flags & NCSI_REQ_FLAG_EVENT_DRIVEN);
	spin_unlock_irqrestore(&ndp->lock, flags);

	if (driven && cmd && --ndp->pending_req_num == 0)
		schedule_work(&ndp->work);

	/* Release command and response */
	consume_skb(cmd);
	consume_skb(rsp);
}