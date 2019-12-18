#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct node {int index; int /*<<< orphan*/  list; struct audit_tree* owner; } ;
struct inode {int /*<<< orphan*/  i_fsnotify_marks; } ;
struct fsnotify_mark {int dummy; } ;
struct audit_tree {int /*<<< orphan*/  same_root; struct audit_chunk* root; int /*<<< orphan*/  chunks; scalar_t__ goner; } ;
struct audit_chunk {int count; int /*<<< orphan*/  trees; struct node* owners; } ;
struct TYPE_3__ {int /*<<< orphan*/  mark_mutex; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct audit_chunk* alloc_chunk (int) ; 
 int /*<<< orphan*/  audit_mark_put_chunk (struct audit_chunk*) ; 
 TYPE_1__* audit_tree_group ; 
 int create_chunk (struct inode*,struct audit_tree*) ; 
 struct fsnotify_mark* fsnotify_find_mark (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  fsnotify_put_mark (struct fsnotify_mark*) ; 
 int /*<<< orphan*/  get_tree (struct audit_tree*) ; 
 int /*<<< orphan*/  hash_lock ; 
 int /*<<< orphan*/  kfree (struct audit_chunk*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct audit_chunk* mark_chunk (struct fsnotify_mark*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  replace_chunk (struct audit_chunk*,struct audit_chunk*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tag_chunk(struct inode *inode, struct audit_tree *tree)
{
	struct fsnotify_mark *mark;
	struct audit_chunk *chunk, *old;
	struct node *p;
	int n;

	mutex_lock(&audit_tree_group->mark_mutex);
	mark = fsnotify_find_mark(&inode->i_fsnotify_marks, audit_tree_group);
	if (!mark)
		return create_chunk(inode, tree);

	/*
	 * Found mark is guaranteed to be attached and mark_mutex protects mark
	 * from getting detached and thus it makes sure there is chunk attached
	 * to the mark.
	 */
	/* are we already there? */
	spin_lock(&hash_lock);
	old = mark_chunk(mark);
	for (n = 0; n < old->count; n++) {
		if (old->owners[n].owner == tree) {
			spin_unlock(&hash_lock);
			mutex_unlock(&audit_tree_group->mark_mutex);
			fsnotify_put_mark(mark);
			return 0;
		}
	}
	spin_unlock(&hash_lock);

	chunk = alloc_chunk(old->count + 1);
	if (!chunk) {
		mutex_unlock(&audit_tree_group->mark_mutex);
		fsnotify_put_mark(mark);
		return -ENOMEM;
	}

	spin_lock(&hash_lock);
	if (tree->goner) {
		spin_unlock(&hash_lock);
		mutex_unlock(&audit_tree_group->mark_mutex);
		fsnotify_put_mark(mark);
		kfree(chunk);
		return 0;
	}
	p = &chunk->owners[chunk->count - 1];
	p->index = (chunk->count - 1) | (1U<<31);
	p->owner = tree;
	get_tree(tree);
	list_add(&p->list, &tree->chunks);
	if (!tree->root) {
		tree->root = chunk;
		list_add(&tree->same_root, &chunk->trees);
	}
	/*
	 * This has to go last when updating chunk as once replace_chunk() is
	 * called, new RCU readers can see the new chunk.
	 */
	replace_chunk(chunk, old);
	spin_unlock(&hash_lock);
	mutex_unlock(&audit_tree_group->mark_mutex);
	fsnotify_put_mark(mark); /* pair to fsnotify_find_mark */
	audit_mark_put_chunk(old);

	return 0;
}