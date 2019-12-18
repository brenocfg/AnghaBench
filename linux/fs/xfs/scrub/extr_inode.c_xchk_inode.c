#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct xfs_scrub {TYPE_2__* ip; TYPE_1__* sm; } ;
struct xfs_dinode {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  i_mode; } ;
struct TYPE_6__ {int /*<<< orphan*/  i_ino; } ;
struct TYPE_5__ {int sm_flags; int /*<<< orphan*/  sm_ino; } ;

/* Variables and functions */
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 TYPE_3__* VFS_I (TYPE_2__*) ; 
 int XFS_SCRUB_OFLAG_CORRUPT ; 
 int /*<<< orphan*/  xchk_dinode (struct xfs_scrub*,struct xfs_dinode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xchk_ino_set_corrupt (struct xfs_scrub*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xchk_inode_check_reflink_iflag (struct xfs_scrub*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xchk_inode_xref (struct xfs_scrub*,int /*<<< orphan*/ ,struct xfs_dinode*) ; 
 int /*<<< orphan*/  xfs_inode_to_disk (TYPE_2__*,struct xfs_dinode*,int /*<<< orphan*/ ) ; 

int
xchk_inode(
	struct xfs_scrub	*sc)
{
	struct xfs_dinode	di;
	int			error = 0;

	/*
	 * If sc->ip is NULL, that means that the setup function called
	 * xfs_iget to look up the inode.  xfs_iget returned a EFSCORRUPTED
	 * and a NULL inode, so flag the corruption error and return.
	 */
	if (!sc->ip) {
		xchk_ino_set_corrupt(sc, sc->sm->sm_ino);
		return 0;
	}

	/* Scrub the inode core. */
	xfs_inode_to_disk(sc->ip, &di, 0);
	xchk_dinode(sc, &di, sc->ip->i_ino);
	if (sc->sm->sm_flags & XFS_SCRUB_OFLAG_CORRUPT)
		goto out;

	/*
	 * Look for discrepancies between file's data blocks and the reflink
	 * iflag.  We already checked the iflag against the file mode when
	 * we scrubbed the dinode.
	 */
	if (S_ISREG(VFS_I(sc->ip)->i_mode))
		xchk_inode_check_reflink_iflag(sc, sc->ip->i_ino);

	xchk_inode_xref(sc, sc->ip->i_ino, &di);
out:
	return error;
}