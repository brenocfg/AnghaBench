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
typedef  scalar_t__ xfs_fsize_t ;
struct TYPE_4__ {int /*<<< orphan*/  totsize; } ;
struct xfs_attr_shortform {TYPE_2__ hdr; } ;
typedef  struct xfs_attr_shortform xfs_attr_shortform_t ;
struct TYPE_3__ {int /*<<< orphan*/  di_size; } ;
struct xfs_inode {int /*<<< orphan*/ * i_cowfp; int /*<<< orphan*/ * i_afp; TYPE_1__ i_d; } ;
struct xfs_dinode {int di_aformat; int /*<<< orphan*/  di_size; int /*<<< orphan*/  di_format; } ;
struct inode {int i_mode; int /*<<< orphan*/  i_rdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int EFSCORRUPTED ; 
 int /*<<< orphan*/  KM_NOFS ; 
#define  S_IFBLK 137 
#define  S_IFCHR 136 
#define  S_IFDIR 135 
#define  S_IFIFO 134 
#define  S_IFLNK 133 
 int S_IFMT ; 
#define  S_IFREG 132 
#define  S_IFSOCK 131 
 struct inode* VFS_I (struct xfs_inode*) ; 
 int /*<<< orphan*/  XFS_ATTR_FORK ; 
 int /*<<< orphan*/  XFS_DATA_FORK ; 
 scalar_t__ XFS_DFORK_APTR (struct xfs_dinode*) ; 
 int /*<<< orphan*/  XFS_DFORK_Q (struct xfs_dinode*) ; 
#define  XFS_DINODE_FMT_BTREE 130 
#define  XFS_DINODE_FMT_EXTENTS 129 
#define  XFS_DINODE_FMT_LOCAL 128 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_zone_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmem_zone_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_dinode_get_rdev (struct xfs_dinode*) ; 
 int /*<<< orphan*/  xfs_idestroy_fork (struct xfs_inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_ifork_init_cow (struct xfs_inode*) ; 
 int /*<<< orphan*/  xfs_ifork_zone ; 
 int xfs_iformat_btree (struct xfs_inode*,struct xfs_dinode*,int /*<<< orphan*/ ) ; 
 int xfs_iformat_extents (struct xfs_inode*,struct xfs_dinode*,int /*<<< orphan*/ ) ; 
 int xfs_iformat_local (struct xfs_inode*,struct xfs_dinode*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ xfs_is_reflink_inode (struct xfs_inode*) ; 
 int /*<<< orphan*/  xfs_to_linux_dev_t (int /*<<< orphan*/ ) ; 

int
xfs_iformat_fork(
	struct xfs_inode	*ip,
	struct xfs_dinode	*dip)
{
	struct inode		*inode = VFS_I(ip);
	struct xfs_attr_shortform *atp;
	int			size;
	int			error = 0;
	xfs_fsize_t             di_size;

	switch (inode->i_mode & S_IFMT) {
	case S_IFIFO:
	case S_IFCHR:
	case S_IFBLK:
	case S_IFSOCK:
		ip->i_d.di_size = 0;
		inode->i_rdev = xfs_to_linux_dev_t(xfs_dinode_get_rdev(dip));
		break;

	case S_IFREG:
	case S_IFLNK:
	case S_IFDIR:
		switch (dip->di_format) {
		case XFS_DINODE_FMT_LOCAL:
			di_size = be64_to_cpu(dip->di_size);
			size = (int)di_size;
			error = xfs_iformat_local(ip, dip, XFS_DATA_FORK, size);
			break;
		case XFS_DINODE_FMT_EXTENTS:
			error = xfs_iformat_extents(ip, dip, XFS_DATA_FORK);
			break;
		case XFS_DINODE_FMT_BTREE:
			error = xfs_iformat_btree(ip, dip, XFS_DATA_FORK);
			break;
		default:
			return -EFSCORRUPTED;
		}
		break;

	default:
		return -EFSCORRUPTED;
	}
	if (error)
		return error;

	if (xfs_is_reflink_inode(ip)) {
		ASSERT(ip->i_cowfp == NULL);
		xfs_ifork_init_cow(ip);
	}

	if (!XFS_DFORK_Q(dip))
		return 0;

	ASSERT(ip->i_afp == NULL);
	ip->i_afp = kmem_zone_zalloc(xfs_ifork_zone, KM_NOFS);

	switch (dip->di_aformat) {
	case XFS_DINODE_FMT_LOCAL:
		atp = (xfs_attr_shortform_t *)XFS_DFORK_APTR(dip);
		size = be16_to_cpu(atp->hdr.totsize);

		error = xfs_iformat_local(ip, dip, XFS_ATTR_FORK, size);
		break;
	case XFS_DINODE_FMT_EXTENTS:
		error = xfs_iformat_extents(ip, dip, XFS_ATTR_FORK);
		break;
	case XFS_DINODE_FMT_BTREE:
		error = xfs_iformat_btree(ip, dip, XFS_ATTR_FORK);
		break;
	default:
		error = -EFSCORRUPTED;
		break;
	}
	if (error) {
		kmem_zone_free(xfs_ifork_zone, ip->i_afp);
		ip->i_afp = NULL;
		if (ip->i_cowfp)
			kmem_zone_free(xfs_ifork_zone, ip->i_cowfp);
		ip->i_cowfp = NULL;
		xfs_idestroy_fork(ip, XFS_DATA_FORK);
	}
	return error;
}