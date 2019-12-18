#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int (* single ) (unsigned int) ;} ;
struct TYPE_3__ {int (* single ) (unsigned int) ;} ;
struct cpuhp_step {char const* name; int multi_instance; int /*<<< orphan*/  list; TYPE_2__ teardown; TYPE_1__ startup; } ;
typedef  enum cpuhp_state { ____Placeholder_cpuhp_state } cpuhp_state ;

/* Variables and functions */
 int CPUHP_AP_ONLINE_DYN ; 
 int CPUHP_BP_PREPARE_DYN ; 
 int EBUSY ; 
 int /*<<< orphan*/  INIT_HLIST_HEAD (int /*<<< orphan*/ *) ; 
 struct cpuhp_step* cpuhp_get_step (int) ; 
 int cpuhp_reserve_state (int) ; 

__attribute__((used)) static int cpuhp_store_callbacks(enum cpuhp_state state, const char *name,
				 int (*startup)(unsigned int cpu),
				 int (*teardown)(unsigned int cpu),
				 bool multi_instance)
{
	/* (Un)Install the callbacks for further cpu hotplug operations */
	struct cpuhp_step *sp;
	int ret = 0;

	/*
	 * If name is NULL, then the state gets removed.
	 *
	 * CPUHP_AP_ONLINE_DYN and CPUHP_BP_PREPARE_DYN are handed out on
	 * the first allocation from these dynamic ranges, so the removal
	 * would trigger a new allocation and clear the wrong (already
	 * empty) state, leaving the callbacks of the to be cleared state
	 * dangling, which causes wreckage on the next hotplug operation.
	 */
	if (name && (state == CPUHP_AP_ONLINE_DYN ||
		     state == CPUHP_BP_PREPARE_DYN)) {
		ret = cpuhp_reserve_state(state);
		if (ret < 0)
			return ret;
		state = ret;
	}
	sp = cpuhp_get_step(state);
	if (name && sp->name)
		return -EBUSY;

	sp->startup.single = startup;
	sp->teardown.single = teardown;
	sp->name = name;
	sp->multi_instance = multi_instance;
	INIT_HLIST_HEAD(&sp->list);
	return ret;
}