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
struct net_bridge {int /*<<< orphan*/  ip4_own_query; } ;
struct TYPE_2__ {int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 struct net_bridge* br ; 
 int /*<<< orphan*/  br_multicast_querier_expired (struct net_bridge*,int /*<<< orphan*/ *) ; 
 struct net_bridge* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 TYPE_1__ ip4_other_query ; 

__attribute__((used)) static void br_ip4_multicast_querier_expired(struct timer_list *t)
{
	struct net_bridge *br = from_timer(br, t, ip4_other_query.timer);

	br_multicast_querier_expired(br, &br->ip4_own_query);
}