#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct afs_addr_cursor {unsigned long tried; int index; int responded; TYPE_1__* alist; int /*<<< orphan*/  nr_iterations; } ;
struct TYPE_2__ {unsigned long responded; unsigned long failed; int /*<<< orphan*/  preferred; } ;

/* Variables and functions */
 int READ_ONCE (int /*<<< orphan*/ ) ; 
 int __ffs (unsigned long) ; 
 int /*<<< orphan*/  _enter (char*,unsigned long,unsigned long,unsigned long,int) ; 
 int /*<<< orphan*/  set_bit (int,unsigned long*) ; 
 scalar_t__ test_bit (int,unsigned long*) ; 

bool afs_iterate_addresses(struct afs_addr_cursor *ac)
{
	unsigned long set, failed;
	int index;

	if (!ac->alist)
		return false;

	set = ac->alist->responded;
	failed = ac->alist->failed;
	_enter("%lx-%lx-%lx,%d", set, failed, ac->tried, ac->index);

	ac->nr_iterations++;

	set &= ~(failed | ac->tried);

	if (!set)
		return false;

	index = READ_ONCE(ac->alist->preferred);
	if (test_bit(index, &set))
		goto selected;

	index = __ffs(set);

selected:
	ac->index = index;
	set_bit(index, &ac->tried);
	ac->responded = false;
	return true;
}