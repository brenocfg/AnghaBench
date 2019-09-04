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
struct inode {int i_nlink; } ;
struct f2fs_inode_info {int /*<<< orphan*/  i_sem; } ;
typedef  int /*<<< orphan*/  nid_t ;

/* Variables and functions */
 struct f2fs_inode_info* F2FS_I (struct inode*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  f2fs_i_pino_write (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  file_got_pino (struct inode*) ; 
 scalar_t__ file_wrong_pino (struct inode*) ; 
 scalar_t__ get_parent_ino (struct inode*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void try_to_fix_pino(struct inode *inode)
{
	struct f2fs_inode_info *fi = F2FS_I(inode);
	nid_t pino;

	down_write(&fi->i_sem);
	if (file_wrong_pino(inode) && inode->i_nlink == 1 &&
			get_parent_ino(inode, &pino)) {
		f2fs_i_pino_write(inode, pino);
		file_got_pino(inode);
	}
	up_write(&fi->i_sem);
}