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
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * btrfs_compress_types ; 
 size_t strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,char const*,size_t) ; 

bool btrfs_compress_is_valid_type(const char *str, size_t len)
{
	int i;

	for (i = 1; i < ARRAY_SIZE(btrfs_compress_types); i++) {
		size_t comp_len = strlen(btrfs_compress_types[i]);

		if (len < comp_len)
			continue;

		if (!strncmp(btrfs_compress_types[i], str, comp_len))
			return true;
	}
	return false;
}