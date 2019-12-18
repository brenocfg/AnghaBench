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
 int EINVAL ; 
 char const* KEY_TRUSTED_PREFIX ; 
 int KEY_TRUSTED_PREFIX_LEN ; 
 char const* KEY_USER_PREFIX ; 
 int KEY_USER_PREFIX_LEN ; 
 scalar_t__ strncmp (char const*,char const*,int) ; 

__attribute__((used)) static int valid_master_desc(const char *new_desc, const char *orig_desc)
{
	int prefix_len;

	if (!strncmp(new_desc, KEY_TRUSTED_PREFIX, KEY_TRUSTED_PREFIX_LEN))
		prefix_len = KEY_TRUSTED_PREFIX_LEN;
	else if (!strncmp(new_desc, KEY_USER_PREFIX, KEY_USER_PREFIX_LEN))
		prefix_len = KEY_USER_PREFIX_LEN;
	else
		return -EINVAL;

	if (!new_desc[prefix_len])
		return -EINVAL;

	if (orig_desc && strncmp(new_desc, orig_desc, prefix_len))
		return -EINVAL;

	return 0;
}