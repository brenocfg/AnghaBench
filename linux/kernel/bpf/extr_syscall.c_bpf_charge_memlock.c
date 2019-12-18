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
typedef  int /*<<< orphan*/  u32 ;
struct user_struct {int /*<<< orphan*/  locked_vm; } ;

/* Variables and functions */
 int EPERM ; 
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  RLIMIT_MEMLOCK ; 
 unsigned long atomic_long_add_return (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_long_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 unsigned long rlimit (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bpf_charge_memlock(struct user_struct *user, u32 pages)
{
	unsigned long memlock_limit = rlimit(RLIMIT_MEMLOCK) >> PAGE_SHIFT;

	if (atomic_long_add_return(pages, &user->locked_vm) > memlock_limit) {
		atomic_long_sub(pages, &user->locked_vm);
		return -EPERM;
	}
	return 0;
}