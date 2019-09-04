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
struct btrfs_path {scalar_t__* slots; struct extent_buffer** nodes; } ;
struct btrfs_fs_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ IS_ERR (struct extent_buffer*) ; 
 int PTR_ERR (struct extent_buffer*) ; 
 struct extent_buffer* read_node_slot (struct btrfs_fs_info*,struct extent_buffer*,scalar_t__) ; 

__attribute__((used)) static int tree_move_down(struct btrfs_fs_info *fs_info,
			   struct btrfs_path *path,
			   int *level)
{
	struct extent_buffer *eb;

	BUG_ON(*level == 0);
	eb = read_node_slot(fs_info, path->nodes[*level], path->slots[*level]);
	if (IS_ERR(eb))
		return PTR_ERR(eb);

	path->nodes[*level - 1] = eb;
	path->slots[*level - 1] = 0;
	(*level)--;
	return 0;
}