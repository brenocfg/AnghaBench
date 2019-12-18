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
struct user_struct {size_t locked_shm; } ;

/* Variables and functions */
 size_t PAGE_SHIFT ; 
 size_t PAGE_SIZE ; 
 int /*<<< orphan*/  free_uid (struct user_struct*) ; 
 int /*<<< orphan*/  shmlock_user_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void user_shm_unlock(size_t size, struct user_struct *user)
{
	spin_lock(&shmlock_user_lock);
	user->locked_shm -= (size + PAGE_SIZE - 1) >> PAGE_SHIFT;
	spin_unlock(&shmlock_user_lock);
	free_uid(user);
}