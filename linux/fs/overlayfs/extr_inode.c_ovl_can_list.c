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
 int /*<<< orphan*/  init_user_ns ; 
 scalar_t__ ns_capable_noaudit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ovl_is_private_xattr (char const*) ; 
 scalar_t__ strncmp (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool ovl_can_list(const char *s)
{
	/* List all non-trusted xatts */
	if (strncmp(s, XATTR_TRUSTED_PREFIX, XATTR_TRUSTED_PREFIX_LEN) != 0)
		return true;

	/* Never list trusted.overlay, list other trusted for superuser only */
	return !ovl_is_private_xattr(s) &&
	       ns_capable_noaudit(&init_user_ns, CAP_SYS_ADMIN);
}