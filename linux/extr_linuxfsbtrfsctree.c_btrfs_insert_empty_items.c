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
typedef  scalar_t__ u32 ;
struct btrfs_trans_handle {int dummy; } ;
struct btrfs_root {int dummy; } ;
struct btrfs_path {int* slots; } ;
struct btrfs_key {int dummy; } ;
struct btrfs_item {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EEXIST ; 
 int btrfs_search_slot (struct btrfs_trans_handle*,struct btrfs_root*,struct btrfs_key const*,struct btrfs_path*,scalar_t__,int) ; 
 int /*<<< orphan*/  setup_items_for_insert (struct btrfs_root*,struct btrfs_path*,struct btrfs_key const*,scalar_t__*,scalar_t__,scalar_t__,int) ; 

int btrfs_insert_empty_items(struct btrfs_trans_handle *trans,
			    struct btrfs_root *root,
			    struct btrfs_path *path,
			    const struct btrfs_key *cpu_key, u32 *data_size,
			    int nr)
{
	int ret = 0;
	int slot;
	int i;
	u32 total_size = 0;
	u32 total_data = 0;

	for (i = 0; i < nr; i++)
		total_data += data_size[i];

	total_size = total_data + (nr * sizeof(struct btrfs_item));
	ret = btrfs_search_slot(trans, root, cpu_key, path, total_size, 1);
	if (ret == 0)
		return -EEXIST;
	if (ret < 0)
		return ret;

	slot = path->slots[0];
	BUG_ON(slot < 0);

	setup_items_for_insert(root, path, cpu_key, data_size,
			       total_data, total_size, nr);
	return 0;
}