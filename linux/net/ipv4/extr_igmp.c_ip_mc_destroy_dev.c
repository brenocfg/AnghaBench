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
struct ip_mc_list {int /*<<< orphan*/  next_rcu; } ;
struct in_device {int /*<<< orphan*/  mc_count; int /*<<< orphan*/  mc_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int /*<<< orphan*/  igmpv3_clear_delrec (struct in_device*) ; 
 int /*<<< orphan*/  ip_ma_put (struct ip_mc_list*) ; 
 int /*<<< orphan*/  ip_mc_down (struct in_device*) ; 
 struct ip_mc_list* rtnl_dereference (int /*<<< orphan*/ ) ; 

void ip_mc_destroy_dev(struct in_device *in_dev)
{
	struct ip_mc_list *i;

	ASSERT_RTNL();

	/* Deactivate timers */
	ip_mc_down(in_dev);
#ifdef CONFIG_IP_MULTICAST
	igmpv3_clear_delrec(in_dev);
#endif

	while ((i = rtnl_dereference(in_dev->mc_list)) != NULL) {
		in_dev->mc_list = i->next_rcu;
		in_dev->mc_count--;
		ip_ma_put(i);
	}
}