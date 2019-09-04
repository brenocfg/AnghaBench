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
typedef  int u16 ;
struct inode {int i_mode; int /*<<< orphan*/  i_flags; int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; int /*<<< orphan*/  i_sb; } ;
struct hfsplus_sb_info {int umask; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; } ;
struct hfsplus_perm {int rootflags; int /*<<< orphan*/  userflags; int /*<<< orphan*/  group; int /*<<< orphan*/  owner; int /*<<< orphan*/  mode; } ;
struct TYPE_2__ {int /*<<< orphan*/  userflags; } ;

/* Variables and functions */
 int HFSPLUS_FLG_APPEND ; 
 int HFSPLUS_FLG_IMMUTABLE ; 
 TYPE_1__* HFSPLUS_I (struct inode*) ; 
 struct hfsplus_sb_info* HFSPLUS_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_APPEND ; 
 int S_IALLUGO ; 
 int S_IFDIR ; 
 int S_IFREG ; 
 int /*<<< orphan*/  S_IMMUTABLE ; 
 int S_IRUGO ; 
 int S_IRWXUGO ; 
 int S_IWUGO ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i_gid_read (struct inode*) ; 
 int /*<<< orphan*/  i_gid_write (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i_uid_read (struct inode*) ; 
 int /*<<< orphan*/  i_uid_write (struct inode*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hfsplus_get_perms(struct inode *inode,
		struct hfsplus_perm *perms, int dir)
{
	struct hfsplus_sb_info *sbi = HFSPLUS_SB(inode->i_sb);
	u16 mode;

	mode = be16_to_cpu(perms->mode);

	i_uid_write(inode, be32_to_cpu(perms->owner));
	if (!i_uid_read(inode) && !mode)
		inode->i_uid = sbi->uid;

	i_gid_write(inode, be32_to_cpu(perms->group));
	if (!i_gid_read(inode) && !mode)
		inode->i_gid = sbi->gid;

	if (dir) {
		mode = mode ? (mode & S_IALLUGO) : (S_IRWXUGO & ~(sbi->umask));
		mode |= S_IFDIR;
	} else if (!mode)
		mode = S_IFREG | ((S_IRUGO|S_IWUGO) & ~(sbi->umask));
	inode->i_mode = mode;

	HFSPLUS_I(inode)->userflags = perms->userflags;
	if (perms->rootflags & HFSPLUS_FLG_IMMUTABLE)
		inode->i_flags |= S_IMMUTABLE;
	else
		inode->i_flags &= ~S_IMMUTABLE;
	if (perms->rootflags & HFSPLUS_FLG_APPEND)
		inode->i_flags |= S_APPEND;
	else
		inode->i_flags &= ~S_APPEND;
}