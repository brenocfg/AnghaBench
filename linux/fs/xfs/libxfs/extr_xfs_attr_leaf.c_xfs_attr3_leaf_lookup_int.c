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
typedef  scalar_t__ xfs_dahash_t ;
struct xfs_da_args {scalar_t__ hashval; int index; int flags; scalar_t__ namelen; scalar_t__ rmtvaluelen; TYPE_1__* dp; int /*<<< orphan*/  rmtblkcnt; scalar_t__ rmtblkno; int /*<<< orphan*/  name; TYPE_2__* geo; } ;
struct xfs_buf {struct xfs_attr_leafblock* b_addr; } ;
struct xfs_attr_leafblock {int dummy; } ;
struct xfs_attr_leaf_name_remote {scalar_t__ namelen; int /*<<< orphan*/  valueblk; int /*<<< orphan*/  valuelen; int /*<<< orphan*/  name; } ;
struct xfs_attr_leaf_name_local {scalar_t__ namelen; int /*<<< orphan*/  nameval; } ;
struct xfs_attr_leaf_entry {int flags; int /*<<< orphan*/  hashval; } ;
struct xfs_attr3_icleaf_hdr {int count; } ;
struct TYPE_4__ {int blksize; } ;
struct TYPE_3__ {int /*<<< orphan*/  i_mount; } ;

/* Variables and functions */
 int EEXIST ; 
 int EFSCORRUPTED ; 
 int ENOATTR ; 
 int XFS_ATTR_INCOMPLETE ; 
 int XFS_ATTR_LOCAL ; 
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  trace_xfs_attr_leaf_lookup (struct xfs_da_args*) ; 
 struct xfs_attr_leaf_entry* xfs_attr3_leaf_entryp (struct xfs_attr_leafblock*) ; 
 int /*<<< orphan*/  xfs_attr3_leaf_hdr_from_disk (TYPE_2__*,struct xfs_attr3_icleaf_hdr*,struct xfs_attr_leafblock*) ; 
 struct xfs_attr_leaf_name_local* xfs_attr3_leaf_name_local (struct xfs_attr_leafblock*,int) ; 
 struct xfs_attr_leaf_name_remote* xfs_attr3_leaf_name_remote (struct xfs_attr_leafblock*,int) ; 
 int /*<<< orphan*/  xfs_attr3_rmt_blocks (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  xfs_attr_namesp_match (int,int) ; 

int
xfs_attr3_leaf_lookup_int(
	struct xfs_buf		*bp,
	struct xfs_da_args	*args)
{
	struct xfs_attr_leafblock *leaf;
	struct xfs_attr3_icleaf_hdr ichdr;
	struct xfs_attr_leaf_entry *entry;
	struct xfs_attr_leaf_entry *entries;
	struct xfs_attr_leaf_name_local *name_loc;
	struct xfs_attr_leaf_name_remote *name_rmt;
	xfs_dahash_t		hashval;
	int			probe;
	int			span;

	trace_xfs_attr_leaf_lookup(args);

	leaf = bp->b_addr;
	xfs_attr3_leaf_hdr_from_disk(args->geo, &ichdr, leaf);
	entries = xfs_attr3_leaf_entryp(leaf);
	if (ichdr.count >= args->geo->blksize / 8)
		return -EFSCORRUPTED;

	/*
	 * Binary search.  (note: small blocks will skip this loop)
	 */
	hashval = args->hashval;
	probe = span = ichdr.count / 2;
	for (entry = &entries[probe]; span > 4; entry = &entries[probe]) {
		span /= 2;
		if (be32_to_cpu(entry->hashval) < hashval)
			probe += span;
		else if (be32_to_cpu(entry->hashval) > hashval)
			probe -= span;
		else
			break;
	}
	if (!(probe >= 0 && (!ichdr.count || probe < ichdr.count)))
		return -EFSCORRUPTED;
	if (!(span <= 4 || be32_to_cpu(entry->hashval) == hashval))
		return -EFSCORRUPTED;

	/*
	 * Since we may have duplicate hashval's, find the first matching
	 * hashval in the leaf.
	 */
	while (probe > 0 && be32_to_cpu(entry->hashval) >= hashval) {
		entry--;
		probe--;
	}
	while (probe < ichdr.count &&
	       be32_to_cpu(entry->hashval) < hashval) {
		entry++;
		probe++;
	}
	if (probe == ichdr.count || be32_to_cpu(entry->hashval) != hashval) {
		args->index = probe;
		return -ENOATTR;
	}

	/*
	 * Duplicate keys may be present, so search all of them for a match.
	 */
	for (; probe < ichdr.count && (be32_to_cpu(entry->hashval) == hashval);
			entry++, probe++) {
/*
 * GROT: Add code to remove incomplete entries.
 */
		/*
		 * If we are looking for INCOMPLETE entries, show only those.
		 * If we are looking for complete entries, show only those.
		 */
		if ((args->flags & XFS_ATTR_INCOMPLETE) !=
		    (entry->flags & XFS_ATTR_INCOMPLETE)) {
			continue;
		}
		if (entry->flags & XFS_ATTR_LOCAL) {
			name_loc = xfs_attr3_leaf_name_local(leaf, probe);
			if (name_loc->namelen != args->namelen)
				continue;
			if (memcmp(args->name, name_loc->nameval,
							args->namelen) != 0)
				continue;
			if (!xfs_attr_namesp_match(args->flags, entry->flags))
				continue;
			args->index = probe;
			return -EEXIST;
		} else {
			name_rmt = xfs_attr3_leaf_name_remote(leaf, probe);
			if (name_rmt->namelen != args->namelen)
				continue;
			if (memcmp(args->name, name_rmt->name,
							args->namelen) != 0)
				continue;
			if (!xfs_attr_namesp_match(args->flags, entry->flags))
				continue;
			args->index = probe;
			args->rmtvaluelen = be32_to_cpu(name_rmt->valuelen);
			args->rmtblkno = be32_to_cpu(name_rmt->valueblk);
			args->rmtblkcnt = xfs_attr3_rmt_blocks(
							args->dp->i_mount,
							args->rmtvaluelen);
			return -EEXIST;
		}
	}
	args->index = probe;
	return -ENOATTR;
}