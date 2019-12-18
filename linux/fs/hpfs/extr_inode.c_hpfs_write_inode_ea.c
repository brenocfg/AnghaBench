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
struct inode {int i_mode; int /*<<< orphan*/  i_rdev; int /*<<< orphan*/  i_sb; int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; } ;
struct hpfs_inode_info {int i_ea_uid; int i_ea_gid; int i_ea_mode; } ;
struct fnode {int dummy; } ;
typedef  scalar_t__ __le32 ;
struct TYPE_2__ {int sb_eas; int sb_mode; int /*<<< orphan*/  sb_gid; int /*<<< orphan*/  sb_uid; } ;

/* Variables and functions */
 int S_IFDIR ; 
 int S_IFREG ; 
 scalar_t__ S_ISBLK (int) ; 
 scalar_t__ S_ISCHR (int) ; 
 scalar_t__ S_ISDIR (int) ; 
 int /*<<< orphan*/  S_ISLNK (int) ; 
 scalar_t__ cpu_to_le32 (int) ; 
 int /*<<< orphan*/  gid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct hpfs_inode_info* hpfs_i (struct inode*) ; 
 TYPE_1__* hpfs_sb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpfs_set_ea (struct inode*,struct fnode*,char*,char*,int) ; 
 int i_gid_read (struct inode*) ; 
 int i_uid_read (struct inode*) ; 
 int new_encode_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hpfs_write_inode_ea(struct inode *i, struct fnode *fnode)
{
	struct hpfs_inode_info *hpfs_inode = hpfs_i(i);
	/*if (le32_to_cpu(fnode->acl_size_l) || le16_to_cpu(fnode->acl_size_s)) {
		   Some unknown structures like ACL may be in fnode,
		   we'd better not overwrite them
		hpfs_error(i->i_sb, "fnode %08x has some unknown HPFS386 structures", i->i_ino);
	} else*/ if (hpfs_sb(i->i_sb)->sb_eas >= 2) {
		__le32 ea;
		if (!uid_eq(i->i_uid, hpfs_sb(i->i_sb)->sb_uid) || hpfs_inode->i_ea_uid) {
			ea = cpu_to_le32(i_uid_read(i));
			hpfs_set_ea(i, fnode, "UID", (char*)&ea, 2);
			hpfs_inode->i_ea_uid = 1;
		}
		if (!gid_eq(i->i_gid, hpfs_sb(i->i_sb)->sb_gid) || hpfs_inode->i_ea_gid) {
			ea = cpu_to_le32(i_gid_read(i));
			hpfs_set_ea(i, fnode, "GID", (char *)&ea, 2);
			hpfs_inode->i_ea_gid = 1;
		}
		if (!S_ISLNK(i->i_mode))
			if ((i->i_mode != ((hpfs_sb(i->i_sb)->sb_mode & ~(S_ISDIR(i->i_mode) ? 0 : 0111))
			  | (S_ISDIR(i->i_mode) ? S_IFDIR : S_IFREG))
			  && i->i_mode != ((hpfs_sb(i->i_sb)->sb_mode & ~(S_ISDIR(i->i_mode) ? 0222 : 0333))
			  | (S_ISDIR(i->i_mode) ? S_IFDIR : S_IFREG))) || hpfs_inode->i_ea_mode) {
				ea = cpu_to_le32(i->i_mode);
				/* sick, but legal */
				hpfs_set_ea(i, fnode, "MODE", (char *)&ea, 2);
				hpfs_inode->i_ea_mode = 1;
			}
		if (S_ISBLK(i->i_mode) || S_ISCHR(i->i_mode)) {
			ea = cpu_to_le32(new_encode_dev(i->i_rdev));
			hpfs_set_ea(i, fnode, "DEV", (char *)&ea, 4);
		}
	}
}