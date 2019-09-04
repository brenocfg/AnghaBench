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
typedef  int /*<<< orphan*/  unwind_entry_cb_t ;
struct unwind_info {int /*<<< orphan*/  machine; struct thread* thread; struct perf_sample* sample; } ;
struct thread {TYPE_1__* mg; } ;
struct TYPE_4__ {int /*<<< orphan*/  regs; } ;
struct perf_sample {TYPE_2__ user_regs; } ;
struct TYPE_3__ {int /*<<< orphan*/  machine; } ;

/* Variables and functions */
 int EINVAL ; 
 int get_entries (struct unwind_info*,int /*<<< orphan*/ ,void*,int) ; 

__attribute__((used)) static int _unwind__get_entries(unwind_entry_cb_t cb, void *arg,
			struct thread *thread,
			struct perf_sample *data, int max_stack)
{
	struct unwind_info ui = {
		.sample       = data,
		.thread       = thread,
		.machine      = thread->mg->machine,
	};

	if (!data->user_regs.regs)
		return -EINVAL;

	if (max_stack <= 0)
		return -EINVAL;

	return get_entries(&ui, cb, arg, max_stack);
}