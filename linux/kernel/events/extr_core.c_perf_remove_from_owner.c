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
struct task_struct {int /*<<< orphan*/  perf_event_mutex; } ;
struct perf_event {int /*<<< orphan*/  owner; int /*<<< orphan*/  owner_entry; } ;

/* Variables and functions */
 struct task_struct* READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SINGLE_DEPTH_NESTING ; 
 int /*<<< orphan*/  get_task_struct (struct task_struct*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock_nested (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_task_struct (struct task_struct*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  smp_store_release (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void perf_remove_from_owner(struct perf_event *event)
{
	struct task_struct *owner;

	rcu_read_lock();
	/*
	 * Matches the smp_store_release() in perf_event_exit_task(). If we
	 * observe !owner it means the list deletion is complete and we can
	 * indeed free this event, otherwise we need to serialize on
	 * owner->perf_event_mutex.
	 */
	owner = READ_ONCE(event->owner);
	if (owner) {
		/*
		 * Since delayed_put_task_struct() also drops the last
		 * task reference we can safely take a new reference
		 * while holding the rcu_read_lock().
		 */
		get_task_struct(owner);
	}
	rcu_read_unlock();

	if (owner) {
		/*
		 * If we're here through perf_event_exit_task() we're already
		 * holding ctx->mutex which would be an inversion wrt. the
		 * normal lock order.
		 *
		 * However we can safely take this lock because its the child
		 * ctx->mutex.
		 */
		mutex_lock_nested(&owner->perf_event_mutex, SINGLE_DEPTH_NESTING);

		/*
		 * We have to re-check the event->owner field, if it is cleared
		 * we raced with perf_event_exit_task(), acquiring the mutex
		 * ensured they're done, and we can proceed with freeing the
		 * event.
		 */
		if (event->owner) {
			list_del_init(&event->owner_entry);
			smp_store_release(&event->owner, NULL);
		}
		mutex_unlock(&owner->perf_event_mutex);
		put_task_struct(owner);
	}
}