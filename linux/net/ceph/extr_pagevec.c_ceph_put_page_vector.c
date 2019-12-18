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
 int /*<<< orphan*/  kvfree (struct page**) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  set_page_dirty_lock (struct page*) ; 

void ceph_put_page_vector(struct page **pages, int num_pages, bool dirty)
{
	int i;

	for (i = 0; i < num_pages; i++) {
		if (dirty)
			set_page_dirty_lock(pages[i]);
		put_page(pages[i]);
	}
	kvfree(pages);
}