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
struct xfs_inode {int dummy; } ;
struct xfs_bmbt_irec {int /*<<< orphan*/  br_startblock; } ;

/* Variables and functions */
 int /*<<< orphan*/  isnullstartblock (int /*<<< orphan*/ ) ; 
 scalar_t__ xfs_is_always_cow_inode (struct xfs_inode*) ; 
 int xfs_reflink_trim_around_shared (struct xfs_inode*,struct xfs_bmbt_irec*,int*) ; 

bool
xfs_inode_need_cow(
	struct xfs_inode	*ip,
	struct xfs_bmbt_irec	*imap,
	bool			*shared)
{
	/* We can't update any real extents in always COW mode. */
	if (xfs_is_always_cow_inode(ip) &&
	    !isnullstartblock(imap->br_startblock)) {
		*shared = true;
		return 0;
	}

	/* Trim the mapping to the nearest shared extent boundary. */
	return xfs_reflink_trim_around_shared(ip, imap, shared);
}