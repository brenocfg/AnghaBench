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
struct timer_list {int dummy; } ;
struct lec_priv {int /*<<< orphan*/  lec_arp_lock; } ;
struct lec_arp_table {int /*<<< orphan*/  next; TYPE_1__* recv_vcc; scalar_t__ vcc; int /*<<< orphan*/  timer; struct lec_priv* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  vci; int /*<<< orphan*/  vpi; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 struct lec_arp_table* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hlist_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lec_arp_clear_vccs (struct lec_arp_table*) ; 
 int /*<<< orphan*/  lec_arp_put (struct lec_arp_table*) ; 
 int /*<<< orphan*/  pr_debug (char*,struct lec_arp_table*,struct lec_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  timer ; 
 struct lec_arp_table* to_remove ; 

__attribute__((used)) static void lec_arp_expire_vcc(struct timer_list *t)
{
	unsigned long flags;
	struct lec_arp_table *to_remove = from_timer(to_remove, t, timer);
	struct lec_priv *priv = to_remove->priv;

	del_timer(&to_remove->timer);

	pr_debug("%p %p: vpi:%d vci:%d\n",
		 to_remove, priv,
		 to_remove->vcc ? to_remove->recv_vcc->vpi : 0,
		 to_remove->vcc ? to_remove->recv_vcc->vci : 0);

	spin_lock_irqsave(&priv->lec_arp_lock, flags);
	hlist_del(&to_remove->next);
	spin_unlock_irqrestore(&priv->lec_arp_lock, flags);

	lec_arp_clear_vccs(to_remove);
	lec_arp_put(to_remove);
}