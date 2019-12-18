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
struct net_bridge {scalar_t__ stp_enabled; int /*<<< orphan*/  lock; scalar_t__ hello_time; int /*<<< orphan*/  hello_timer; TYPE_1__* dev; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 scalar_t__ BR_KERNEL_STP ; 
 int IFF_UP ; 
 struct net_bridge* br ; 
 int /*<<< orphan*/  br_config_bpdu_generation (struct net_bridge*) ; 
 int /*<<< orphan*/  br_debug (struct net_bridge*,char*) ; 
 struct net_bridge* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hello_timer ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  round_jiffies (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void br_hello_timer_expired(struct timer_list *t)
{
	struct net_bridge *br = from_timer(br, t, hello_timer);

	br_debug(br, "hello timer expired\n");
	spin_lock(&br->lock);
	if (br->dev->flags & IFF_UP) {
		br_config_bpdu_generation(br);

		if (br->stp_enabled == BR_KERNEL_STP)
			mod_timer(&br->hello_timer,
				  round_jiffies(jiffies + br->hello_time));
	}
	spin_unlock(&br->lock);
}