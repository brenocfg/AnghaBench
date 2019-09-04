#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct inode {int dummy; } ;
struct fsnotify_mark {int /*<<< orphan*/  lock; } ;
struct audit_tree {int /*<<< orphan*/  same_root; struct audit_chunk* root; int /*<<< orphan*/  chunks; scalar_t__ goner; } ;
struct audit_chunk {int dead; int /*<<< orphan*/  trees; TYPE_1__* owners; struct fsnotify_mark mark; } ;
struct TYPE_2__ {unsigned int index; int /*<<< orphan*/  list; struct audit_tree* owner; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENOSPC ; 
 struct audit_chunk* alloc_chunk (int) ; 
 int /*<<< orphan*/  audit_tree_group ; 
 scalar_t__ fsnotify_add_inode_mark (struct fsnotify_mark*,struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsnotify_destroy_mark (struct fsnotify_mark*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsnotify_put_mark (struct fsnotify_mark*) ; 
 int /*<<< orphan*/  get_tree (struct audit_tree*) ; 
 int /*<<< orphan*/  hash_lock ; 
 int /*<<< orphan*/  insert_hash (struct audit_chunk*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int create_chunk(struct inode *inode, struct audit_tree *tree)
{
	struct fsnotify_mark *entry;
	struct audit_chunk *chunk = alloc_chunk(1);
	if (!chunk)
		return -ENOMEM;

	entry = &chunk->mark;
	if (fsnotify_add_inode_mark(entry, inode, 0)) {
		fsnotify_put_mark(entry);
		return -ENOSPC;
	}

	spin_lock(&entry->lock);
	spin_lock(&hash_lock);
	if (tree->goner) {
		spin_unlock(&hash_lock);
		chunk->dead = 1;
		spin_unlock(&entry->lock);
		fsnotify_destroy_mark(entry, audit_tree_group);
		fsnotify_put_mark(entry);
		return 0;
	}
	chunk->owners[0].index = (1U << 31);
	chunk->owners[0].owner = tree;
	get_tree(tree);
	list_add(&chunk->owners[0].list, &tree->chunks);
	if (!tree->root) {
		tree->root = chunk;
		list_add(&tree->same_root, &chunk->trees);
	}
	insert_hash(chunk);
	spin_unlock(&hash_lock);
	spin_unlock(&entry->lock);
	fsnotify_put_mark(entry);	/* drop initial reference */
	return 0;
}