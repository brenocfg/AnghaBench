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
typedef  scalar_t__ xfs_fileoff_t ;
struct xfs_inode {int dummy; } ;
struct xfs_bmbt_irec {scalar_t__ br_startoff; scalar_t__ br_blockcount; } ;

/* Variables and functions */
 int xfs_bmap_last_extent (int /*<<< orphan*/ *,struct xfs_inode*,int,struct xfs_bmbt_irec*,int*) ; 

int
xfs_bmap_eof(
	struct xfs_inode	*ip,
	xfs_fileoff_t		endoff,
	int			whichfork,
	int			*eof)
{
	struct xfs_bmbt_irec	rec;
	int			error;

	error = xfs_bmap_last_extent(NULL, ip, whichfork, &rec, eof);
	if (error || *eof)
		return error;

	*eof = endoff >= rec.br_startoff + rec.br_blockcount;
	return 0;
}