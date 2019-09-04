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
struct sk_buff {int /*<<< orphan*/ * dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  id; TYPE_2__* up; } ;
struct caif_device_entry {int xoff; void (* xoff_skb_dtor ) (struct sk_buff*) ;TYPE_1__ layer; int /*<<< orphan*/  flow_lock; struct sk_buff* xoff_skb; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* ctrlcmd ) (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  _CAIF_CTRLCMD_PHYIF_FLOW_ON_IND ; 
 struct caif_device_entry* caif_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  caifd_hold (struct caif_device_entry*) ; 
 int /*<<< orphan*/  caifd_put (struct caif_device_entry*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void caif_flow_cb(struct sk_buff *skb)
{
	struct caif_device_entry *caifd;
	void (*dtor)(struct sk_buff *skb) = NULL;
	bool send_xoff;

	WARN_ON(skb->dev == NULL);

	rcu_read_lock();
	caifd = caif_get(skb->dev);

	WARN_ON(caifd == NULL);
	if (!caifd) {
		rcu_read_unlock();
		return;
	}

	caifd_hold(caifd);
	rcu_read_unlock();

	spin_lock_bh(&caifd->flow_lock);
	send_xoff = caifd->xoff;
	caifd->xoff = 0;
	dtor = caifd->xoff_skb_dtor;

	if (WARN_ON(caifd->xoff_skb != skb))
		skb = NULL;

	caifd->xoff_skb = NULL;
	caifd->xoff_skb_dtor = NULL;

	spin_unlock_bh(&caifd->flow_lock);

	if (dtor && skb)
		dtor(skb);

	if (send_xoff)
		caifd->layer.up->
			ctrlcmd(caifd->layer.up,
				_CAIF_CTRLCMD_PHYIF_FLOW_ON_IND,
				caifd->layer.id);
	caifd_put(caifd);
}