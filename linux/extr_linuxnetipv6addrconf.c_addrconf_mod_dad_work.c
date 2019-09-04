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
struct inet6_ifaddr {int /*<<< orphan*/  dad_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  addrconf_wq ; 
 int /*<<< orphan*/  in6_ifa_hold (struct inet6_ifaddr*) ; 
 int /*<<< orphan*/  in6_ifa_put (struct inet6_ifaddr*) ; 
 scalar_t__ mod_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void addrconf_mod_dad_work(struct inet6_ifaddr *ifp,
				   unsigned long delay)
{
	in6_ifa_hold(ifp);
	if (mod_delayed_work(addrconf_wq, &ifp->dad_work, delay))
		in6_ifa_put(ifp);
}