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
struct mm_walk {unsigned char* private; } ;
typedef  int /*<<< orphan*/  pte_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  huge_pte_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  huge_ptep_get (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mincore_hugetlb(pte_t *pte, unsigned long hmask, unsigned long addr,
			unsigned long end, struct mm_walk *walk)
{
#ifdef CONFIG_HUGETLB_PAGE
	unsigned char present;
	unsigned char *vec = walk->private;

	/*
	 * Hugepages under user process are always in RAM and never
	 * swapped out, but theoretically it needs to be checked.
	 */
	present = pte && !huge_pte_none(huge_ptep_get(pte));
	for (; addr != end; vec++, addr += PAGE_SIZE)
		*vec = present;
	walk->private = vec;
#else
	BUG();
#endif
	return 0;
}