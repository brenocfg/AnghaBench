#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_6__ {scalar_t__ base_ntfs_ino; int is_first; scalar_t__ ntfs_ino; int /*<<< orphan*/  base_mrec; int /*<<< orphan*/ * al_entry; TYPE_1__* mrec; int /*<<< orphan*/ * attr; } ;
typedef  TYPE_2__ ntfs_attr_search_ctx ;
struct TYPE_5__ {int /*<<< orphan*/  attrs_offset; } ;
typedef  int /*<<< orphan*/  ATTR_RECORD ;

/* Variables and functions */
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  ntfs_attr_init_search_ctx (TYPE_2__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unmap_extent_mft_record (scalar_t__) ; 

void ntfs_attr_reinit_search_ctx(ntfs_attr_search_ctx *ctx)
{
	if (likely(!ctx->base_ntfs_ino)) {
		/* No attribute list. */
		ctx->is_first = true;
		/* Sanity checks are performed elsewhere. */
		ctx->attr = (ATTR_RECORD*)((u8*)ctx->mrec +
				le16_to_cpu(ctx->mrec->attrs_offset));
		/*
		 * This needs resetting due to ntfs_external_attr_find() which
		 * can leave it set despite having zeroed ctx->base_ntfs_ino.
		 */
		ctx->al_entry = NULL;
		return;
	} /* Attribute list. */
	if (ctx->ntfs_ino != ctx->base_ntfs_ino)
		unmap_extent_mft_record(ctx->ntfs_ino);
	ntfs_attr_init_search_ctx(ctx, ctx->base_ntfs_ino, ctx->base_mrec);
	return;
}