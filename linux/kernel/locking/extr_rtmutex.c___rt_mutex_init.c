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
struct rt_mutex {int /*<<< orphan*/  waiters; int /*<<< orphan*/  wait_lock; int /*<<< orphan*/ * owner; } ;
struct lock_class_key {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RB_ROOT_CACHED ; 
 int /*<<< orphan*/  debug_rt_mutex_init (struct rt_mutex*,char const*,struct lock_class_key*) ; 
 int /*<<< orphan*/  raw_spin_lock_init (int /*<<< orphan*/ *) ; 

void __rt_mutex_init(struct rt_mutex *lock, const char *name,
		     struct lock_class_key *key)
{
	lock->owner = NULL;
	raw_spin_lock_init(&lock->wait_lock);
	lock->waiters = RB_ROOT_CACHED;

	if (name && key)
		debug_rt_mutex_init(lock, name, key);
}