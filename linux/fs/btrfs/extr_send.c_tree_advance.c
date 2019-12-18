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
struct btrfs_path {int /*<<< orphan*/ * slots; int /*<<< orphan*/ * nodes; } ;
struct btrfs_key {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  btrfs_item_key_to_cpu (int /*<<< orphan*/ ,struct btrfs_key*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_node_key_to_cpu (int /*<<< orphan*/ ,struct btrfs_key*,int /*<<< orphan*/ ) ; 
 int tree_move_down (struct btrfs_path*,int*) ; 
 int tree_move_next_or_upnext (struct btrfs_path*,int*,int) ; 

__attribute__((used)) static int tree_advance(struct btrfs_path *path,
			int *level, int root_level,
			int allow_down,
			struct btrfs_key *key)
{
	int ret;

	if (*level == 0 || !allow_down) {
		ret = tree_move_next_or_upnext(path, level, root_level);
	} else {
		ret = tree_move_down(path, level);
	}
	if (ret >= 0) {
		if (*level == 0)
			btrfs_item_key_to_cpu(path->nodes[*level], key,
					path->slots[*level]);
		else
			btrfs_node_key_to_cpu(path->nodes[*level], key,
					path->slots[*level]);
	}
	return ret;
}