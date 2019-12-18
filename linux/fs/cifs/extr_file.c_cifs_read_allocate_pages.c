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
struct page {int dummy; } ;
struct cifs_readdata {struct page** pages; } ;

/* Variables and functions */
 int ENOMEM ; 
 int GFP_KERNEL ; 
 int __GFP_HIGHMEM ; 
 struct page* alloc_page (int) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 

__attribute__((used)) static int
cifs_read_allocate_pages(struct cifs_readdata *rdata, unsigned int nr_pages)
{
	int rc = 0;
	struct page *page;
	unsigned int i;

	for (i = 0; i < nr_pages; i++) {
		page = alloc_page(GFP_KERNEL|__GFP_HIGHMEM);
		if (!page) {
			rc = -ENOMEM;
			break;
		}
		rdata->pages[i] = page;
	}

	if (rc) {
		unsigned int nr_page_failed = i;

		for (i = 0; i < nr_page_failed; i++) {
			put_page(rdata->pages[i]);
			rdata->pages[i] = NULL;
		}
	}
	return rc;
}