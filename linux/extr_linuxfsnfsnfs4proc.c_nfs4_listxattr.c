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
struct dentry {int dummy; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 scalar_t__ generic_listxattr (struct dentry*,char*,size_t) ; 
 scalar_t__ nfs4_listxattr_nfs4_label (int /*<<< orphan*/ ,char*,size_t) ; 

__attribute__((used)) static ssize_t nfs4_listxattr(struct dentry *dentry, char *list, size_t size)
{
	ssize_t error, error2;

	error = generic_listxattr(dentry, list, size);
	if (error < 0)
		return error;
	if (list) {
		list += error;
		size -= error;
	}

	error2 = nfs4_listxattr_nfs4_label(d_inode(dentry), list, size);
	if (error2 < 0)
		return error2;
	return error + error2;
}