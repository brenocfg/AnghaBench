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
typedef  int /*<<< orphan*/ * xfs_failaddr_t ;
struct TYPE_3__ {scalar_t__ di_format; } ;
struct xfs_inode {TYPE_1__ i_d; } ;
struct TYPE_4__ {scalar_t__ if_data; } ;
struct xfs_ifork {int if_bytes; TYPE_2__ if_u1; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  XFS_DATA_FORK ; 
 scalar_t__ XFS_DINODE_FMT_LOCAL ; 
 struct xfs_ifork* XFS_IFORK_PTR (struct xfs_inode*,int /*<<< orphan*/ ) ; 
 int XFS_SYMLINK_MAXLEN ; 
 int /*<<< orphan*/ * __this_address ; 
 scalar_t__ memchr (char*,int /*<<< orphan*/ ,int) ; 

xfs_failaddr_t
xfs_symlink_shortform_verify(
	struct xfs_inode	*ip)
{
	char			*sfp;
	char			*endp;
	struct xfs_ifork	*ifp;
	int			size;

	ASSERT(ip->i_d.di_format == XFS_DINODE_FMT_LOCAL);
	ifp = XFS_IFORK_PTR(ip, XFS_DATA_FORK);
	sfp = (char *)ifp->if_u1.if_data;
	size = ifp->if_bytes;
	endp = sfp + size;

	/*
	 * Zero length symlinks should never occur in memory as they are
	 * never alllowed to exist on disk.
	 */
	if (!size)
		return __this_address;

	/* No negative sizes or overly long symlink targets. */
	if (size < 0 || size > XFS_SYMLINK_MAXLEN)
		return __this_address;

	/* No NULLs in the target either. */
	if (memchr(sfp, 0, size - 1))
		return __this_address;

	/* We /did/ null-terminate the buffer, right? */
	if (*endp != 0)
		return __this_address;
	return NULL;
}