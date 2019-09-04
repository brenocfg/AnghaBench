#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct fault_attr {int probability; int interval; int count; int /*<<< orphan*/  times; int /*<<< orphan*/  space; scalar_t__ task_filter; } ;
typedef  int ssize_t ;
struct TYPE_3__ {int /*<<< orphan*/  fail_nth; } ;

/* Variables and functions */
 unsigned int READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  atomic_dec_not_zero (int /*<<< orphan*/ *) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_sub (int,int /*<<< orphan*/ *) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  fail_dump (struct fault_attr*) ; 
 int /*<<< orphan*/  fail_stacktrace (struct fault_attr*) ; 
 int /*<<< orphan*/  fail_task (struct fault_attr*,TYPE_1__*) ; 
 scalar_t__ in_task () ; 
 int prandom_u32 () ; 

bool should_fail(struct fault_attr *attr, ssize_t size)
{
	if (in_task()) {
		unsigned int fail_nth = READ_ONCE(current->fail_nth);

		if (fail_nth) {
			if (!WRITE_ONCE(current->fail_nth, fail_nth - 1))
				goto fail;

			return false;
		}
	}

	/* No need to check any other properties if the probability is 0 */
	if (attr->probability == 0)
		return false;

	if (attr->task_filter && !fail_task(attr, current))
		return false;

	if (atomic_read(&attr->times) == 0)
		return false;

	if (atomic_read(&attr->space) > size) {
		atomic_sub(size, &attr->space);
		return false;
	}

	if (attr->interval > 1) {
		attr->count++;
		if (attr->count % attr->interval)
			return false;
	}

	if (attr->probability <= prandom_u32() % 100)
		return false;

	if (!fail_stacktrace(attr))
		return false;

fail:
	fail_dump(attr);

	if (atomic_read(&attr->times) != -1)
		atomic_dec_not_zero(&attr->times);

	return true;
}