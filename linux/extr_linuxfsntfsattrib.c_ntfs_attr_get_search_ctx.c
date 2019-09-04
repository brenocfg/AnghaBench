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
typedef  int /*<<< orphan*/  ntfs_inode ;
typedef  int /*<<< orphan*/  ntfs_attr_search_ctx ;
typedef  int /*<<< orphan*/  MFT_RECORD ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/ * kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntfs_attr_ctx_cache ; 
 int /*<<< orphan*/  ntfs_attr_init_search_ctx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

ntfs_attr_search_ctx *ntfs_attr_get_search_ctx(ntfs_inode *ni, MFT_RECORD *mrec)
{
	ntfs_attr_search_ctx *ctx;

	ctx = kmem_cache_alloc(ntfs_attr_ctx_cache, GFP_NOFS);
	if (ctx)
		ntfs_attr_init_search_ctx(ctx, ni, mrec);
	return ctx;
}