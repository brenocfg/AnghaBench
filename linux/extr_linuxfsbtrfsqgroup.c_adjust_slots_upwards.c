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
struct btrfs_path {int* slots; struct extent_buffer** nodes; int /*<<< orphan*/ * locks; } ;

/* Variables and functions */
 int btrfs_header_nritems (struct extent_buffer*) ; 
 int /*<<< orphan*/  btrfs_tree_unlock_rw (struct extent_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_extent_buffer (struct extent_buffer*) ; 

__attribute__((used)) static int adjust_slots_upwards(struct btrfs_path *path, int root_level)
{
	int level = 0;
	int nr, slot;
	struct extent_buffer *eb;

	if (root_level == 0)
		return 1;

	while (level <= root_level) {
		eb = path->nodes[level];
		nr = btrfs_header_nritems(eb);
		path->slots[level]++;
		slot = path->slots[level];
		if (slot >= nr || level == 0) {
			/*
			 * Don't free the root -  we will detect this
			 * condition after our loop and return a
			 * positive value for caller to stop walking the tree.
			 */
			if (level != root_level) {
				btrfs_tree_unlock_rw(eb, path->locks[level]);
				path->locks[level] = 0;

				free_extent_buffer(eb);
				path->nodes[level] = NULL;
				path->slots[level] = 0;
			}
		} else {
			/*
			 * We have a valid slot to walk back down
			 * from. Stop here so caller can process these
			 * new nodes.
			 */
			break;
		}

		level++;
	}

	eb = path->nodes[root_level];
	if (path->slots[root_level] >= btrfs_header_nritems(eb))
		return 1;

	return 0;
}