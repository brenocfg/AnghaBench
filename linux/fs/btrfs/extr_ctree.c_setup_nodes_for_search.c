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
struct btrfs_trans_handle {int dummy; } ;
struct btrfs_root {struct btrfs_fs_info* fs_info; } ;
struct btrfs_path {struct extent_buffer** nodes; scalar_t__ search_for_split; } ;
struct btrfs_fs_info {int dummy; } ;

/* Variables and functions */
 int BTRFS_NODEPTRS_PER_BLOCK (struct btrfs_fs_info*) ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EAGAIN ; 
 int balance_level (struct btrfs_trans_handle*,struct btrfs_root*,struct btrfs_path*,int) ; 
 int btrfs_header_nritems (struct extent_buffer*) ; 
 int /*<<< orphan*/  btrfs_release_path (struct btrfs_path*) ; 
 int /*<<< orphan*/  btrfs_set_path_blocking (struct btrfs_path*) ; 
 int /*<<< orphan*/  reada_for_balance (struct btrfs_fs_info*,struct btrfs_path*,int) ; 
 int split_node (struct btrfs_trans_handle*,struct btrfs_root*,struct btrfs_path*,int) ; 

__attribute__((used)) static int
setup_nodes_for_search(struct btrfs_trans_handle *trans,
		       struct btrfs_root *root, struct btrfs_path *p,
		       struct extent_buffer *b, int level, int ins_len,
		       int *write_lock_level)
{
	struct btrfs_fs_info *fs_info = root->fs_info;
	int ret;

	if ((p->search_for_split || ins_len > 0) && btrfs_header_nritems(b) >=
	    BTRFS_NODEPTRS_PER_BLOCK(fs_info) - 3) {
		int sret;

		if (*write_lock_level < level + 1) {
			*write_lock_level = level + 1;
			btrfs_release_path(p);
			goto again;
		}

		btrfs_set_path_blocking(p);
		reada_for_balance(fs_info, p, level);
		sret = split_node(trans, root, p, level);

		BUG_ON(sret > 0);
		if (sret) {
			ret = sret;
			goto done;
		}
		b = p->nodes[level];
	} else if (ins_len < 0 && btrfs_header_nritems(b) <
		   BTRFS_NODEPTRS_PER_BLOCK(fs_info) / 2) {
		int sret;

		if (*write_lock_level < level + 1) {
			*write_lock_level = level + 1;
			btrfs_release_path(p);
			goto again;
		}

		btrfs_set_path_blocking(p);
		reada_for_balance(fs_info, p, level);
		sret = balance_level(trans, root, p, level);

		if (sret) {
			ret = sret;
			goto done;
		}
		b = p->nodes[level];
		if (!b) {
			btrfs_release_path(p);
			goto again;
		}
		BUG_ON(btrfs_header_nritems(b) == 1);
	}
	return 0;

again:
	ret = -EAGAIN;
done:
	return ret;
}