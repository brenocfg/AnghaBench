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
struct TYPE_2__ {int /*<<< orphan*/  tailpack; } ;

/* Variables and functions */
 TYPE_1__* REISERFS_I (struct inode*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reiserfs_truncate_file (struct inode*,int) ; 

void reiserfs_vfs_truncate_file(struct inode *inode)
{
	mutex_lock(&REISERFS_I(inode)->tailpack);
	reiserfs_truncate_file(inode, 1);
	mutex_unlock(&REISERFS_I(inode)->tailpack);
}