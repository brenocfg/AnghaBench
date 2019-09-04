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
struct btrfs_fs_info {int /*<<< orphan*/ * stripe_hash_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  btrfs_clear_rbio_cache (struct btrfs_fs_info*) ; 
 int /*<<< orphan*/  kvfree (int /*<<< orphan*/ *) ; 

void btrfs_free_stripe_hash_table(struct btrfs_fs_info *info)
{
	if (!info->stripe_hash_table)
		return;
	btrfs_clear_rbio_cache(info);
	kvfree(info->stripe_hash_table);
	info->stripe_hash_table = NULL;
}