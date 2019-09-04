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
struct page {unsigned long flags; scalar_t__ mapping; int /*<<< orphan*/  _mapcount; } ;

/* Variables and functions */
 int atomic_read (int /*<<< orphan*/ *) ; 
 unsigned long page_ref_count (struct page*) ; 
 scalar_t__ unlikely (unsigned long) ; 

__attribute__((used)) static inline bool page_expected_state(struct page *page,
					unsigned long check_flags)
{
	if (unlikely(atomic_read(&page->_mapcount) != -1))
		return false;

	if (unlikely((unsigned long)page->mapping |
			page_ref_count(page) |
#ifdef CONFIG_MEMCG
			(unsigned long)page->mem_cgroup |
#endif
			(page->flags & check_flags)))
		return false;

	return true;
}