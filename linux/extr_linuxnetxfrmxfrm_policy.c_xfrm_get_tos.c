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
struct xfrm_policy_afinfo {int (* get_tos ) (struct flowi const*) ;} ;
struct flowi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int stub1 (struct flowi const*) ; 
 struct xfrm_policy_afinfo* xfrm_policy_get_afinfo (int) ; 

__attribute__((used)) static int xfrm_get_tos(const struct flowi *fl, int family)
{
	const struct xfrm_policy_afinfo *afinfo;
	int tos;

	afinfo = xfrm_policy_get_afinfo(family);
	if (!afinfo)
		return 0;

	tos = afinfo->get_tos(fl);

	rcu_read_unlock();

	return tos;
}