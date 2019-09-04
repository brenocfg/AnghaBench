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

/* Variables and functions */
 int ENOMEM ; 
 int GFP_KERNEL ; 
 int __GFP_HIGHMEM ; 
 struct page* alloc_page (int) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 

__attribute__((used)) static int
cifs_write_allocate_pages(struct page **pages, unsigned long num_pages)
{
	int rc = 0;
	unsigned long i;

	for (i = 0; i < num_pages; i++) {
		pages[i] = alloc_page(GFP_KERNEL|__GFP_HIGHMEM);
		if (!pages[i]) {
			/*
			 * save number of pages we have already allocated and
			 * return with ENOMEM error
			 */
			num_pages = i;
			rc = -ENOMEM;
			break;
		}
	}

	if (rc) {
		for (i = 0; i < num_pages; i++)
			put_page(pages[i]);
	}
	return rc;
}