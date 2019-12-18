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
struct TYPE_4__ {scalar_t__ base_ntfs_ino; scalar_t__ ntfs_ino; } ;
typedef  TYPE_1__ ntfs_attr_search_ctx ;

/* Variables and functions */
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  ntfs_attr_ctx_cache ; 
 int /*<<< orphan*/  unmap_extent_mft_record (scalar_t__) ; 

void ntfs_attr_put_search_ctx(ntfs_attr_search_ctx *ctx)
{
	if (ctx->base_ntfs_ino && ctx->ntfs_ino != ctx->base_ntfs_ino)
		unmap_extent_mft_record(ctx->ntfs_ino);
	kmem_cache_free(ntfs_attr_ctx_cache, ctx);
	return;
}