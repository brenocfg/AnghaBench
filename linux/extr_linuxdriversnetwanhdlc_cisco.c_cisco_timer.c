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
struct net_device {int dummy; } ;
struct TYPE_4__ {scalar_t__ expires; } ;
struct TYPE_3__ {int timeout; int interval; } ;
struct cisco_state {TYPE_2__ timer; TYPE_1__ settings; int /*<<< orphan*/  lock; int /*<<< orphan*/  rxseq; int /*<<< orphan*/  txseq; scalar_t__ up; scalar_t__ last_poll; struct net_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CISCO_KEEPALIVE_REQ ; 
 int HZ ; 
 int /*<<< orphan*/  add_timer (TYPE_2__*) ; 
 int /*<<< orphan*/  cisco_keepalive_send (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cisco_state* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*) ; 
 int /*<<< orphan*/  netif_dormant_on (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct cisco_state* st ; 
 scalar_t__ time_after (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  timer ; 

__attribute__((used)) static void cisco_timer(struct timer_list *t)
{
	struct cisco_state *st = from_timer(st, t, timer);
	struct net_device *dev = st->dev;

	spin_lock(&st->lock);
	if (st->up &&
	    time_after(jiffies, st->last_poll + st->settings.timeout * HZ)) {
		st->up = 0;
		netdev_info(dev, "Link down\n");
		netif_dormant_on(dev);
	}

	cisco_keepalive_send(dev, CISCO_KEEPALIVE_REQ, htonl(++st->txseq),
			     htonl(st->rxseq));
	spin_unlock(&st->lock);

	st->timer.expires = jiffies + st->settings.interval * HZ;
	add_timer(&st->timer);
}