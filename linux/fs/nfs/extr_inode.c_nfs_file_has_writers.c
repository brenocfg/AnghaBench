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
struct inode {int /*<<< orphan*/  i_mode; } ;
struct nfs_inode {int /*<<< orphan*/  open_files; struct inode vfs_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int inode_is_open_for_write (struct inode*) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool nfs_file_has_writers(struct nfs_inode *nfsi)
{
	struct inode *inode = &nfsi->vfs_inode;

	if (!S_ISREG(inode->i_mode))
		return false;
	if (list_empty(&nfsi->open_files))
		return false;
	return inode_is_open_for_write(inode);
}