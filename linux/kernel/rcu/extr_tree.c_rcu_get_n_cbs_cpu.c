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
struct rcu_data {int /*<<< orphan*/  cblist; } ;

/* Variables and functions */
 struct rcu_data* per_cpu_ptr (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rcu_data ; 
 scalar_t__ rcu_segcblist_is_enabled (int /*<<< orphan*/ *) ; 
 long rcu_segcblist_n_cbs (int /*<<< orphan*/ *) ; 

__attribute__((used)) static long rcu_get_n_cbs_cpu(int cpu)
{
	struct rcu_data *rdp = per_cpu_ptr(&rcu_data, cpu);

	if (rcu_segcblist_is_enabled(&rdp->cblist))
		return rcu_segcblist_n_cbs(&rdp->cblist);
	return 0;
}