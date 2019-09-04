#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct page {int dummy; } ;
struct TYPE_4__ {struct page* page; scalar_t__ base_ni; scalar_t__ actx; scalar_t__ is_in_root; scalar_t__ entry; } ;
typedef  TYPE_1__ ntfs_index_context ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  PageLocked (struct page*) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  ntfs_attr_put_search_ctx (scalar_t__) ; 
 int /*<<< orphan*/  ntfs_index_ctx_cache ; 
 int /*<<< orphan*/  ntfs_unmap_page (struct page*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 
 int /*<<< orphan*/  unmap_mft_record (scalar_t__) ; 

void ntfs_index_ctx_put(ntfs_index_context *ictx)
{
	if (ictx->entry) {
		if (ictx->is_in_root) {
			if (ictx->actx)
				ntfs_attr_put_search_ctx(ictx->actx);
			if (ictx->base_ni)
				unmap_mft_record(ictx->base_ni);
		} else {
			struct page *page = ictx->page;
			if (page) {
				BUG_ON(!PageLocked(page));
				unlock_page(page);
				ntfs_unmap_page(page);
			}
		}
	}
	kmem_cache_free(ntfs_index_ctx_cache, ictx);
	return;
}