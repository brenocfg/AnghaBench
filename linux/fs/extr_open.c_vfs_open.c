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
struct path {int /*<<< orphan*/  dentry; } ;
struct file {struct path f_path; } ;

/* Variables and functions */
 int /*<<< orphan*/  d_backing_inode (int /*<<< orphan*/ ) ; 
 int do_dentry_open (struct file*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int vfs_open(const struct path *path, struct file *file)
{
	file->f_path = *path;
	return do_dentry_open(file, d_backing_inode(path->dentry), NULL);
}