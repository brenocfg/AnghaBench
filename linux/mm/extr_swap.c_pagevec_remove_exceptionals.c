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
struct pagevec {int nr; struct page** pages; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int pagevec_count (struct pagevec*) ; 
 int /*<<< orphan*/  xa_is_value (struct page*) ; 

void pagevec_remove_exceptionals(struct pagevec *pvec)
{
	int i, j;

	for (i = 0, j = 0; i < pagevec_count(pvec); i++) {
		struct page *page = pvec->pages[i];
		if (!xa_is_value(page))
			pvec->pages[j++] = page;
	}
	pvec->nr = j;
}