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
struct extent_buffer {int dummy; } ;
struct btrfs_key {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void key_search_validate(struct extent_buffer *b,
				const struct btrfs_key *key,
				int level)
{
#ifdef CONFIG_BTRFS_ASSERT
	struct btrfs_disk_key disk_key;

	btrfs_cpu_key_to_disk(&disk_key, key);

	if (level == 0)
		ASSERT(!memcmp_extent_buffer(b, &disk_key,
		    offsetof(struct btrfs_leaf, items[0].key),
		    sizeof(disk_key)));
	else
		ASSERT(!memcmp_extent_buffer(b, &disk_key,
		    offsetof(struct btrfs_node, ptrs[0].key),
		    sizeof(disk_key)));
#endif
}