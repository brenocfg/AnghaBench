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
struct tcp_ulp_ops {int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct tcp_ulp_ops* tcp_ulp_find_id (int const) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const struct tcp_ulp_ops *__tcp_ulp_lookup(const int uid)
{
	const struct tcp_ulp_ops *ulp;

	rcu_read_lock();
	ulp = tcp_ulp_find_id(uid);
	if (!ulp || !try_module_get(ulp->owner))
		ulp = NULL;
	rcu_read_unlock();
	return ulp;
}