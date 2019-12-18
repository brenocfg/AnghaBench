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
struct net_bridge {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  br_ip4_multicast_leave_snoopers (struct net_bridge*) ; 
 int /*<<< orphan*/  br_ip6_multicast_leave_snoopers (struct net_bridge*) ; 

__attribute__((used)) static void br_multicast_leave_snoopers(struct net_bridge *br)
{
	br_ip4_multicast_leave_snoopers(br);
	br_ip6_multicast_leave_snoopers(br);
}