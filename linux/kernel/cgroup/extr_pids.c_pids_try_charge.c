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
struct pids_cgroup {scalar_t__ limit; int /*<<< orphan*/  counter; } ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 int EAGAIN ; 
 scalar_t__ atomic64_add_return (int,int /*<<< orphan*/ *) ; 
 struct pids_cgroup* parent_pids (struct pids_cgroup*) ; 
 int /*<<< orphan*/  pids_cancel (struct pids_cgroup*,int) ; 

__attribute__((used)) static int pids_try_charge(struct pids_cgroup *pids, int num)
{
	struct pids_cgroup *p, *q;

	for (p = pids; parent_pids(p); p = parent_pids(p)) {
		int64_t new = atomic64_add_return(num, &p->counter);

		/*
		 * Since new is capped to the maximum number of pid_t, if
		 * p->limit is %PIDS_MAX then we know that this test will never
		 * fail.
		 */
		if (new > p->limit)
			goto revert;
	}

	return 0;

revert:
	for (q = pids; q != p; q = parent_pids(q))
		pids_cancel(q, num);
	pids_cancel(p, num);

	return -EAGAIN;
}