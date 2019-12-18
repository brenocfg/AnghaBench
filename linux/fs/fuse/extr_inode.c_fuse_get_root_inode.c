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
struct fuse_attr {unsigned int mode; int nlink; int /*<<< orphan*/  ino; } ;
typedef  int /*<<< orphan*/  attr ;

/* Variables and functions */
 int /*<<< orphan*/  FUSE_ROOT_ID ; 
 struct inode* fuse_iget (struct super_block*,int,int /*<<< orphan*/ ,struct fuse_attr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct fuse_attr*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct inode *fuse_get_root_inode(struct super_block *sb, unsigned mode)
{
	struct fuse_attr attr;
	memset(&attr, 0, sizeof(attr));

	attr.mode = mode;
	attr.ino = FUSE_ROOT_ID;
	attr.nlink = 1;
	return fuse_iget(sb, 1, 0, &attr, 0, 0);
}