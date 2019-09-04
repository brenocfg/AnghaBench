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

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int EPERM ; 
 int /*<<< orphan*/  XATTR_NAME_IMA ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ima_protect_xattr(struct dentry *dentry, const char *xattr_name,
			     const void *xattr_value, size_t xattr_value_len)
{
	if (strcmp(xattr_name, XATTR_NAME_IMA) == 0) {
		if (!capable(CAP_SYS_ADMIN))
			return -EPERM;
		return 1;
	}
	return 0;
}