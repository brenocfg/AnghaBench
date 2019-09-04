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
struct pagevec {int dummy; } ;
struct page {int dummy; } ;

/* Variables and functions */
 scalar_t__ pagevec_add (struct pagevec*,struct page*) ; 
 int /*<<< orphan*/  pagevec_init (struct pagevec*) ; 
 int /*<<< orphan*/  pagevec_release (struct pagevec*) ; 

__attribute__((used)) static void ceph_release_pages(struct page **pages, int num)
{
	struct pagevec pvec;
	int i;

	pagevec_init(&pvec);
	for (i = 0; i < num; i++) {
		if (pagevec_add(&pvec, pages[i]) == 0)
			pagevec_release(&pvec);
	}
	pagevec_release(&pvec);
}