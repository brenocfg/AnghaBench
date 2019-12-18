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

/* Variables and functions */
 int /*<<< orphan*/  BLK_RW_ASYNC ; 
 int /*<<< orphan*/  ENOMEM ; 
 int HZ ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 int /*<<< orphan*/  PTR_ERR (struct inode*) ; 
 int /*<<< orphan*/  congestion_wait (int /*<<< orphan*/ ,int) ; 
 struct inode* f2fs_iget (struct super_block*,unsigned long) ; 

struct inode *f2fs_iget_retry(struct super_block *sb, unsigned long ino)
{
	struct inode *inode;
retry:
	inode = f2fs_iget(sb, ino);
	if (IS_ERR(inode)) {
		if (PTR_ERR(inode) == -ENOMEM) {
			congestion_wait(BLK_RW_ASYNC, HZ/50);
			goto retry;
		}
	}
	return inode;
}