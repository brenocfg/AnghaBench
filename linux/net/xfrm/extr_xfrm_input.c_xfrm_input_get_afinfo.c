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
struct xfrm_input_afinfo {int dummy; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 struct xfrm_input_afinfo* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/ * xfrm_input_afinfo ; 

__attribute__((used)) static const struct xfrm_input_afinfo *xfrm_input_get_afinfo(unsigned int family)
{
	const struct xfrm_input_afinfo *afinfo;

	if (WARN_ON_ONCE(family >= ARRAY_SIZE(xfrm_input_afinfo)))
		return NULL;

	rcu_read_lock();
	afinfo = rcu_dereference(xfrm_input_afinfo[family]);
	if (unlikely(!afinfo))
		rcu_read_unlock();
	return afinfo;
}