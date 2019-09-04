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
struct cmp_pages {int num_pages; struct page** dst_pages; struct page** src_pages; } ;

/* Variables and functions */
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

__attribute__((used)) static void btrfs_cmp_data_free(struct cmp_pages *cmp)
{
	int i;
	struct page *pg;

	for (i = 0; i < cmp->num_pages; i++) {
		pg = cmp->src_pages[i];
		if (pg) {
			unlock_page(pg);
			put_page(pg);
			cmp->src_pages[i] = NULL;
		}
		pg = cmp->dst_pages[i];
		if (pg) {
			unlock_page(pg);
			put_page(pg);
			cmp->dst_pages[i] = NULL;
		}
	}
}