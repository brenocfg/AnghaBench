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
struct x25_asy {int /*<<< orphan*/  lock; scalar_t__ xleft; scalar_t__ rcount; TYPE_1__* tty; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  TTY_DO_WRITE_WAKEUP ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct x25_asy* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int x25_asy_close(struct net_device *dev)
{
	struct x25_asy *sl = netdev_priv(dev);

	spin_lock(&sl->lock);
	if (sl->tty)
		clear_bit(TTY_DO_WRITE_WAKEUP, &sl->tty->flags);

	netif_stop_queue(dev);
	sl->rcount = 0;
	sl->xleft  = 0;
	spin_unlock(&sl->lock);
	return 0;
}