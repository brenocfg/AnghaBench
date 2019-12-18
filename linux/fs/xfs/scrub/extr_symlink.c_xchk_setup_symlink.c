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
struct xfs_scrub {int /*<<< orphan*/  buf; } ;
struct xfs_inode {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ XFS_SYMLINK_MAXLEN ; 
 int /*<<< orphan*/  kmem_zalloc_large (scalar_t__,int /*<<< orphan*/ ) ; 
 int xchk_setup_inode_contents (struct xfs_scrub*,struct xfs_inode*,int /*<<< orphan*/ ) ; 

int
xchk_setup_symlink(
	struct xfs_scrub	*sc,
	struct xfs_inode	*ip)
{
	/* Allocate the buffer without the inode lock held. */
	sc->buf = kmem_zalloc_large(XFS_SYMLINK_MAXLEN + 1, 0);
	if (!sc->buf)
		return -ENOMEM;

	return xchk_setup_inode_contents(sc, ip, 0);
}