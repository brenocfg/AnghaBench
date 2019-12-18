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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u64 ;
struct btrfs_trans_handle {int dummy; } ;
struct btrfs_root {int dummy; } ;
struct btrfs_path {scalar_t__* slots; int /*<<< orphan*/ * nodes; } ;
struct btrfs_key {scalar_t__ offset; scalar_t__ type; int /*<<< orphan*/  objectid; } ;

/* Variables and functions */
 scalar_t__ btrfs_header_nritems (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_item_key_to_cpu (int /*<<< orphan*/ ,struct btrfs_key*,scalar_t__) ; 
 int /*<<< orphan*/  btrfs_release_path (struct btrfs_path*) ; 
 int btrfs_search_prev_slot (struct btrfs_trans_handle*,struct btrfs_root*,struct btrfs_key*,struct btrfs_path*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int free_space_next_bitmap(struct btrfs_trans_handle *trans,
				  struct btrfs_root *root, struct btrfs_path *p)
{
	struct btrfs_key key;

	if (p->slots[0] + 1 < btrfs_header_nritems(p->nodes[0])) {
		p->slots[0]++;
		return 0;
	}

	btrfs_item_key_to_cpu(p->nodes[0], &key, p->slots[0]);
	btrfs_release_path(p);

	key.objectid += key.offset;
	key.type = (u8)-1;
	key.offset = (u64)-1;

	return btrfs_search_prev_slot(trans, root, &key, p, 0, 1);
}