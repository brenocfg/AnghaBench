#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct inode {int dummy; } ;
struct fsnotify_mark {int dummy; } ;
struct audit_tree {int /*<<< orphan*/  same_root; struct audit_chunk* root; int /*<<< orphan*/  chunks; scalar_t__ goner; } ;
struct audit_chunk {int /*<<< orphan*/  key; int /*<<< orphan*/  trees; TYPE_1__* owners; } ;
struct TYPE_4__ {int /*<<< orphan*/  mark_mutex; } ;
struct TYPE_3__ {unsigned int index; int /*<<< orphan*/  list; struct audit_tree* owner; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENOSPC ; 
 struct audit_chunk* alloc_chunk (int) ; 
 struct fsnotify_mark* alloc_mark () ; 
 TYPE_2__* audit_tree_group ; 
 scalar_t__ fsnotify_add_inode_mark_locked (struct fsnotify_mark*,struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsnotify_detach_mark (struct fsnotify_mark*) ; 
 int /*<<< orphan*/  fsnotify_free_mark (struct fsnotify_mark*) ; 
 int /*<<< orphan*/  fsnotify_put_mark (struct fsnotify_mark*) ; 
 int /*<<< orphan*/  get_tree (struct audit_tree*) ; 
 int /*<<< orphan*/  hash_lock ; 
 int /*<<< orphan*/  inode_to_key (struct inode*) ; 
 int /*<<< orphan*/  insert_hash (struct audit_chunk*) ; 
 int /*<<< orphan*/  kfree (struct audit_chunk*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  replace_mark_chunk (struct fsnotify_mark*,struct audit_chunk*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int create_chunk(struct inode *inode, struct audit_tree *tree)
{
	struct fsnotify_mark *mark;
	struct audit_chunk *chunk = alloc_chunk(1);

	if (!chunk) {
		mutex_unlock(&audit_tree_group->mark_mutex);
		return -ENOMEM;
	}

	mark = alloc_mark();
	if (!mark) {
		mutex_unlock(&audit_tree_group->mark_mutex);
		kfree(chunk);
		return -ENOMEM;
	}

	if (fsnotify_add_inode_mark_locked(mark, inode, 0)) {
		mutex_unlock(&audit_tree_group->mark_mutex);
		fsnotify_put_mark(mark);
		kfree(chunk);
		return -ENOSPC;
	}

	spin_lock(&hash_lock);
	if (tree->goner) {
		spin_unlock(&hash_lock);
		fsnotify_detach_mark(mark);
		mutex_unlock(&audit_tree_group->mark_mutex);
		fsnotify_free_mark(mark);
		fsnotify_put_mark(mark);
		kfree(chunk);
		return 0;
	}
	replace_mark_chunk(mark, chunk);
	chunk->owners[0].index = (1U << 31);
	chunk->owners[0].owner = tree;
	get_tree(tree);
	list_add(&chunk->owners[0].list, &tree->chunks);
	if (!tree->root) {
		tree->root = chunk;
		list_add(&tree->same_root, &chunk->trees);
	}
	chunk->key = inode_to_key(inode);
	/*
	 * Inserting into the hash table has to go last as once we do that RCU
	 * readers can see the chunk.
	 */
	insert_hash(chunk);
	spin_unlock(&hash_lock);
	mutex_unlock(&audit_tree_group->mark_mutex);
	/*
	 * Drop our initial reference. When mark we point to is getting freed,
	 * we get notification through ->freeing_mark callback and cleanup
	 * chunk pointing to this mark.
	 */
	fsnotify_put_mark(mark);
	return 0;
}