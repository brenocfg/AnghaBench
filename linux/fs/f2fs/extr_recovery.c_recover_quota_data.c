#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  void* uid_t ;
struct page {int dummy; } ;
struct inode {int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; TYPE_1__* i_sb; } ;
struct iattr {int /*<<< orphan*/  ia_valid; int /*<<< orphan*/  ia_gid; int /*<<< orphan*/  ia_uid; } ;
struct f2fs_inode {int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; } ;
typedef  void* gid_t ;
typedef  int /*<<< orphan*/  attr ;
struct TYPE_2__ {int /*<<< orphan*/  s_user_ns; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATTR_GID ; 
 int /*<<< orphan*/  ATTR_UID ; 
 struct f2fs_inode* F2FS_INODE (struct page*) ; 
 int /*<<< orphan*/  F2FS_I_SB (struct inode*) ; 
 int /*<<< orphan*/  SBI_QUOTA_NEED_REPAIR ; 
 int dquot_transfer (struct inode*,struct iattr*) ; 
 int /*<<< orphan*/  gid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_kgid (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  make_kuid (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  memset (struct iattr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_sbi_flag (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int recover_quota_data(struct inode *inode, struct page *page)
{
	struct f2fs_inode *raw = F2FS_INODE(page);
	struct iattr attr;
	uid_t i_uid = le32_to_cpu(raw->i_uid);
	gid_t i_gid = le32_to_cpu(raw->i_gid);
	int err;

	memset(&attr, 0, sizeof(attr));

	attr.ia_uid = make_kuid(inode->i_sb->s_user_ns, i_uid);
	attr.ia_gid = make_kgid(inode->i_sb->s_user_ns, i_gid);

	if (!uid_eq(attr.ia_uid, inode->i_uid))
		attr.ia_valid |= ATTR_UID;
	if (!gid_eq(attr.ia_gid, inode->i_gid))
		attr.ia_valid |= ATTR_GID;

	if (!attr.ia_valid)
		return 0;

	err = dquot_transfer(inode, &attr);
	if (err)
		set_sbi_flag(F2FS_I_SB(inode), SBI_QUOTA_NEED_REPAIR);
	return err;
}