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
struct shrinker {int dummy; } ;
struct shrink_control {int dummy; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 unsigned long HPAGE_PMD_NR ; 
 int /*<<< orphan*/  __free_pages (struct page*,int /*<<< orphan*/ ) ; 
 int atomic_cmpxchg (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  compound_order (struct page*) ; 
 int /*<<< orphan*/  huge_zero_page ; 
 int /*<<< orphan*/  huge_zero_refcount ; 
 struct page* xchg (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned long shrink_huge_zero_page_scan(struct shrinker *shrink,
				       struct shrink_control *sc)
{
	if (atomic_cmpxchg(&huge_zero_refcount, 1, 0) == 1) {
		struct page *zero_page = xchg(&huge_zero_page, NULL);
		BUG_ON(zero_page == NULL);
		__free_pages(zero_page, compound_order(zero_page));
		return HPAGE_PMD_NR;
	}

	return 0;
}