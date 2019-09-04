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
struct user_struct {unsigned long locked_shm; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_IPC_LOCK ; 
 size_t PAGE_SHIFT ; 
 size_t PAGE_SIZE ; 
 int /*<<< orphan*/  RLIMIT_MEMLOCK ; 
 unsigned long RLIM_INFINITY ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_uid (struct user_struct*) ; 
 unsigned long rlimit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shmlock_user_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int user_shm_lock(size_t size, struct user_struct *user)
{
	unsigned long lock_limit, locked;
	int allowed = 0;

	locked = (size + PAGE_SIZE - 1) >> PAGE_SHIFT;
	lock_limit = rlimit(RLIMIT_MEMLOCK);
	if (lock_limit == RLIM_INFINITY)
		allowed = 1;
	lock_limit >>= PAGE_SHIFT;
	spin_lock(&shmlock_user_lock);
	if (!allowed &&
	    locked + user->locked_shm > lock_limit && !capable(CAP_IPC_LOCK))
		goto out;
	get_uid(user);
	user->locked_shm += locked;
	allowed = 1;
out:
	spin_unlock(&shmlock_user_lock);
	return allowed;
}