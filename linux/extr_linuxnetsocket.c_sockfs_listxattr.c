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
 scalar_t__ ERANGE ; 
 int /*<<< orphan*/  XATTR_NAME_SOCKPROTONAME ; 
 scalar_t__ XATTR_NAME_SOCKPROTONAME_LEN ; 
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ security_inode_listsecurity (int /*<<< orphan*/ ,char*,size_t) ; 

__attribute__((used)) static ssize_t sockfs_listxattr(struct dentry *dentry, char *buffer,
				size_t size)
{
	ssize_t len;
	ssize_t used = 0;

	len = security_inode_listsecurity(d_inode(dentry), buffer, size);
	if (len < 0)
		return len;
	used += len;
	if (buffer) {
		if (size < used)
			return -ERANGE;
		buffer += len;
	}

	len = (XATTR_NAME_SOCKPROTONAME_LEN + 1);
	used += len;
	if (buffer) {
		if (size < used)
			return -ERANGE;
		memcpy(buffer, XATTR_NAME_SOCKPROTONAME, len);
		buffer += len;
	}

	return used;
}