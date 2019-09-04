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
struct extent_buffer {int dummy; } ;
struct btrfs_root {struct extent_buffer* node; } ;
struct btrfs_path {scalar_t__* slots; struct extent_buffer** nodes; } ;
struct btrfs_key {scalar_t__ offset; void* type; void* objectid; } ;
struct btrfs_item {int dummy; } ;
typedef  int /*<<< orphan*/  path ;

/* Variables and functions */
 void* BTRFS_INODE_ITEM_KEY ; 
 int /*<<< orphan*/  memset (struct btrfs_path*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  setup_items_for_insert (struct btrfs_root*,struct btrfs_path*,struct btrfs_key*,scalar_t__*,scalar_t__,scalar_t__,int) ; 

__attribute__((used)) static void insert_inode_item_key(struct btrfs_root *root)
{
	struct btrfs_path path;
	struct extent_buffer *leaf = root->node;
	struct btrfs_key key;
	u32 value_len = 0;

	memset(&path, 0, sizeof(path));

	path.nodes[0] = leaf;
	path.slots[0] = 0;

	key.objectid = BTRFS_INODE_ITEM_KEY;
	key.type = BTRFS_INODE_ITEM_KEY;
	key.offset = 0;

	setup_items_for_insert(root, &path, &key, &value_len, value_len,
			       value_len + sizeof(struct btrfs_item), 1);
}