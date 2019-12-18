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

/* Variables and functions */
 unsigned long __frontswap_curr_pages () ; 
 int __frontswap_unuse_pages (unsigned long,unsigned long*,int*) ; 
 int /*<<< orphan*/  assert_spin_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  swap_lock ; 

__attribute__((used)) static int __frontswap_shrink(unsigned long target_pages,
				unsigned long *pages_to_unuse,
				int *type)
{
	unsigned long total_pages = 0, total_pages_to_unuse;

	assert_spin_locked(&swap_lock);

	total_pages = __frontswap_curr_pages();
	if (total_pages <= target_pages) {
		/* Nothing to do */
		*pages_to_unuse = 0;
		return 1;
	}
	total_pages_to_unuse = total_pages - target_pages;
	return __frontswap_unuse_pages(total_pages_to_unuse, pages_to_unuse, type);
}