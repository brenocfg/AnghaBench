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
struct inode {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EPERM ; 
 int /*<<< orphan*/  __putname (char*) ; 
 scalar_t__ append ; 
 char* dentry_name (struct dentry*) ; 
 int unlink_file (char*) ; 

__attribute__((used)) static int hostfs_unlink(struct inode *ino, struct dentry *dentry)
{
	char *file;
	int err;

	if (append)
		return -EPERM;

	if ((file = dentry_name(dentry)) == NULL)
		return -ENOMEM;

	err = unlink_file(file);
	__putname(file);
	return err;
}