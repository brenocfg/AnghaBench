#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {void* expires; } ;
struct ifmcaddr6 {int /*<<< orphan*/  mca_flags; int /*<<< orphan*/  mca_refcnt; TYPE_1__ mca_timer; int /*<<< orphan*/  mca_addr; } ;

/* Variables and functions */
 scalar_t__ IPV6_ADDR_MC_SCOPE (int /*<<< orphan*/ *) ; 
 scalar_t__ IPV6_ADDR_SCOPE_LINKLOCAL ; 
 int /*<<< orphan*/  MAF_TIMER_RUNNING ; 
 scalar_t__ del_timer (TYPE_1__*) ; 
 scalar_t__ ipv6_addr_is_ll_all_nodes (int /*<<< orphan*/ *) ; 
 void* jiffies ; 
 int /*<<< orphan*/  mod_timer (TYPE_1__*,void*) ; 
 unsigned long prandom_u32 () ; 
 int /*<<< orphan*/  refcount_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_inc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void igmp6_group_queried(struct ifmcaddr6 *ma, unsigned long resptime)
{
	unsigned long delay = resptime;

	/* Do not start timer for these addresses */
	if (ipv6_addr_is_ll_all_nodes(&ma->mca_addr) ||
	    IPV6_ADDR_MC_SCOPE(&ma->mca_addr) < IPV6_ADDR_SCOPE_LINKLOCAL)
		return;

	if (del_timer(&ma->mca_timer)) {
		refcount_dec(&ma->mca_refcnt);
		delay = ma->mca_timer.expires - jiffies;
	}

	if (delay >= resptime)
		delay = prandom_u32() % resptime;

	ma->mca_timer.expires = jiffies + delay;
	if (!mod_timer(&ma->mca_timer, jiffies + delay))
		refcount_inc(&ma->mca_refcnt);
	ma->mca_flags |= MAF_TIMER_RUNNING;
}