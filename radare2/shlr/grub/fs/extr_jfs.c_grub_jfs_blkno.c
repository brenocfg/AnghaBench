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
struct TYPE_2__ {int /*<<< orphan*/ * extents; int /*<<< orphan*/  tree; } ;
struct grub_jfs_inode {TYPE_1__ file; } ;
struct grub_jfs_data {int dummy; } ;
struct getblk_closure {unsigned int blk; struct grub_jfs_data* data; } ;

/* Variables and functions */
 int getblk (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct getblk_closure*) ; 

__attribute__((used)) static int
grub_jfs_blkno (struct grub_jfs_data *data, struct grub_jfs_inode *inode,
		unsigned int blk)
{
  struct getblk_closure c;
  c.data = data;
  c.blk = blk;
  return getblk (&inode->file.tree, &inode->file.extents[0], &c);
}