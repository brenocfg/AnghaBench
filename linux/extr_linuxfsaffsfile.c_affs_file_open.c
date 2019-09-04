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
struct inode {int /*<<< orphan*/  i_ino; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  i_opencnt; } ;

/* Variables and functions */
 TYPE_1__* AFFS_I (struct inode*) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
affs_file_open(struct inode *inode, struct file *filp)
{
	pr_debug("open(%lu,%d)\n",
		 inode->i_ino, atomic_read(&AFFS_I(inode)->i_opencnt));
	atomic_inc(&AFFS_I(inode)->i_opencnt);
	return 0;
}