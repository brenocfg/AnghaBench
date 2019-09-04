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
struct hstate {unsigned long long max_huge_pages; } ;
typedef  enum hugetlbfs_size_type { ____Placeholder_hugetlbfs_size_type } hugetlbfs_size_type ;

/* Variables and functions */
 int NO_SIZE ; 
 int SIZE_PERCENT ; 
 int /*<<< orphan*/  do_div (unsigned long long,int) ; 
 unsigned long long huge_page_shift (struct hstate*) ; 

__attribute__((used)) static long
hugetlbfs_size_to_hpages(struct hstate *h, unsigned long long size_opt,
			 enum hugetlbfs_size_type val_type)
{
	if (val_type == NO_SIZE)
		return -1;

	if (val_type == SIZE_PERCENT) {
		size_opt <<= huge_page_shift(h);
		size_opt *= h->max_huge_pages;
		do_div(size_opt, 100);
	}

	size_opt >>= huge_page_shift(h);
	return size_opt;
}