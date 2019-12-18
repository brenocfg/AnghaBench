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
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int /*<<< orphan*/  UBIFS_XATTR_NAME_ENCRYPTION_CONTEXT ; 
 int /*<<< orphan*/  XATTR_TRUSTED_PREFIX ; 
 int /*<<< orphan*/  XATTR_TRUSTED_PREFIX_LEN ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool xattr_visible(const char *name)
{
	/* File encryption related xattrs are for internal use only */
	if (strcmp(name, UBIFS_XATTR_NAME_ENCRYPTION_CONTEXT) == 0)
		return false;

	/* Show trusted namespace only for "power" users */
	if (strncmp(name, XATTR_TRUSTED_PREFIX,
		    XATTR_TRUSTED_PREFIX_LEN) == 0 && !capable(CAP_SYS_ADMIN))
		return false;

	return true;
}