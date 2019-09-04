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
struct inode {int /*<<< orphan*/  i_sb; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hpfs_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpfs_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpfs_write_if_changed (struct inode*) ; 

__attribute__((used)) static int hpfs_file_release(struct inode *inode, struct file *file)
{
	hpfs_lock(inode->i_sb);
	hpfs_write_if_changed(inode);
	hpfs_unlock(inode->i_sb);
	return 0;
}