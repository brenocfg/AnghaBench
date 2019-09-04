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
struct ld_semaphore {int /*<<< orphan*/  read_wait; int /*<<< orphan*/  write_wait; } ;

/* Variables and functions */
 int /*<<< orphan*/  __ldsem_wake_readers (struct ld_semaphore*) ; 
 int /*<<< orphan*/  __ldsem_wake_writer (struct ld_semaphore*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __ldsem_wake(struct ld_semaphore *sem)
{
	if (!list_empty(&sem->write_wait))
		__ldsem_wake_writer(sem);
	else if (!list_empty(&sem->read_wait))
		__ldsem_wake_readers(sem);
}