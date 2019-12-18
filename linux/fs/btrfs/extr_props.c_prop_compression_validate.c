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
 scalar_t__ btrfs_compress_is_valid_type (char const*,size_t) ; 

__attribute__((used)) static int prop_compression_validate(const char *value, size_t len)
{
	if (!value)
		return 0;

	if (btrfs_compress_is_valid_type(value, len))
		return 0;

	return -EINVAL;
}