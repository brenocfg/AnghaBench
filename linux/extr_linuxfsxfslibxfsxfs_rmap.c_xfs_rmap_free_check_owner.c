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
typedef  scalar_t__ xfs_filblks_t ;
typedef  scalar_t__ uint64_t ;
struct xfs_rmap_irec {unsigned int rm_flags; scalar_t__ rm_owner; scalar_t__ rm_offset; scalar_t__ rm_blockcount; } ;
struct xfs_mount {int dummy; } ;

/* Variables and functions */
 unsigned int XFS_RMAP_BMBT_BLOCK ; 
 scalar_t__ XFS_RMAP_NON_INODE_OWNER (scalar_t__) ; 
 scalar_t__ XFS_RMAP_OWN_UNKNOWN ; 
 unsigned int XFS_RMAP_UNWRITTEN ; 
 int /*<<< orphan*/  XFS_WANT_CORRUPTED_GOTO (struct xfs_mount*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  out ; 

__attribute__((used)) static int
xfs_rmap_free_check_owner(
	struct xfs_mount	*mp,
	uint64_t		ltoff,
	struct xfs_rmap_irec	*rec,
	xfs_filblks_t		len,
	uint64_t		owner,
	uint64_t		offset,
	unsigned int		flags)
{
	int			error = 0;

	if (owner == XFS_RMAP_OWN_UNKNOWN)
		return 0;

	/* Make sure the unwritten flag matches. */
	XFS_WANT_CORRUPTED_GOTO(mp, (flags & XFS_RMAP_UNWRITTEN) ==
			(rec->rm_flags & XFS_RMAP_UNWRITTEN), out);

	/* Make sure the owner matches what we expect to find in the tree. */
	XFS_WANT_CORRUPTED_GOTO(mp, owner == rec->rm_owner, out);

	/* Check the offset, if necessary. */
	if (XFS_RMAP_NON_INODE_OWNER(owner))
		goto out;

	if (flags & XFS_RMAP_BMBT_BLOCK) {
		XFS_WANT_CORRUPTED_GOTO(mp, rec->rm_flags & XFS_RMAP_BMBT_BLOCK,
				out);
	} else {
		XFS_WANT_CORRUPTED_GOTO(mp, rec->rm_offset <= offset, out);
		XFS_WANT_CORRUPTED_GOTO(mp,
				ltoff + rec->rm_blockcount >= offset + len,
				out);
	}

out:
	return error;
}