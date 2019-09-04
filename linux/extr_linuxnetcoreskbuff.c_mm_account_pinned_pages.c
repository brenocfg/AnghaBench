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
struct user_struct {int /*<<< orphan*/  locked_vm; } ;
struct mmpin {unsigned long num_pg; int /*<<< orphan*/  user; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_IPC_LOCK ; 
 int ENOBUFS ; 
 size_t PAGE_SHIFT ; 
 int /*<<< orphan*/  RLIMIT_MEMLOCK ; 
 unsigned long atomic_long_cmpxchg (int /*<<< orphan*/ *,unsigned long,unsigned long) ; 
 unsigned long atomic_long_read (int /*<<< orphan*/ *) ; 
 scalar_t__ capable (int /*<<< orphan*/ ) ; 
 struct user_struct* current_user () ; 
 int /*<<< orphan*/  get_uid (struct user_struct*) ; 
 size_t rlimit (int /*<<< orphan*/ ) ; 

int mm_account_pinned_pages(struct mmpin *mmp, size_t size)
{
	unsigned long max_pg, num_pg, new_pg, old_pg;
	struct user_struct *user;

	if (capable(CAP_IPC_LOCK) || !size)
		return 0;

	num_pg = (size >> PAGE_SHIFT) + 2;	/* worst case */
	max_pg = rlimit(RLIMIT_MEMLOCK) >> PAGE_SHIFT;
	user = mmp->user ? : current_user();

	do {
		old_pg = atomic_long_read(&user->locked_vm);
		new_pg = old_pg + num_pg;
		if (new_pg > max_pg)
			return -ENOBUFS;
	} while (atomic_long_cmpxchg(&user->locked_vm, old_pg, new_pg) !=
		 old_pg);

	if (!mmp->user) {
		mmp->user = get_uid(user);
		mmp->num_pg = num_pg;
	} else {
		mmp->num_pg += num_pg;
	}

	return 0;
}