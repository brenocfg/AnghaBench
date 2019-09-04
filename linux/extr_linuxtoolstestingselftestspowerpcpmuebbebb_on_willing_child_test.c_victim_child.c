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
typedef  union pipe {int dummy; } pipe ;
struct TYPE_3__ {int ebb_count; } ;
struct TYPE_4__ {TYPE_1__ stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  FAIL_IF (int) ; 
 int core_busy_loop () ; 
 int /*<<< orphan*/  count_pmc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dump_ebb_state () ; 
 int /*<<< orphan*/  ebb_enable_pmc_counting (int) ; 
 int /*<<< orphan*/  ebb_freeze_pmcs () ; 
 int /*<<< orphan*/  ebb_global_disable () ; 
 int /*<<< orphan*/  ebb_global_enable () ; 
 TYPE_2__ ebb_state ; 
 int notify_parent (union pipe) ; 
 int /*<<< orphan*/  sample_period ; 
 int /*<<< orphan*/  setup_ebb_handler (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  standard_ebb_callee ; 
 int wait_for_parent (union pipe) ; 

__attribute__((used)) static int victim_child(union pipe read_pipe, union pipe write_pipe)
{
	FAIL_IF(wait_for_parent(read_pipe));

	/* Setup our EBB handler, before the EBB event is created */
	ebb_enable_pmc_counting(1);
	setup_ebb_handler(standard_ebb_callee);
	ebb_global_enable();

	FAIL_IF(notify_parent(write_pipe));

	while (ebb_state.stats.ebb_count < 20) {
		FAIL_IF(core_busy_loop());
	}

	ebb_global_disable();
	ebb_freeze_pmcs();

	count_pmc(1, sample_period);

	dump_ebb_state();

	FAIL_IF(ebb_state.stats.ebb_count == 0);

	return 0;
}