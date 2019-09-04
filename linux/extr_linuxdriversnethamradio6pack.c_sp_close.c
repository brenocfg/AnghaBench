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
struct sixpack {int /*<<< orphan*/  lock; TYPE_1__* tty; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  TTY_DO_WRITE_WAKEUP ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct sixpack* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sp_close(struct net_device *dev)
{
	struct sixpack *sp = netdev_priv(dev);

	spin_lock_bh(&sp->lock);
	if (sp->tty) {
		/* TTY discipline is running. */
		clear_bit(TTY_DO_WRITE_WAKEUP, &sp->tty->flags);
	}
	netif_stop_queue(dev);
	spin_unlock_bh(&sp->lock);

	return 0;
}