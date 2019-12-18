#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct test_driver {size_t cpu; void* stop; void* start; } ;
typedef  int /*<<< orphan*/  ktime_t ;
struct TYPE_5__ {scalar_t__ time; int /*<<< orphan*/  test_failed; int /*<<< orphan*/  test_passed; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* test_func ) () ;} ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  cpumask_of (size_t) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  do_div (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 void* get_cycles () ; 
 int /*<<< orphan*/  kthread_should_stop () ; 
 int /*<<< orphan*/  ktime_get () ; 
 scalar_t__ ktime_us_delta (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 TYPE_2__** per_cpu_test_data ; 
 int /*<<< orphan*/  pr_err (char*,size_t) ; 
 int /*<<< orphan*/  prepare_for_test_rwsem ; 
 int run_test_mask ; 
 int /*<<< orphan*/  sequential_test_order ; 
 scalar_t__ set_cpus_allowed_ptr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shuffle_array (int*,int) ; 
 int /*<<< orphan*/  stub1 () ; 
 TYPE_1__* test_case_array ; 
 int test_repeat_count ; 
 int /*<<< orphan*/  test_report_one_done () ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int test_func(void *private)
{
	struct test_driver *t = private;
	int random_array[ARRAY_SIZE(test_case_array)];
	int index, i, j;
	ktime_t kt;
	u64 delta;

	if (set_cpus_allowed_ptr(current, cpumask_of(t->cpu)) < 0)
		pr_err("Failed to set affinity to %d CPU\n", t->cpu);

	for (i = 0; i < ARRAY_SIZE(test_case_array); i++)
		random_array[i] = i;

	if (!sequential_test_order)
		shuffle_array(random_array, ARRAY_SIZE(test_case_array));

	/*
	 * Block until initialization is done.
	 */
	down_read(&prepare_for_test_rwsem);

	t->start = get_cycles();
	for (i = 0; i < ARRAY_SIZE(test_case_array); i++) {
		index = random_array[i];

		/*
		 * Skip tests if run_test_mask has been specified.
		 */
		if (!((run_test_mask & (1 << index)) >> index))
			continue;

		kt = ktime_get();
		for (j = 0; j < test_repeat_count; j++) {
			if (!test_case_array[index].test_func())
				per_cpu_test_data[t->cpu][index].test_passed++;
			else
				per_cpu_test_data[t->cpu][index].test_failed++;
		}

		/*
		 * Take an average time that test took.
		 */
		delta = (u64) ktime_us_delta(ktime_get(), kt);
		do_div(delta, (u32) test_repeat_count);

		per_cpu_test_data[t->cpu][index].time = delta;
	}
	t->stop = get_cycles();

	up_read(&prepare_for_test_rwsem);
	test_report_one_done();

	/*
	 * Wait for the kthread_stop() call.
	 */
	while (!kthread_should_stop())
		msleep(10);

	return 0;
}