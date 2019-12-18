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
typedef  int /*<<< orphan*/  umode_t ;
struct qstr {int /*<<< orphan*/  len; int /*<<< orphan*/  name; } ;
struct inode {int dummy; } ;
struct fscrypt_name {int /*<<< orphan*/  usr_fname; } ;
typedef  int /*<<< orphan*/  nid_t ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  F2FS_I_SB (struct inode*) ; 
 int /*<<< orphan*/  REQ_TIME ; 
 int f2fs_add_inline_entry (struct inode*,struct qstr*,int /*<<< orphan*/ ,struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int f2fs_add_regular_entry (struct inode*,struct qstr*,int /*<<< orphan*/ ,struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ f2fs_has_inline_dentry (struct inode*) ; 
 int /*<<< orphan*/  f2fs_update_time (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fname_len (struct fscrypt_name*) ; 
 int /*<<< orphan*/  fname_name (struct fscrypt_name*) ; 

int f2fs_add_dentry(struct inode *dir, struct fscrypt_name *fname,
				struct inode *inode, nid_t ino, umode_t mode)
{
	struct qstr new_name;
	int err = -EAGAIN;

	new_name.name = fname_name(fname);
	new_name.len = fname_len(fname);

	if (f2fs_has_inline_dentry(dir))
		err = f2fs_add_inline_entry(dir, &new_name, fname->usr_fname,
							inode, ino, mode);
	if (err == -EAGAIN)
		err = f2fs_add_regular_entry(dir, &new_name, fname->usr_fname,
							inode, ino, mode);

	f2fs_update_time(F2FS_I_SB(dir), REQ_TIME);
	return err;
}