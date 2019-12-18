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
struct net_bridge {int /*<<< orphan*/  lock; scalar_t__ bridge_hello_time; int /*<<< orphan*/  tcn_timer; TYPE_1__* dev; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int IFF_UP ; 
 struct net_bridge* br ; 
 int /*<<< orphan*/  br_debug (struct net_bridge*,char*) ; 
 int /*<<< orphan*/  br_is_root_bridge (struct net_bridge*) ; 
 int /*<<< orphan*/  br_transmit_tcn (struct net_bridge*) ; 
 struct net_bridge* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcn_timer ; 

__attribute__((used)) static void br_tcn_timer_expired(struct timer_list *t)
{
	struct net_bridge *br = from_timer(br, t, tcn_timer);

	br_debug(br, "tcn timer expired\n");
	spin_lock(&br->lock);
	if (!br_is_root_bridge(br) && (br->dev->flags & IFF_UP)) {
		br_transmit_tcn(br);

		mod_timer(&br->tcn_timer, jiffies + br->bridge_hello_time);
	}
	spin_unlock(&br->lock);
}