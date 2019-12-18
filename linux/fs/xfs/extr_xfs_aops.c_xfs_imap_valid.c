#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ xfs_fileoff_t ;
struct TYPE_5__ {scalar_t__ br_startoff; scalar_t__ br_blockcount; } ;
struct xfs_writepage_ctx {scalar_t__ fork; scalar_t__ data_seq; scalar_t__ cow_seq; TYPE_2__ imap; } ;
struct TYPE_6__ {int /*<<< orphan*/  if_seq; } ;
struct xfs_inode {TYPE_1__* i_cowfp; TYPE_3__ i_df; } ;
struct TYPE_4__ {int /*<<< orphan*/  if_seq; } ;

/* Variables and functions */
 scalar_t__ READ_ONCE (int /*<<< orphan*/ ) ; 
 scalar_t__ XFS_COW_FORK ; 
 scalar_t__ xfs_inode_has_cow_data (struct xfs_inode*) ; 

__attribute__((used)) static bool
xfs_imap_valid(
	struct xfs_writepage_ctx	*wpc,
	struct xfs_inode		*ip,
	xfs_fileoff_t			offset_fsb)
{
	if (offset_fsb < wpc->imap.br_startoff ||
	    offset_fsb >= wpc->imap.br_startoff + wpc->imap.br_blockcount)
		return false;
	/*
	 * If this is a COW mapping, it is sufficient to check that the mapping
	 * covers the offset. Be careful to check this first because the caller
	 * can revalidate a COW mapping without updating the data seqno.
	 */
	if (wpc->fork == XFS_COW_FORK)
		return true;

	/*
	 * This is not a COW mapping. Check the sequence number of the data fork
	 * because concurrent changes could have invalidated the extent. Check
	 * the COW fork because concurrent changes since the last time we
	 * checked (and found nothing at this offset) could have added
	 * overlapping blocks.
	 */
	if (wpc->data_seq != READ_ONCE(ip->i_df.if_seq))
		return false;
	if (xfs_inode_has_cow_data(ip) &&
	    wpc->cow_seq != READ_ONCE(ip->i_cowfp->if_seq))
		return false;
	return true;
}