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

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  XATTR_NAME_SMACK ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int smack_inode_copy_up_xattr(const char *name)
{
	/*
	 * Return 1 if this is the smack access Smack attribute.
	 */
	if (strcmp(name, XATTR_NAME_SMACK) == 0)
		return 1;

	return -EOPNOTSUPP;
}