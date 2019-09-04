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
struct TYPE_4__ {scalar_t__ linked; } ;
struct TYPE_3__ {scalar_t__ linked; } ;
struct net_dev_context {int /*<<< orphan*/  dev; TYPE_2__ tx; TYPE_1__ rx; } ;
struct most_interface {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_hold (int /*<<< orphan*/ ) ; 
 struct net_dev_context* get_net_dev (struct most_interface*) ; 
 int /*<<< orphan*/  list_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static struct net_dev_context *get_net_dev_hold(struct most_interface *iface)
{
	struct net_dev_context *nd;
	unsigned long flags;

	spin_lock_irqsave(&list_lock, flags);
	nd = get_net_dev(iface);
	if (nd && nd->rx.linked && nd->tx.linked)
		dev_hold(nd->dev);
	else
		nd = NULL;
	spin_unlock_irqrestore(&list_lock, flags);
	return nd;
}