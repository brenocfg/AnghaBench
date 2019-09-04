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
 scalar_t__ XATTR_MAC_OSX_PREFIX_LEN ; 
 int /*<<< orphan*/  is_known_namespace (char const*) ; 

__attribute__((used)) static int name_len(const char *xattr_name, int xattr_name_len)
{
	int len = xattr_name_len + 1;

	if (!is_known_namespace(xattr_name))
		len += XATTR_MAC_OSX_PREFIX_LEN;

	return len;
}