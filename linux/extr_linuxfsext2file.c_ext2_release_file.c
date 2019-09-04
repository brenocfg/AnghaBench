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
struct file {int f_mode; } ;
struct TYPE_2__ {int /*<<< orphan*/  truncate_mutex; } ;

/* Variables and functions */
 TYPE_1__* EXT2_I (struct inode*) ; 
 int FMODE_WRITE ; 
 int /*<<< orphan*/  ext2_discard_reservation (struct inode*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ext2_release_file (struct inode * inode, struct file * filp)
{
	if (filp->f_mode & FMODE_WRITE) {
		mutex_lock(&EXT2_I(inode)->truncate_mutex);
		ext2_discard_reservation(inode);
		mutex_unlock(&EXT2_I(inode)->truncate_mutex);
	}
	return 0;
}