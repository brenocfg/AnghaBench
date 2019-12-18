#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  ntfschar ;
typedef  int /*<<< orphan*/  ntfs_inode ;
struct TYPE_5__ {int /*<<< orphan*/ * ntfs_ino; int /*<<< orphan*/ * base_ntfs_ino; int /*<<< orphan*/  mrec; } ;
typedef  TYPE_1__ ntfs_attr_search_ctx ;
typedef  int /*<<< orphan*/  VCN ;
typedef  int /*<<< orphan*/  IGNORE_CASE_BOOL ;
typedef  scalar_t__ ATTR_TYPE ;

/* Variables and functions */
 scalar_t__ const AT_ATTRIBUTE_LIST ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NInoAttrList (int /*<<< orphan*/ *) ; 
 int ntfs_attr_find (scalar_t__ const,int /*<<< orphan*/  const*,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/  const*,int /*<<< orphan*/  const,TYPE_1__*) ; 
 int /*<<< orphan*/  ntfs_debug (char*) ; 
 int ntfs_external_attr_find (scalar_t__ const,int /*<<< orphan*/  const*,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/  const*,int /*<<< orphan*/  const,TYPE_1__*) ; 

int ntfs_attr_lookup(const ATTR_TYPE type, const ntfschar *name,
		const u32 name_len, const IGNORE_CASE_BOOL ic,
		const VCN lowest_vcn, const u8 *val, const u32 val_len,
		ntfs_attr_search_ctx *ctx)
{
	ntfs_inode *base_ni;

	ntfs_debug("Entering.");
	BUG_ON(IS_ERR(ctx->mrec));
	if (ctx->base_ntfs_ino)
		base_ni = ctx->base_ntfs_ino;
	else
		base_ni = ctx->ntfs_ino;
	/* Sanity check, just for debugging really. */
	BUG_ON(!base_ni);
	if (!NInoAttrList(base_ni) || type == AT_ATTRIBUTE_LIST)
		return ntfs_attr_find(type, name, name_len, ic, val, val_len,
				ctx);
	return ntfs_external_attr_find(type, name, name_len, ic, lowest_vcn,
			val, val_len, ctx);
}