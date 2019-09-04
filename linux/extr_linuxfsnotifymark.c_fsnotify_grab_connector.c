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
struct fsnotify_mark_connector {scalar_t__ type; int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  fsnotify_connp_t ;

/* Variables and functions */
 scalar_t__ FSNOTIFY_OBJ_TYPE_DETACHED ; 
 int /*<<< orphan*/  fsnotify_mark_srcu ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct fsnotify_mark_connector* srcu_dereference (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int srcu_read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  srcu_read_unlock (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static struct fsnotify_mark_connector *fsnotify_grab_connector(
						fsnotify_connp_t *connp)
{
	struct fsnotify_mark_connector *conn;
	int idx;

	idx = srcu_read_lock(&fsnotify_mark_srcu);
	conn = srcu_dereference(*connp, &fsnotify_mark_srcu);
	if (!conn)
		goto out;
	spin_lock(&conn->lock);
	if (conn->type == FSNOTIFY_OBJ_TYPE_DETACHED) {
		spin_unlock(&conn->lock);
		srcu_read_unlock(&fsnotify_mark_srcu, idx);
		return NULL;
	}
out:
	srcu_read_unlock(&fsnotify_mark_srcu, idx);
	return conn;
}