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
struct pids_cgroup {int /*<<< orphan*/  counter; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic64_add (int,int /*<<< orphan*/ *) ; 
 struct pids_cgroup* parent_pids (struct pids_cgroup*) ; 

__attribute__((used)) static void pids_charge(struct pids_cgroup *pids, int num)
{
	struct pids_cgroup *p;

	for (p = pids; parent_pids(p); p = parent_pids(p))
		atomic64_add(num, &p->counter);
}