#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ xfs_fileoff_t ;
struct TYPE_2__ {scalar_t__ br_startoff; scalar_t__ br_blockcount; } ;
struct xfs_writepage_ctx {scalar_t__ fork; int /*<<< orphan*/  data_seq; int /*<<< orphan*/  cow_seq; TYPE_1__ imap; } ;
struct xfs_inode {int dummy; } ;

/* Variables and functions */
 scalar_t__ XFS_COW_FORK ; 
 int xfs_bmapi_convert_delalloc (struct xfs_inode*,scalar_t__,scalar_t__,TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
xfs_convert_blocks(
	struct xfs_writepage_ctx *wpc,
	struct xfs_inode	*ip,
	xfs_fileoff_t		offset_fsb)
{
	int			error;

	/*
	 * Attempt to allocate whatever delalloc extent currently backs
	 * offset_fsb and put the result into wpc->imap.  Allocate in a loop
	 * because it may take several attempts to allocate real blocks for a
	 * contiguous delalloc extent if free space is sufficiently fragmented.
	 */
	do {
		error = xfs_bmapi_convert_delalloc(ip, wpc->fork, offset_fsb,
				&wpc->imap, wpc->fork == XFS_COW_FORK ?
					&wpc->cow_seq : &wpc->data_seq);
		if (error)
			return error;
	} while (wpc->imap.br_startoff + wpc->imap.br_blockcount <= offset_fsb);

	return 0;
}