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
struct TYPE_2__ {struct dentry* dentry; } ;
struct file {int f_mode; TYPE_1__ f_path; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int FMODE_OPENED ; 
 int /*<<< orphan*/  d_backing_inode (struct dentry*) ; 
 int do_dentry_open (struct file*,int /*<<< orphan*/ ,int (*) (struct inode*,struct file*)) ; 

int finish_open(struct file *file, struct dentry *dentry,
		int (*open)(struct inode *, struct file *))
{
	BUG_ON(file->f_mode & FMODE_OPENED); /* once it's opened, it's opened */

	file->f_path.dentry = dentry;
	return do_dentry_open(file, d_backing_inode(dentry), open);
}