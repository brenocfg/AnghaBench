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

/* Variables and functions */
 scalar_t__ FSNOTIFY_OBJ_TYPE_INODE ; 
 int /*<<< orphan*/  __fsnotify_recalc_mask (struct fsnotify_mark_connector*) ; 
 int /*<<< orphan*/  __fsnotify_update_child_dentry_flags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsnotify_conn_inode (struct fsnotify_mark_connector*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void fsnotify_recalc_mask(struct fsnotify_mark_connector *conn)
{
	if (!conn)
		return;

	spin_lock(&conn->lock);
	__fsnotify_recalc_mask(conn);
	spin_unlock(&conn->lock);
	if (conn->type == FSNOTIFY_OBJ_TYPE_INODE)
		__fsnotify_update_child_dentry_flags(
					fsnotify_conn_inode(conn));
}