#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int umode_t ;
struct inode {unsigned int i_nlink; TYPE_2__* i_op; TYPE_1__* i_sb; } ;
struct dentry {int dummy; } ;
struct TYPE_4__ {int (* mkdir ) (struct inode*,struct dentry*,int) ;} ;
struct TYPE_3__ {unsigned int s_max_links; } ;

/* Variables and functions */
 int EMLINK ; 
 int EPERM ; 
 int S_IRWXUGO ; 
 int S_ISVTX ; 
 int /*<<< orphan*/  fsnotify_mkdir (struct inode*,struct dentry*) ; 
 int may_create (struct inode*,struct dentry*) ; 
 int security_inode_mkdir (struct inode*,struct dentry*,int) ; 
 int stub1 (struct inode*,struct dentry*,int) ; 

int vfs_mkdir(struct inode *dir, struct dentry *dentry, umode_t mode)
{
	int error = may_create(dir, dentry);
	unsigned max_links = dir->i_sb->s_max_links;

	if (error)
		return error;

	if (!dir->i_op->mkdir)
		return -EPERM;

	mode &= (S_IRWXUGO|S_ISVTX);
	error = security_inode_mkdir(dir, dentry, mode);
	if (error)
		return error;

	if (max_links && dir->i_nlink >= max_links)
		return -EMLINK;

	error = dir->i_op->mkdir(dir, dentry, mode);
	if (!error)
		fsnotify_mkdir(dir, dentry);
	return error;
}