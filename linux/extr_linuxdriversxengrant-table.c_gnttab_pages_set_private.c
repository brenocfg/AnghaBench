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
struct xen_page_foreign {int dummy; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SetPagePrivate (struct page*) ; 
 struct xen_page_foreign* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_page_private (struct page*,unsigned long) ; 

int gnttab_pages_set_private(int nr_pages, struct page **pages)
{
	int i;

	for (i = 0; i < nr_pages; i++) {
#if BITS_PER_LONG < 64
		struct xen_page_foreign *foreign;

		foreign = kzalloc(sizeof(*foreign), GFP_KERNEL);
		if (!foreign)
			return -ENOMEM;

		set_page_private(pages[i], (unsigned long)foreign);
#endif
		SetPagePrivate(pages[i]);
	}

	return 0;
}