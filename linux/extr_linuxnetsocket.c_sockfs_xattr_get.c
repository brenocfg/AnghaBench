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
struct xattr_handler {int dummy; } ;
struct inode {int dummy; } ;
struct TYPE_2__ {int len; int /*<<< orphan*/  name; } ;
struct dentry {TYPE_1__ d_name; } ;

/* Variables and functions */
 int ERANGE ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int sockfs_xattr_get(const struct xattr_handler *handler,
			    struct dentry *dentry, struct inode *inode,
			    const char *suffix, void *value, size_t size)
{
	if (value) {
		if (dentry->d_name.len + 1 > size)
			return -ERANGE;
		memcpy(value, dentry->d_name.name, dentry->d_name.len + 1);
	}
	return dentry->d_name.len + 1;
}