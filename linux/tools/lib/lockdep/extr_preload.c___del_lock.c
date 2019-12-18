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
struct lock_lookup {int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_lock (struct lock_lookup*) ; 
 int /*<<< orphan*/  ll_pthread_rwlock_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ll_pthread_rwlock_wrlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  locks ; 
 int /*<<< orphan*/  locks_rwlock ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __del_lock(struct lock_lookup *lock)
{
	ll_pthread_rwlock_wrlock(&locks_rwlock);
	rb_erase(&lock->node, &locks);
	ll_pthread_rwlock_unlock(&locks_rwlock);
	free_lock(lock);
}