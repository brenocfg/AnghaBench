#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct page {int dummy; } ;
struct TYPE_7__ {void* tv_nsec; void* tv_sec; } ;
struct TYPE_6__ {void* tv_nsec; void* tv_sec; } ;
struct TYPE_5__ {void* tv_nsec; void* tv_sec; } ;
struct inode {TYPE_3__ i_mtime; TYPE_2__ i_ctime; TYPE_1__ i_atime; void* i_mode; } ;
struct f2fs_inode {int i_inline; char* i_name; int /*<<< orphan*/  i_gc_failures; int /*<<< orphan*/  i_flags; int /*<<< orphan*/  i_advise; int /*<<< orphan*/  i_mtime_nsec; int /*<<< orphan*/  i_ctime_nsec; int /*<<< orphan*/  i_atime_nsec; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_atime; int /*<<< orphan*/  i_size; int /*<<< orphan*/  i_projid; int /*<<< orphan*/  i_extra_isize; int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; int /*<<< orphan*/  i_mode; } ;
typedef  scalar_t__ projid_t ;
typedef  int /*<<< orphan*/  kprojid_t ;
struct TYPE_8__ {void** i_gc_failures; void* i_flags; int /*<<< orphan*/  i_advise; int /*<<< orphan*/  i_projid; } ;

/* Variables and functions */
 int F2FS_EXTRA_ATTR ; 
 scalar_t__ F2FS_FITS_IN_INODE (struct f2fs_inode*,void*,int /*<<< orphan*/ ) ; 
 TYPE_4__* F2FS_I (struct inode*) ; 
 struct f2fs_inode* F2FS_INODE (struct page*) ; 
 int /*<<< orphan*/  F2FS_I_SB (struct inode*) ; 
 size_t GC_FAILURE_PIN ; 
 int /*<<< orphan*/  f2fs_i_size_write (struct inode*,void*) ; 
 int /*<<< orphan*/  f2fs_mark_inode_dirty_sync (struct inode*,int) ; 
 int /*<<< orphan*/  f2fs_notice (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ f2fs_sb_has_project_quota (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_set_inode_flags (struct inode*) ; 
 int f2fs_transfer_project_quota (struct inode*,int /*<<< orphan*/ ) ; 
 scalar_t__ file_enc_name (struct inode*) ; 
 int /*<<< orphan*/  i_gid_write (struct inode*,void*) ; 
 int /*<<< orphan*/  i_projid ; 
 int /*<<< orphan*/  i_uid_write (struct inode*,void*) ; 
 int /*<<< orphan*/  init_user_ns ; 
 int /*<<< orphan*/  ino_of_node (struct page*) ; 
 void* le16_to_cpu (int /*<<< orphan*/ ) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 
 void* le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_kprojid (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  projid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  recover_inline_flags (struct inode*,struct f2fs_inode*) ; 
 int recover_quota_data (struct inode*,struct page*) ; 

__attribute__((used)) static int recover_inode(struct inode *inode, struct page *page)
{
	struct f2fs_inode *raw = F2FS_INODE(page);
	char *name;
	int err;

	inode->i_mode = le16_to_cpu(raw->i_mode);

	err = recover_quota_data(inode, page);
	if (err)
		return err;

	i_uid_write(inode, le32_to_cpu(raw->i_uid));
	i_gid_write(inode, le32_to_cpu(raw->i_gid));

	if (raw->i_inline & F2FS_EXTRA_ATTR) {
		if (f2fs_sb_has_project_quota(F2FS_I_SB(inode)) &&
			F2FS_FITS_IN_INODE(raw, le16_to_cpu(raw->i_extra_isize),
								i_projid)) {
			projid_t i_projid;
			kprojid_t kprojid;

			i_projid = (projid_t)le32_to_cpu(raw->i_projid);
			kprojid = make_kprojid(&init_user_ns, i_projid);

			if (!projid_eq(kprojid, F2FS_I(inode)->i_projid)) {
				err = f2fs_transfer_project_quota(inode,
								kprojid);
				if (err)
					return err;
				F2FS_I(inode)->i_projid = kprojid;
			}
		}
	}

	f2fs_i_size_write(inode, le64_to_cpu(raw->i_size));
	inode->i_atime.tv_sec = le64_to_cpu(raw->i_atime);
	inode->i_ctime.tv_sec = le64_to_cpu(raw->i_ctime);
	inode->i_mtime.tv_sec = le64_to_cpu(raw->i_mtime);
	inode->i_atime.tv_nsec = le32_to_cpu(raw->i_atime_nsec);
	inode->i_ctime.tv_nsec = le32_to_cpu(raw->i_ctime_nsec);
	inode->i_mtime.tv_nsec = le32_to_cpu(raw->i_mtime_nsec);

	F2FS_I(inode)->i_advise = raw->i_advise;
	F2FS_I(inode)->i_flags = le32_to_cpu(raw->i_flags);
	f2fs_set_inode_flags(inode);
	F2FS_I(inode)->i_gc_failures[GC_FAILURE_PIN] =
				le16_to_cpu(raw->i_gc_failures);

	recover_inline_flags(inode, raw);

	f2fs_mark_inode_dirty_sync(inode, true);

	if (file_enc_name(inode))
		name = "<encrypted>";
	else
		name = F2FS_INODE(page)->i_name;

	f2fs_notice(F2FS_I_SB(inode), "recover_inode: ino = %x, name = %s, inline = %x",
		    ino_of_node(page), name, raw->i_inline);
	return 0;
}