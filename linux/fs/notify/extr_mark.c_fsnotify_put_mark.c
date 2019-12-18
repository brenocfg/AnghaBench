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
struct fsnotify_mark_connector {struct fsnotify_mark_connector* destroy_next; int /*<<< orphan*/  lock; int /*<<< orphan*/  list; } ;
struct fsnotify_mark {int /*<<< orphan*/  g_list; int /*<<< orphan*/  connector; int /*<<< orphan*/  obj_list; int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 unsigned int FSNOTIFY_OBJ_TYPE_DETACHED ; 
 int /*<<< orphan*/  FSNOTIFY_REAPER_DELAY ; 
 struct fsnotify_mark_connector* READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __fsnotify_recalc_mask (struct fsnotify_mark_connector*) ; 
 struct fsnotify_mark_connector* connector_destroy_list ; 
 int /*<<< orphan*/  connector_reaper_work ; 
 int /*<<< orphan*/  destroy_list ; 
 int /*<<< orphan*/  destroy_lock ; 
 void* fsnotify_detach_connector_from_object (struct fsnotify_mark_connector*,unsigned int*) ; 
 int /*<<< orphan*/  fsnotify_drop_object (unsigned int,void*) ; 
 int /*<<< orphan*/  fsnotify_final_mark_destroy (struct fsnotify_mark*) ; 
 int /*<<< orphan*/  hlist_del_init_rcu (int /*<<< orphan*/ *) ; 
 scalar_t__ hlist_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reaper_work ; 
 int /*<<< orphan*/  refcount_dec_and_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ refcount_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  system_unbound_wq ; 

void fsnotify_put_mark(struct fsnotify_mark *mark)
{
	struct fsnotify_mark_connector *conn = READ_ONCE(mark->connector);
	void *objp = NULL;
	unsigned int type = FSNOTIFY_OBJ_TYPE_DETACHED;
	bool free_conn = false;

	/* Catch marks that were actually never attached to object */
	if (!conn) {
		if (refcount_dec_and_test(&mark->refcnt))
			fsnotify_final_mark_destroy(mark);
		return;
	}

	/*
	 * We have to be careful so that traversals of obj_list under lock can
	 * safely grab mark reference.
	 */
	if (!refcount_dec_and_lock(&mark->refcnt, &conn->lock))
		return;

	hlist_del_init_rcu(&mark->obj_list);
	if (hlist_empty(&conn->list)) {
		objp = fsnotify_detach_connector_from_object(conn, &type);
		free_conn = true;
	} else {
		__fsnotify_recalc_mask(conn);
	}
	WRITE_ONCE(mark->connector, NULL);
	spin_unlock(&conn->lock);

	fsnotify_drop_object(type, objp);

	if (free_conn) {
		spin_lock(&destroy_lock);
		conn->destroy_next = connector_destroy_list;
		connector_destroy_list = conn;
		spin_unlock(&destroy_lock);
		queue_work(system_unbound_wq, &connector_reaper_work);
	}
	/*
	 * Note that we didn't update flags telling whether inode cares about
	 * what's happening with children. We update these flags from
	 * __fsnotify_parent() lazily when next event happens on one of our
	 * children.
	 */
	spin_lock(&destroy_lock);
	list_add(&mark->g_list, &destroy_list);
	spin_unlock(&destroy_lock);
	queue_delayed_work(system_unbound_wq, &reaper_work,
			   FSNOTIFY_REAPER_DELAY);
}