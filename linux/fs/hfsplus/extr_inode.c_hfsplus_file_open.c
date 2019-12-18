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
struct inode {int dummy; } ;
struct file {int f_flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  opencnt; struct inode* rsrc_inode; } ;

/* Variables and functions */
 int EOVERFLOW ; 
 TYPE_1__* HFSPLUS_I (struct inode*) ; 
 scalar_t__ HFSPLUS_IS_RSRC (struct inode*) ; 
 scalar_t__ MAX_NON_LFS ; 
 int O_LARGEFILE ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ i_size_read (struct inode*) ; 

__attribute__((used)) static int hfsplus_file_open(struct inode *inode, struct file *file)
{
	if (HFSPLUS_IS_RSRC(inode))
		inode = HFSPLUS_I(inode)->rsrc_inode;
	if (!(file->f_flags & O_LARGEFILE) && i_size_read(inode) > MAX_NON_LFS)
		return -EOVERFLOW;
	atomic_inc(&HFSPLUS_I(inode)->opencnt);
	return 0;
}