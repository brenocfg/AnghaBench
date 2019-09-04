#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct inode {int /*<<< orphan*/  i_sb; } ;
struct file {TYPE_1__* f_mapping; } ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_6__ {TYPE_2__* fat_inode; } ;
struct TYPE_5__ {int /*<<< orphan*/  i_mapping; } ;
struct TYPE_4__ {struct inode* host; } ;

/* Variables and functions */
 TYPE_3__* MSDOS_SB (int /*<<< orphan*/ ) ; 
 int generic_file_fsync (struct file*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int sync_mapping_buffers (int /*<<< orphan*/ ) ; 

int fat_file_fsync(struct file *filp, loff_t start, loff_t end, int datasync)
{
	struct inode *inode = filp->f_mapping->host;
	int res, err;

	res = generic_file_fsync(filp, start, end, datasync);
	err = sync_mapping_buffers(MSDOS_SB(inode->i_sb)->fat_inode->i_mapping);

	return res ? res : err;
}