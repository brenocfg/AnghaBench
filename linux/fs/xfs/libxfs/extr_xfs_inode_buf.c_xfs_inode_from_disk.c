#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {void* t_nsec; void* t_sec; } ;
struct xfs_icdinode {int di_version; void* di_cowextsize; void* di_flags2; TYPE_7__ di_crtime; void* di_flags; void* di_dmstate; void* di_dmevmask; int /*<<< orphan*/  di_aformat; int /*<<< orphan*/  di_forkoff; void* di_anextents; void* di_nextents; void* di_extsize; void* di_nblocks; void* di_size; void* di_flushiter; void* di_gid; void* di_uid; int /*<<< orphan*/  di_format; void* di_projid_hi; void* di_projid_lo; } ;
struct xfs_inode {struct xfs_icdinode i_d; } ;
struct TYPE_16__ {int /*<<< orphan*/  t_nsec; int /*<<< orphan*/  t_sec; } ;
struct TYPE_14__ {int /*<<< orphan*/  t_nsec; int /*<<< orphan*/  t_sec; } ;
struct TYPE_12__ {int /*<<< orphan*/  t_nsec; int /*<<< orphan*/  t_sec; } ;
struct TYPE_10__ {int /*<<< orphan*/  t_nsec; int /*<<< orphan*/  t_sec; } ;
struct xfs_dinode {int di_version; int /*<<< orphan*/  di_cowextsize; int /*<<< orphan*/  di_flags2; TYPE_8__ di_crtime; int /*<<< orphan*/  di_changecount; int /*<<< orphan*/  di_flags; int /*<<< orphan*/  di_dmstate; int /*<<< orphan*/  di_dmevmask; int /*<<< orphan*/  di_aformat; int /*<<< orphan*/  di_forkoff; int /*<<< orphan*/  di_anextents; int /*<<< orphan*/  di_nextents; int /*<<< orphan*/  di_extsize; int /*<<< orphan*/  di_nblocks; int /*<<< orphan*/  di_size; int /*<<< orphan*/  di_mode; int /*<<< orphan*/  di_gen; TYPE_6__ di_ctime; TYPE_4__ di_mtime; TYPE_2__ di_atime; int /*<<< orphan*/  di_flushiter; int /*<<< orphan*/  di_gid; int /*<<< orphan*/  di_uid; int /*<<< orphan*/  di_format; int /*<<< orphan*/  di_projid_hi; int /*<<< orphan*/  di_projid_lo; int /*<<< orphan*/  di_nlink; int /*<<< orphan*/  di_onlink; } ;
struct TYPE_13__ {int tv_sec; int tv_nsec; } ;
struct TYPE_11__ {int tv_sec; int tv_nsec; } ;
struct TYPE_9__ {int tv_sec; int tv_nsec; } ;
struct inode {void* i_mode; void* i_generation; TYPE_5__ i_ctime; TYPE_3__ i_mtime; TYPE_1__ i_atime; } ;

/* Variables and functions */
 struct inode* VFS_I (struct xfs_inode*) ; 
 void* be16_to_cpu (int /*<<< orphan*/ ) ; 
 void* be32_to_cpu (int /*<<< orphan*/ ) ; 
 void* be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_set_iversion_queried (struct inode*,void*) ; 
 int /*<<< orphan*/  set_nlink (struct inode*,void*) ; 

void
xfs_inode_from_disk(
	struct xfs_inode	*ip,
	struct xfs_dinode	*from)
{
	struct xfs_icdinode	*to = &ip->i_d;
	struct inode		*inode = VFS_I(ip);


	/*
	 * Convert v1 inodes immediately to v2 inode format as this is the
	 * minimum inode version format we support in the rest of the code.
	 */
	to->di_version = from->di_version;
	if (to->di_version == 1) {
		set_nlink(inode, be16_to_cpu(from->di_onlink));
		to->di_projid_lo = 0;
		to->di_projid_hi = 0;
		to->di_version = 2;
	} else {
		set_nlink(inode, be32_to_cpu(from->di_nlink));
		to->di_projid_lo = be16_to_cpu(from->di_projid_lo);
		to->di_projid_hi = be16_to_cpu(from->di_projid_hi);
	}

	to->di_format = from->di_format;
	to->di_uid = be32_to_cpu(from->di_uid);
	to->di_gid = be32_to_cpu(from->di_gid);
	to->di_flushiter = be16_to_cpu(from->di_flushiter);

	/*
	 * Time is signed, so need to convert to signed 32 bit before
	 * storing in inode timestamp which may be 64 bit. Otherwise
	 * a time before epoch is converted to a time long after epoch
	 * on 64 bit systems.
	 */
	inode->i_atime.tv_sec = (int)be32_to_cpu(from->di_atime.t_sec);
	inode->i_atime.tv_nsec = (int)be32_to_cpu(from->di_atime.t_nsec);
	inode->i_mtime.tv_sec = (int)be32_to_cpu(from->di_mtime.t_sec);
	inode->i_mtime.tv_nsec = (int)be32_to_cpu(from->di_mtime.t_nsec);
	inode->i_ctime.tv_sec = (int)be32_to_cpu(from->di_ctime.t_sec);
	inode->i_ctime.tv_nsec = (int)be32_to_cpu(from->di_ctime.t_nsec);
	inode->i_generation = be32_to_cpu(from->di_gen);
	inode->i_mode = be16_to_cpu(from->di_mode);

	to->di_size = be64_to_cpu(from->di_size);
	to->di_nblocks = be64_to_cpu(from->di_nblocks);
	to->di_extsize = be32_to_cpu(from->di_extsize);
	to->di_nextents = be32_to_cpu(from->di_nextents);
	to->di_anextents = be16_to_cpu(from->di_anextents);
	to->di_forkoff = from->di_forkoff;
	to->di_aformat	= from->di_aformat;
	to->di_dmevmask	= be32_to_cpu(from->di_dmevmask);
	to->di_dmstate	= be16_to_cpu(from->di_dmstate);
	to->di_flags	= be16_to_cpu(from->di_flags);

	if (to->di_version == 3) {
		inode_set_iversion_queried(inode,
					   be64_to_cpu(from->di_changecount));
		to->di_crtime.t_sec = be32_to_cpu(from->di_crtime.t_sec);
		to->di_crtime.t_nsec = be32_to_cpu(from->di_crtime.t_nsec);
		to->di_flags2 = be64_to_cpu(from->di_flags2);
		to->di_cowextsize = be32_to_cpu(from->di_cowextsize);
	}
}