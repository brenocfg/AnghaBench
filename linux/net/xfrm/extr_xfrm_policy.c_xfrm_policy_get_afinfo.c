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
struct xfrm_policy_afinfo {int dummy; } ;

/* Variables and functions */
 unsigned short ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 struct xfrm_policy_afinfo* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/ * xfrm_policy_afinfo ; 

__attribute__((used)) static const struct xfrm_policy_afinfo *xfrm_policy_get_afinfo(unsigned short family)
{
	const struct xfrm_policy_afinfo *afinfo;

	if (unlikely(family >= ARRAY_SIZE(xfrm_policy_afinfo)))
		return NULL;
	rcu_read_lock();
	afinfo = rcu_dereference(xfrm_policy_afinfo[family]);
	if (unlikely(!afinfo))
		rcu_read_unlock();
	return afinfo;
}