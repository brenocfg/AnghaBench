#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ xfs_ino_t ;
struct xfs_mount {int /*<<< orphan*/  m_super; } ;
struct xfs_inode {scalar_t__ i_ino; int /*<<< orphan*/  i_ioend_lock; int /*<<< orphan*/  i_ioend_list; int /*<<< orphan*/  i_ioend_work; scalar_t__ i_checked; scalar_t__ i_sick; int /*<<< orphan*/  i_d; scalar_t__ i_delayed_blks; scalar_t__ i_flags; int /*<<< orphan*/  i_df; int /*<<< orphan*/  i_cformat; scalar_t__ i_cnextents; int /*<<< orphan*/ * i_cowfp; int /*<<< orphan*/ * i_afp; int /*<<< orphan*/  i_imap; struct xfs_mount* i_mount; int /*<<< orphan*/  i_pincount; } ;
struct xfs_imap {int dummy; } ;
struct TYPE_3__ {scalar_t__ i_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* VFS_I (struct xfs_inode*) ; 
 int /*<<< orphan*/  XFS_DINODE_FMT_EXTENTS ; 
 int /*<<< orphan*/  XFS_STATS_INC (struct xfs_mount*,int /*<<< orphan*/ ) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ inode_init_always (int /*<<< orphan*/ ,TYPE_1__*) ; 
 struct xfs_inode* kmem_zone_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_zone_free (int /*<<< orphan*/ ,struct xfs_inode*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vn_active ; 
 int /*<<< orphan*/  xfs_end_io ; 
 int /*<<< orphan*/  xfs_inode_zone ; 
 int /*<<< orphan*/  xfs_isiflocked (struct xfs_inode*) ; 

struct xfs_inode *
xfs_inode_alloc(
	struct xfs_mount	*mp,
	xfs_ino_t		ino)
{
	struct xfs_inode	*ip;

	/*
	 * if this didn't occur in transactions, we could use
	 * KM_MAYFAIL and return NULL here on ENOMEM. Set the
	 * code up to do this anyway.
	 */
	ip = kmem_zone_alloc(xfs_inode_zone, 0);
	if (!ip)
		return NULL;
	if (inode_init_always(mp->m_super, VFS_I(ip))) {
		kmem_zone_free(xfs_inode_zone, ip);
		return NULL;
	}

	/* VFS doesn't initialise i_mode! */
	VFS_I(ip)->i_mode = 0;

	XFS_STATS_INC(mp, vn_active);
	ASSERT(atomic_read(&ip->i_pincount) == 0);
	ASSERT(!xfs_isiflocked(ip));
	ASSERT(ip->i_ino == 0);

	/* initialise the xfs inode */
	ip->i_ino = ino;
	ip->i_mount = mp;
	memset(&ip->i_imap, 0, sizeof(struct xfs_imap));
	ip->i_afp = NULL;
	ip->i_cowfp = NULL;
	ip->i_cnextents = 0;
	ip->i_cformat = XFS_DINODE_FMT_EXTENTS;
	memset(&ip->i_df, 0, sizeof(ip->i_df));
	ip->i_flags = 0;
	ip->i_delayed_blks = 0;
	memset(&ip->i_d, 0, sizeof(ip->i_d));
	ip->i_sick = 0;
	ip->i_checked = 0;
	INIT_WORK(&ip->i_ioend_work, xfs_end_io);
	INIT_LIST_HEAD(&ip->i_ioend_list);
	spin_lock_init(&ip->i_ioend_lock);

	return ip;
}