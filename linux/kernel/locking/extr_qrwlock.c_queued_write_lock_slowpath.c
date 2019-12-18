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
struct qrwlock {int /*<<< orphan*/  wait_lock; int /*<<< orphan*/  cnts; } ;

/* Variables and functions */
 scalar_t__ VAL ; 
 int /*<<< orphan*/  _QW_LOCKED ; 
 scalar_t__ _QW_WAITING ; 
 int /*<<< orphan*/  arch_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  arch_spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_add (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_cmpxchg_acquire (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ atomic_cmpxchg_relaxed (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_cond_read_acquire (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 

void queued_write_lock_slowpath(struct qrwlock *lock)
{
	/* Put the writer into the wait queue */
	arch_spin_lock(&lock->wait_lock);

	/* Try to acquire the lock directly if no reader is present */
	if (!atomic_read(&lock->cnts) &&
	    (atomic_cmpxchg_acquire(&lock->cnts, 0, _QW_LOCKED) == 0))
		goto unlock;

	/* Set the waiting flag to notify readers that a writer is pending */
	atomic_add(_QW_WAITING, &lock->cnts);

	/* When no more readers or writers, set the locked flag */
	do {
		atomic_cond_read_acquire(&lock->cnts, VAL == _QW_WAITING);
	} while (atomic_cmpxchg_relaxed(&lock->cnts, _QW_WAITING,
					_QW_LOCKED) != _QW_WAITING);
unlock:
	arch_spin_unlock(&lock->wait_lock);
}