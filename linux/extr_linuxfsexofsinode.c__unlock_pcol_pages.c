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
struct page_collect {int nr_pages; struct page** pages; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int READ ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 
 int /*<<< orphan*/  update_read_page (struct page*,int) ; 
 int /*<<< orphan*/  update_write_page (struct page*,int) ; 

__attribute__((used)) static void _unlock_pcol_pages(struct page_collect *pcol, int ret, int rw)
{
	int i;

	for (i = 0; i < pcol->nr_pages; i++) {
		struct page *page = pcol->pages[i];

		if (rw == READ)
			update_read_page(page, ret);
		else
			update_write_page(page, ret);

		unlock_page(page);
	}
}