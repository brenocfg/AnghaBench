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
struct slip {int /*<<< orphan*/  lock; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 struct slip* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_queue_stopped (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sl_tx_timeout(struct net_device *dev)
{
	struct slip *sl = netdev_priv(dev);

	spin_lock(&sl->lock);

	if (netif_queue_stopped(dev)) {
		if (!netif_running(dev))
			goto out;

		/* May be we must check transmitter timeout here ?
		 *      14 Oct 1994 Dmitry Gorodchanin.
		 */
#ifdef SL_CHECK_TRANSMIT
		if (time_before(jiffies, dev_trans_start(dev) + 20 * HZ))  {
			/* 20 sec timeout not reached */
			goto out;
		}
		printk(KERN_WARNING "%s: transmit timed out, %s?\n",
			dev->name,
			(tty_chars_in_buffer(sl->tty) || sl->xleft) ?
				"bad line quality" : "driver error");
		sl->xleft = 0;
		clear_bit(TTY_DO_WRITE_WAKEUP, &sl->tty->flags);
		sl_unlock(sl);
#endif
	}
out:
	spin_unlock(&sl->lock);
}