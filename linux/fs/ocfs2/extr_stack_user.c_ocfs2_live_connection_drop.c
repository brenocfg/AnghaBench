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
struct ocfs2_live_connection {int /*<<< orphan*/ * oc_conn; int /*<<< orphan*/  oc_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct ocfs2_live_connection*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocfs2_control_lock ; 

__attribute__((used)) static void ocfs2_live_connection_drop(struct ocfs2_live_connection *c)
{
	mutex_lock(&ocfs2_control_lock);
	list_del_init(&c->oc_list);
	c->oc_conn = NULL;
	mutex_unlock(&ocfs2_control_lock);

	kfree(c);
}