#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct task_struct {struct held_lock* held_locks; } ;
struct held_lock {int /*<<< orphan*/  pin_count; int /*<<< orphan*/  references; int /*<<< orphan*/  acquire_ip; int /*<<< orphan*/  nest_lock; int /*<<< orphan*/  hardirqs_off; int /*<<< orphan*/  check; int /*<<< orphan*/  read; int /*<<< orphan*/  trylock; int /*<<< orphan*/  instance; } ;
struct TYPE_2__ {int /*<<< orphan*/  subclass; } ;

/* Variables and functions */
 scalar_t__ DEBUG_LOCKS_WARN_ON (int) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int __lock_acquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* hlock_class (struct held_lock*) ; 
 int /*<<< orphan*/  irqs_disabled () ; 

__attribute__((used)) static int reacquire_held_locks(struct task_struct *curr, unsigned int depth,
				int idx, unsigned int *merged)
{
	struct held_lock *hlock;
	int first_idx = idx;

	if (DEBUG_LOCKS_WARN_ON(!irqs_disabled()))
		return 0;

	for (hlock = curr->held_locks + idx; idx < depth; idx++, hlock++) {
		switch (__lock_acquire(hlock->instance,
				    hlock_class(hlock)->subclass,
				    hlock->trylock,
				    hlock->read, hlock->check,
				    hlock->hardirqs_off,
				    hlock->nest_lock, hlock->acquire_ip,
				    hlock->references, hlock->pin_count)) {
		case 0:
			return 1;
		case 1:
			break;
		case 2:
			*merged += (idx == first_idx);
			break;
		default:
			WARN_ON(1);
			return 0;
		}
	}
	return 0;
}