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
struct z_erofs_pcluster {int /*<<< orphan*/  obj; struct page** compressed_pages; int /*<<< orphan*/  clusterbits; } ;
struct page {int dummy; } ;
struct address_space {int dummy; } ;

/* Variables and functions */
 unsigned int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ClearPagePrivate (struct page*) ; 
 int /*<<< orphan*/  WRITE_ONCE (struct page*,int /*<<< orphan*/ *) ; 
 scalar_t__ erofs_workgroup_try_to_freeze (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  erofs_workgroup_unfreeze (int /*<<< orphan*/ *,int) ; 
 scalar_t__ page_private (struct page*) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 

int erofs_try_to_free_cached_page(struct address_space *mapping,
				  struct page *page)
{
	struct z_erofs_pcluster *const pcl = (void *)page_private(page);
	const unsigned int clusterpages = BIT(pcl->clusterbits);
	int ret = 0;	/* 0 - busy */

	if (erofs_workgroup_try_to_freeze(&pcl->obj, 1)) {
		unsigned int i;

		for (i = 0; i < clusterpages; ++i) {
			if (pcl->compressed_pages[i] == page) {
				WRITE_ONCE(pcl->compressed_pages[i], NULL);
				ret = 1;
				break;
			}
		}
		erofs_workgroup_unfreeze(&pcl->obj, 1);

		if (ret) {
			ClearPagePrivate(page);
			put_page(page);
		}
	}
	return ret;
}