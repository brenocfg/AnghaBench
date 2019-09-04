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
struct super_block {int dummy; } ;
struct inode {int dummy; } ;
struct hostfs_inode_info {int fd; struct inode vfs_inode; int /*<<< orphan*/  open_mutex; scalar_t__ mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL_ACCOUNT ; 
 int /*<<< orphan*/  inode_init_once (struct inode*) ; 
 struct hostfs_inode_info* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct inode *hostfs_alloc_inode(struct super_block *sb)
{
	struct hostfs_inode_info *hi;

	hi = kmalloc(sizeof(*hi), GFP_KERNEL_ACCOUNT);
	if (hi == NULL)
		return NULL;
	hi->fd = -1;
	hi->mode = 0;
	inode_init_once(&hi->vfs_inode);
	mutex_init(&hi->open_mutex);
	return &hi->vfs_inode;
}