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
struct cftype {char* name; scalar_t__ max_write_len; int flags; int /*<<< orphan*/ * ss; int /*<<< orphan*/ * kf_ops; } ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 int __CFTYPE_NOT_ON_DFL ; 
 int __CFTYPE_ONLY_ON_DFL ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cgroup_exit_cftypes(struct cftype *cfts)
{
	struct cftype *cft;

	for (cft = cfts; cft->name[0] != '\0'; cft++) {
		/* free copy for custom atomic_write_len, see init_cftypes() */
		if (cft->max_write_len && cft->max_write_len != PAGE_SIZE)
			kfree(cft->kf_ops);
		cft->kf_ops = NULL;
		cft->ss = NULL;

		/* revert flags set by cgroup core while adding @cfts */
		cft->flags &= ~(__CFTYPE_ONLY_ON_DFL | __CFTYPE_NOT_ON_DFL);
	}
}