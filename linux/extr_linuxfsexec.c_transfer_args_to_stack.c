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
struct linux_binprm {unsigned long p; int /*<<< orphan*/ * page; } ;

/* Variables and functions */
 int EFAULT ; 
 int MAX_ARG_PAGES ; 
 unsigned int PAGE_MASK ; 
 unsigned long PAGE_SHIFT ; 
 unsigned int PAGE_SIZE ; 
 scalar_t__ copy_to_user (void*,char*,unsigned int) ; 
 char* kmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kunmap (int /*<<< orphan*/ ) ; 

int transfer_args_to_stack(struct linux_binprm *bprm,
			   unsigned long *sp_location)
{
	unsigned long index, stop, sp;
	int ret = 0;

	stop = bprm->p >> PAGE_SHIFT;
	sp = *sp_location;

	for (index = MAX_ARG_PAGES - 1; index >= stop; index--) {
		unsigned int offset = index == stop ? bprm->p & ~PAGE_MASK : 0;
		char *src = kmap(bprm->page[index]) + offset;
		sp -= PAGE_SIZE - offset;
		if (copy_to_user((void *) sp, src, PAGE_SIZE - offset) != 0)
			ret = -EFAULT;
		kunmap(bprm->page[index]);
		if (ret)
			goto out;
	}

	*sp_location = sp;

out:
	return ret;
}