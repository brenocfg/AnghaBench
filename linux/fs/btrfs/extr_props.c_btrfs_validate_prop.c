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
struct prop_handler {int (* validate ) (char const*,size_t) ;} ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ XATTR_BTRFS_PREFIX_LEN ; 
 struct prop_handler* find_prop_handler (char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ strlen (char const*) ; 
 int stub1 (char const*,size_t) ; 

int btrfs_validate_prop(const char *name, const char *value, size_t value_len)
{
	const struct prop_handler *handler;

	if (strlen(name) <= XATTR_BTRFS_PREFIX_LEN)
		return -EINVAL;

	handler = find_prop_handler(name, NULL);
	if (!handler)
		return -EINVAL;

	if (value_len == 0)
		return 0;

	return handler->validate(value, value_len);
}