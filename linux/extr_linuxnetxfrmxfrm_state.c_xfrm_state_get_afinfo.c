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
struct xfrm_state_afinfo {int dummy; } ;

/* Variables and functions */
 unsigned int NPROTO ; 
 struct xfrm_state_afinfo* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/ * xfrm_state_afinfo ; 

struct xfrm_state_afinfo *xfrm_state_get_afinfo(unsigned int family)
{
	struct xfrm_state_afinfo *afinfo;
	if (unlikely(family >= NPROTO))
		return NULL;
	rcu_read_lock();
	afinfo = rcu_dereference(xfrm_state_afinfo[family]);
	if (unlikely(!afinfo))
		rcu_read_unlock();
	return afinfo;
}