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
 int /*<<< orphan*/  XATTR_TRUSTED_PREFIX ; 
 int /*<<< orphan*/  XATTR_TRUSTED_PREFIX_LEN ; 
 scalar_t__ capable (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int can_list(const char *xattr_name)
{
	if (!xattr_name)
		return 0;

	return strncmp(xattr_name, XATTR_TRUSTED_PREFIX,
			XATTR_TRUSTED_PREFIX_LEN) ||
				capable(CAP_SYS_ADMIN);
}