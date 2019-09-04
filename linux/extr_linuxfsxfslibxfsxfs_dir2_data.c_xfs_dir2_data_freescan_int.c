#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  length; int /*<<< orphan*/  freetag; } ;
typedef  TYPE_1__ xfs_dir2_data_unused_t ;
struct TYPE_7__ {int /*<<< orphan*/  namelen; } ;
typedef  TYPE_2__ xfs_dir2_data_entry_t ;
struct xfs_dir_ops {int /*<<< orphan*/  (* data_entsize ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/ * (* data_entry_tag_p ) (TYPE_2__*) ;scalar_t__ (* data_entry_p ) (struct xfs_dir2_data_hdr*) ;struct xfs_dir2_data_free* (* data_bestfree_p ) (struct xfs_dir2_data_hdr*) ;} ;
struct xfs_dir2_data_hdr {scalar_t__ magic; } ;
struct xfs_dir2_data_free {int dummy; } ;
struct xfs_da_geometry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  XFS_DIR2_BLOCK_MAGIC ; 
 int XFS_DIR2_DATA_FD_COUNT ; 
 int XFS_DIR2_DATA_FREE_TAG ; 
 int /*<<< orphan*/  XFS_DIR2_DATA_MAGIC ; 
 int /*<<< orphan*/  XFS_DIR3_BLOCK_MAGIC ; 
 int /*<<< orphan*/  XFS_DIR3_DATA_MAGIC ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct xfs_dir2_data_free*,int /*<<< orphan*/ ,int) ; 
 struct xfs_dir2_data_free* stub1 (struct xfs_dir2_data_hdr*) ; 
 scalar_t__ stub2 (struct xfs_dir2_data_hdr*) ; 
 int /*<<< orphan*/ * stub3 (TYPE_2__*) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_dir2_data_freeinsert (struct xfs_dir2_data_hdr*,struct xfs_dir2_data_free*,TYPE_1__*,int*) ; 
 int /*<<< orphan*/ * xfs_dir2_data_unused_tag_p (TYPE_1__*) ; 
 char* xfs_dir3_data_endp (struct xfs_da_geometry*,struct xfs_dir2_data_hdr*) ; 

void
xfs_dir2_data_freescan_int(
	struct xfs_da_geometry	*geo,
	const struct xfs_dir_ops *ops,
	struct xfs_dir2_data_hdr *hdr,
	int			*loghead)
{
	xfs_dir2_data_entry_t	*dep;		/* active data entry */
	xfs_dir2_data_unused_t	*dup;		/* unused data entry */
	struct xfs_dir2_data_free *bf;
	char			*endp;		/* end of block's data */
	char			*p;		/* current entry pointer */

	ASSERT(hdr->magic == cpu_to_be32(XFS_DIR2_DATA_MAGIC) ||
	       hdr->magic == cpu_to_be32(XFS_DIR3_DATA_MAGIC) ||
	       hdr->magic == cpu_to_be32(XFS_DIR2_BLOCK_MAGIC) ||
	       hdr->magic == cpu_to_be32(XFS_DIR3_BLOCK_MAGIC));

	/*
	 * Start by clearing the table.
	 */
	bf = ops->data_bestfree_p(hdr);
	memset(bf, 0, sizeof(*bf) * XFS_DIR2_DATA_FD_COUNT);
	*loghead = 1;
	/*
	 * Set up pointers.
	 */
	p = (char *)ops->data_entry_p(hdr);
	endp = xfs_dir3_data_endp(geo, hdr);
	/*
	 * Loop over the block's entries.
	 */
	while (p < endp) {
		dup = (xfs_dir2_data_unused_t *)p;
		/*
		 * If it's a free entry, insert it.
		 */
		if (be16_to_cpu(dup->freetag) == XFS_DIR2_DATA_FREE_TAG) {
			ASSERT((char *)dup - (char *)hdr ==
			       be16_to_cpu(*xfs_dir2_data_unused_tag_p(dup)));
			xfs_dir2_data_freeinsert(hdr, bf, dup, loghead);
			p += be16_to_cpu(dup->length);
		}
		/*
		 * For active entries, check their tags and skip them.
		 */
		else {
			dep = (xfs_dir2_data_entry_t *)p;
			ASSERT((char *)dep - (char *)hdr ==
			       be16_to_cpu(*ops->data_entry_tag_p(dep)));
			p += ops->data_entsize(dep->namelen);
		}
	}
}