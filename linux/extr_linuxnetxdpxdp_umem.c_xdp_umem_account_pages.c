#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct xdp_umem {unsigned long npgs; TYPE_1__* user; } ;
struct TYPE_3__ {int /*<<< orphan*/  locked_vm; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_IPC_LOCK ; 
 int ENOBUFS ; 
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  RLIMIT_MEMLOCK ; 
 unsigned long atomic_long_cmpxchg (int /*<<< orphan*/ *,unsigned long,unsigned long) ; 
 unsigned long atomic_long_read (int /*<<< orphan*/ *) ; 
 scalar_t__ capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_user () ; 
 int /*<<< orphan*/  free_uid (TYPE_1__*) ; 
 TYPE_1__* get_uid (int /*<<< orphan*/ ) ; 
 unsigned long rlimit (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xdp_umem_account_pages(struct xdp_umem *umem)
{
	unsigned long lock_limit, new_npgs, old_npgs;

	if (capable(CAP_IPC_LOCK))
		return 0;

	lock_limit = rlimit(RLIMIT_MEMLOCK) >> PAGE_SHIFT;
	umem->user = get_uid(current_user());

	do {
		old_npgs = atomic_long_read(&umem->user->locked_vm);
		new_npgs = old_npgs + umem->npgs;
		if (new_npgs > lock_limit) {
			free_uid(umem->user);
			umem->user = NULL;
			return -ENOBUFS;
		}
	} while (atomic_long_cmpxchg(&umem->user->locked_vm, old_npgs,
				     new_npgs) != old_npgs);
	return 0;
}