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
typedef  unsigned long u32 ;
struct user_struct {int /*<<< orphan*/  locked_vm; } ;

/* Variables and functions */
 int EPERM ; 
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  RLIMIT_MEMLOCK ; 
 unsigned long atomic_long_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_uid (struct user_struct*) ; 
 struct user_struct* get_current_user () ; 
 unsigned long rlimit (int /*<<< orphan*/ ) ; 

int bpf_map_precharge_memlock(u32 pages)
{
	struct user_struct *user = get_current_user();
	unsigned long memlock_limit, cur;

	memlock_limit = rlimit(RLIMIT_MEMLOCK) >> PAGE_SHIFT;
	cur = atomic_long_read(&user->locked_vm);
	free_uid(user);
	if (cur + pages > memlock_limit)
		return -EPERM;
	return 0;
}