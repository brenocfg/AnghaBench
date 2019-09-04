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
struct btrfs_root {struct extent_buffer* commit_root; struct btrfs_fs_info* fs_info; } ;
struct btrfs_path {int skip_locking; int* locks; struct extent_buffer** nodes; scalar_t__ need_commit_sem; scalar_t__ search_commit_root; } ;
struct btrfs_fs_info {int /*<<< orphan*/  commit_root_sem; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int BTRFS_MAX_LEVEL ; 
 int BTRFS_READ_LOCK ; 
 int BTRFS_WRITE_LOCK ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct extent_buffer* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct extent_buffer* btrfs_clone_extent_buffer (struct extent_buffer*) ; 
 int btrfs_header_level (struct extent_buffer*) ; 
 struct extent_buffer* btrfs_lock_root_node (struct btrfs_root*) ; 
 struct extent_buffer* btrfs_read_lock_root_node (struct btrfs_root*) ; 
 struct extent_buffer* btrfs_root_node (struct btrfs_root*) ; 
 int /*<<< orphan*/  btrfs_tree_read_unlock (struct extent_buffer*) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_buffer_get (struct extent_buffer*) ; 
 int /*<<< orphan*/  free_extent_buffer (struct extent_buffer*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct extent_buffer *btrfs_search_slot_get_root(struct btrfs_root *root,
							struct btrfs_path *p,
							int write_lock_level)
{
	struct btrfs_fs_info *fs_info = root->fs_info;
	struct extent_buffer *b;
	int root_lock;
	int level = 0;

	/* We try very hard to do read locks on the root */
	root_lock = BTRFS_READ_LOCK;

	if (p->search_commit_root) {
		/*
		 * The commit roots are read only so we always do read locks,
		 * and we always must hold the commit_root_sem when doing
		 * searches on them, the only exception is send where we don't
		 * want to block transaction commits for a long time, so
		 * we need to clone the commit root in order to avoid races
		 * with transaction commits that create a snapshot of one of
		 * the roots used by a send operation.
		 */
		if (p->need_commit_sem) {
			down_read(&fs_info->commit_root_sem);
			b = btrfs_clone_extent_buffer(root->commit_root);
			up_read(&fs_info->commit_root_sem);
			if (!b)
				return ERR_PTR(-ENOMEM);

		} else {
			b = root->commit_root;
			extent_buffer_get(b);
		}
		level = btrfs_header_level(b);
		/*
		 * Ensure that all callers have set skip_locking when
		 * p->search_commit_root = 1.
		 */
		ASSERT(p->skip_locking == 1);

		goto out;
	}

	if (p->skip_locking) {
		b = btrfs_root_node(root);
		level = btrfs_header_level(b);
		goto out;
	}

	/*
	 * If the level is set to maximum, we can skip trying to get the read
	 * lock.
	 */
	if (write_lock_level < BTRFS_MAX_LEVEL) {
		/*
		 * We don't know the level of the root node until we actually
		 * have it read locked
		 */
		b = btrfs_read_lock_root_node(root);
		level = btrfs_header_level(b);
		if (level > write_lock_level)
			goto out;

		/* Whoops, must trade for write lock */
		btrfs_tree_read_unlock(b);
		free_extent_buffer(b);
	}

	b = btrfs_lock_root_node(root);
	root_lock = BTRFS_WRITE_LOCK;

	/* The level might have changed, check again */
	level = btrfs_header_level(b);

out:
	p->nodes[level] = b;
	if (!p->skip_locking)
		p->locks[level] = root_lock;
	/*
	 * Callers are responsible for dropping b's references.
	 */
	return b;
}