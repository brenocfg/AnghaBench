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
struct work_struct {int dummy; } ;
struct fsnotify_mark_connector {struct fsnotify_mark_connector* destroy_next; } ;

/* Variables and functions */
 struct fsnotify_mark_connector* connector_destroy_list ; 
 int /*<<< orphan*/  destroy_lock ; 
 int /*<<< orphan*/  fsnotify_mark_connector_cachep ; 
 int /*<<< orphan*/  fsnotify_mark_srcu ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct fsnotify_mark_connector*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synchronize_srcu (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fsnotify_connector_destroy_workfn(struct work_struct *work)
{
	struct fsnotify_mark_connector *conn, *free;

	spin_lock(&destroy_lock);
	conn = connector_destroy_list;
	connector_destroy_list = NULL;
	spin_unlock(&destroy_lock);

	synchronize_srcu(&fsnotify_mark_srcu);
	while (conn) {
		free = conn;
		conn = conn->destroy_next;
		kmem_cache_free(fsnotify_mark_connector_cachep, free);
	}
}