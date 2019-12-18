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
struct fsnotify_mark {int flags; } ;
struct audit_chunk {int /*<<< orphan*/  hash; int /*<<< orphan*/  trees; } ;
struct TYPE_2__ {int /*<<< orphan*/  mark_mutex; } ;

/* Variables and functions */
 int FSNOTIFY_MARK_FLAG_ATTACHED ; 
 struct audit_chunk* alloc_chunk (int) ; 
 int /*<<< orphan*/  audit_mark_put_chunk (struct audit_chunk*) ; 
 TYPE_1__* audit_tree_group ; 
 int chunk_count_trees (struct audit_chunk*) ; 
 int /*<<< orphan*/  fsnotify_detach_mark (struct fsnotify_mark*) ; 
 int /*<<< orphan*/  fsnotify_free_mark (struct fsnotify_mark*) ; 
 int /*<<< orphan*/  hash_lock ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 struct audit_chunk* mark_chunk (struct fsnotify_mark*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  replace_chunk (struct audit_chunk*,struct audit_chunk*) ; 
 int /*<<< orphan*/  replace_mark_chunk (struct fsnotify_mark*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void untag_chunk(struct audit_chunk *chunk, struct fsnotify_mark *mark)
{
	struct audit_chunk *new;
	int size;

	mutex_lock(&audit_tree_group->mark_mutex);
	/*
	 * mark_mutex stabilizes chunk attached to the mark so we can check
	 * whether it didn't change while we've dropped hash_lock.
	 */
	if (!(mark->flags & FSNOTIFY_MARK_FLAG_ATTACHED) ||
	    mark_chunk(mark) != chunk)
		goto out_mutex;

	size = chunk_count_trees(chunk);
	if (!size) {
		spin_lock(&hash_lock);
		list_del_init(&chunk->trees);
		list_del_rcu(&chunk->hash);
		replace_mark_chunk(mark, NULL);
		spin_unlock(&hash_lock);
		fsnotify_detach_mark(mark);
		mutex_unlock(&audit_tree_group->mark_mutex);
		audit_mark_put_chunk(chunk);
		fsnotify_free_mark(mark);
		return;
	}

	new = alloc_chunk(size);
	if (!new)
		goto out_mutex;

	spin_lock(&hash_lock);
	/*
	 * This has to go last when updating chunk as once replace_chunk() is
	 * called, new RCU readers can see the new chunk.
	 */
	replace_chunk(new, chunk);
	spin_unlock(&hash_lock);
	mutex_unlock(&audit_tree_group->mark_mutex);
	audit_mark_put_chunk(chunk);
	return;

out_mutex:
	mutex_unlock(&audit_tree_group->mark_mutex);
}