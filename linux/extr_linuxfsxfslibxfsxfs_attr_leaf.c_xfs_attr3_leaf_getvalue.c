#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct xfs_da_args {int index; size_t namelen; int flags; int valuelen; int rmtvaluelen; TYPE_1__* dp; int /*<<< orphan*/  rmtblkcnt; void* rmtblkno; int /*<<< orphan*/  name; int /*<<< orphan*/  value; TYPE_2__* geo; } ;
struct xfs_buf {struct xfs_attr_leafblock* b_addr; } ;
struct xfs_attr_leafblock {int dummy; } ;
struct xfs_attr_leaf_name_remote {size_t namelen; int /*<<< orphan*/  valueblk; int /*<<< orphan*/  valuelen; int /*<<< orphan*/ * name; } ;
struct xfs_attr_leaf_name_local {size_t namelen; int /*<<< orphan*/ * nameval; int /*<<< orphan*/  valuelen; } ;
struct xfs_attr_leaf_entry {int flags; } ;
struct xfs_attr3_icleaf_hdr {int count; } ;
struct TYPE_4__ {int blksize; } ;
struct TYPE_3__ {int /*<<< orphan*/  i_mount; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int ATTR_KERNOVAL ; 
 int ERANGE ; 
 int XFS_ATTR_LOCAL ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 void* be32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 struct xfs_attr_leaf_entry* xfs_attr3_leaf_entryp (struct xfs_attr_leafblock*) ; 
 int /*<<< orphan*/  xfs_attr3_leaf_hdr_from_disk (TYPE_2__*,struct xfs_attr3_icleaf_hdr*,struct xfs_attr_leafblock*) ; 
 struct xfs_attr_leaf_name_local* xfs_attr3_leaf_name_local (struct xfs_attr_leafblock*,size_t) ; 
 struct xfs_attr_leaf_name_remote* xfs_attr3_leaf_name_remote (struct xfs_attr_leafblock*,size_t) ; 
 int /*<<< orphan*/  xfs_attr3_rmt_blocks (int /*<<< orphan*/ ,int) ; 

int
xfs_attr3_leaf_getvalue(
	struct xfs_buf		*bp,
	struct xfs_da_args	*args)
{
	struct xfs_attr_leafblock *leaf;
	struct xfs_attr3_icleaf_hdr ichdr;
	struct xfs_attr_leaf_entry *entry;
	struct xfs_attr_leaf_name_local *name_loc;
	struct xfs_attr_leaf_name_remote *name_rmt;
	int			valuelen;

	leaf = bp->b_addr;
	xfs_attr3_leaf_hdr_from_disk(args->geo, &ichdr, leaf);
	ASSERT(ichdr.count < args->geo->blksize / 8);
	ASSERT(args->index < ichdr.count);

	entry = &xfs_attr3_leaf_entryp(leaf)[args->index];
	if (entry->flags & XFS_ATTR_LOCAL) {
		name_loc = xfs_attr3_leaf_name_local(leaf, args->index);
		ASSERT(name_loc->namelen == args->namelen);
		ASSERT(memcmp(args->name, name_loc->nameval, args->namelen) == 0);
		valuelen = be16_to_cpu(name_loc->valuelen);
		if (args->flags & ATTR_KERNOVAL) {
			args->valuelen = valuelen;
			return 0;
		}
		if (args->valuelen < valuelen) {
			args->valuelen = valuelen;
			return -ERANGE;
		}
		args->valuelen = valuelen;
		memcpy(args->value, &name_loc->nameval[args->namelen], valuelen);
	} else {
		name_rmt = xfs_attr3_leaf_name_remote(leaf, args->index);
		ASSERT(name_rmt->namelen == args->namelen);
		ASSERT(memcmp(args->name, name_rmt->name, args->namelen) == 0);
		args->rmtvaluelen = be32_to_cpu(name_rmt->valuelen);
		args->rmtblkno = be32_to_cpu(name_rmt->valueblk);
		args->rmtblkcnt = xfs_attr3_rmt_blocks(args->dp->i_mount,
						       args->rmtvaluelen);
		if (args->flags & ATTR_KERNOVAL) {
			args->valuelen = args->rmtvaluelen;
			return 0;
		}
		if (args->valuelen < args->rmtvaluelen) {
			args->valuelen = args->rmtvaluelen;
			return -ERANGE;
		}
		args->valuelen = args->rmtvaluelen;
	}
	return 0;
}