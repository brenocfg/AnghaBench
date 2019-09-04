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
struct TYPE_4__ {scalar_t__ magic; int /*<<< orphan*/  raw_lock; } ;
typedef  TYPE_1__ rwlock_t ;

/* Variables and functions */
 int /*<<< orphan*/  RWLOCK_BUG_ON (int,TYPE_1__*,char*) ; 
 scalar_t__ RWLOCK_MAGIC ; 
 int /*<<< orphan*/  arch_read_lock (int /*<<< orphan*/ *) ; 

void do_raw_read_lock(rwlock_t *lock)
{
	RWLOCK_BUG_ON(lock->magic != RWLOCK_MAGIC, lock, "bad magic");
	arch_read_lock(&lock->raw_lock);
}