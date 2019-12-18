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
struct in_device {int /*<<< orphan*/  mc_tomb_lock; int /*<<< orphan*/  mr_ifc_timer; int /*<<< orphan*/  mr_gq_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int /*<<< orphan*/  igmp_gq_timer_expire ; 
 int /*<<< orphan*/  igmp_ifc_timer_expire ; 
 int /*<<< orphan*/  ip_mc_reset (struct in_device*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ip_mc_init_dev(struct in_device *in_dev)
{
	ASSERT_RTNL();

#ifdef CONFIG_IP_MULTICAST
	timer_setup(&in_dev->mr_gq_timer, igmp_gq_timer_expire, 0);
	timer_setup(&in_dev->mr_ifc_timer, igmp_ifc_timer_expire, 0);
#endif
	ip_mc_reset(in_dev);

	spin_lock_init(&in_dev->mc_tomb_lock);
}