#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  raw_lock; } ;
typedef  TYPE_1__ rwlock_t ;

/* Variables and functions */
 int /*<<< orphan*/  arch_write_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debug_write_unlock (TYPE_1__*) ; 

void do_raw_write_unlock(rwlock_t *lock)
{
	debug_write_unlock(lock);
	arch_write_unlock(&lock->raw_lock);
}