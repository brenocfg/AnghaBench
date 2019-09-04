#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xfs_lsn_t ;
struct TYPE_18__ {int /*<<< orphan*/  t_nsec; int /*<<< orphan*/  t_sec; } ;
struct TYPE_16__ {int /*<<< orphan*/  t_nsec; int /*<<< orphan*/  t_sec; } ;
struct TYPE_14__ {int /*<<< orphan*/  t_nsec; int /*<<< orphan*/  t_sec; } ;
struct TYPE_12__ {int /*<<< orphan*/  t_nsec; int /*<<< orphan*/  t_sec; } ;
struct xfs_log_dinode {int di_version; int /*<<< orphan*/  di_flushiter; int /*<<< orphan*/  di_uuid; int /*<<< orphan*/  di_pad2; int /*<<< orphan*/  di_lsn; int /*<<< orphan*/  di_ino; int /*<<< orphan*/  di_cowextsize; int /*<<< orphan*/  di_flags2; TYPE_7__ di_crtime; int /*<<< orphan*/  di_changecount; int /*<<< orphan*/  di_next_unlinked; int /*<<< orphan*/  di_flags; int /*<<< orphan*/  di_dmstate; int /*<<< orphan*/  di_dmevmask; int /*<<< orphan*/  di_aformat; int /*<<< orphan*/  di_forkoff; int /*<<< orphan*/  di_anextents; int /*<<< orphan*/  di_nextents; int /*<<< orphan*/  di_extsize; int /*<<< orphan*/  di_nblocks; int /*<<< orphan*/  di_size; int /*<<< orphan*/  di_mode; int /*<<< orphan*/  di_gen; int /*<<< orphan*/  di_nlink; TYPE_5__ di_ctime; TYPE_3__ di_mtime; TYPE_1__ di_atime; int /*<<< orphan*/  di_pad3; int /*<<< orphan*/  di_pad; int /*<<< orphan*/  di_projid_hi; int /*<<< orphan*/  di_projid_lo; int /*<<< orphan*/  di_gid; int /*<<< orphan*/  di_uid; int /*<<< orphan*/  di_format; int /*<<< orphan*/  di_magic; } ;
struct TYPE_19__ {int /*<<< orphan*/  t_nsec; int /*<<< orphan*/  t_sec; } ;
struct xfs_icdinode {int di_version; int /*<<< orphan*/  di_flushiter; int /*<<< orphan*/  di_cowextsize; int /*<<< orphan*/  di_flags2; TYPE_8__ di_crtime; int /*<<< orphan*/  di_flags; int /*<<< orphan*/  di_dmstate; int /*<<< orphan*/  di_dmevmask; int /*<<< orphan*/  di_aformat; int /*<<< orphan*/  di_forkoff; int /*<<< orphan*/  di_anextents; int /*<<< orphan*/  di_nextents; int /*<<< orphan*/  di_extsize; int /*<<< orphan*/  di_nblocks; int /*<<< orphan*/  di_size; int /*<<< orphan*/  di_projid_hi; int /*<<< orphan*/  di_projid_lo; int /*<<< orphan*/  di_gid; int /*<<< orphan*/  di_uid; int /*<<< orphan*/  di_format; } ;
struct xfs_inode {TYPE_10__* i_mount; int /*<<< orphan*/  i_ino; struct xfs_icdinode i_d; } ;
struct TYPE_17__ {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_15__ {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_13__ {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct inode {int /*<<< orphan*/  i_mode; int /*<<< orphan*/  i_generation; int /*<<< orphan*/  i_nlink; TYPE_6__ i_ctime; TYPE_4__ i_mtime; TYPE_2__ i_atime; } ;
struct TYPE_20__ {int /*<<< orphan*/  sb_meta_uuid; } ;
struct TYPE_11__ {TYPE_9__ m_sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  NULLAGINO ; 
 struct inode* VFS_I (struct xfs_inode*) ; 
 int /*<<< orphan*/  XFS_DINODE_MAGIC ; 
 int /*<<< orphan*/  inode_peek_iversion (struct inode*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uuid_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
xfs_inode_to_log_dinode(
	struct xfs_inode	*ip,
	struct xfs_log_dinode	*to,
	xfs_lsn_t		lsn)
{
	struct xfs_icdinode	*from = &ip->i_d;
	struct inode		*inode = VFS_I(ip);

	to->di_magic = XFS_DINODE_MAGIC;

	to->di_version = from->di_version;
	to->di_format = from->di_format;
	to->di_uid = from->di_uid;
	to->di_gid = from->di_gid;
	to->di_projid_lo = from->di_projid_lo;
	to->di_projid_hi = from->di_projid_hi;

	memset(to->di_pad, 0, sizeof(to->di_pad));
	memset(to->di_pad3, 0, sizeof(to->di_pad3));
	to->di_atime.t_sec = inode->i_atime.tv_sec;
	to->di_atime.t_nsec = inode->i_atime.tv_nsec;
	to->di_mtime.t_sec = inode->i_mtime.tv_sec;
	to->di_mtime.t_nsec = inode->i_mtime.tv_nsec;
	to->di_ctime.t_sec = inode->i_ctime.tv_sec;
	to->di_ctime.t_nsec = inode->i_ctime.tv_nsec;
	to->di_nlink = inode->i_nlink;
	to->di_gen = inode->i_generation;
	to->di_mode = inode->i_mode;

	to->di_size = from->di_size;
	to->di_nblocks = from->di_nblocks;
	to->di_extsize = from->di_extsize;
	to->di_nextents = from->di_nextents;
	to->di_anextents = from->di_anextents;
	to->di_forkoff = from->di_forkoff;
	to->di_aformat = from->di_aformat;
	to->di_dmevmask = from->di_dmevmask;
	to->di_dmstate = from->di_dmstate;
	to->di_flags = from->di_flags;

	/* log a dummy value to ensure log structure is fully initialised */
	to->di_next_unlinked = NULLAGINO;

	if (from->di_version == 3) {
		to->di_changecount = inode_peek_iversion(inode);
		to->di_crtime.t_sec = from->di_crtime.t_sec;
		to->di_crtime.t_nsec = from->di_crtime.t_nsec;
		to->di_flags2 = from->di_flags2;
		to->di_cowextsize = from->di_cowextsize;
		to->di_ino = ip->i_ino;
		to->di_lsn = lsn;
		memset(to->di_pad2, 0, sizeof(to->di_pad2));
		uuid_copy(&to->di_uuid, &ip->i_mount->m_sb.sb_meta_uuid);
		to->di_flushiter = 0;
	} else {
		to->di_flushiter = from->di_flushiter;
	}
}