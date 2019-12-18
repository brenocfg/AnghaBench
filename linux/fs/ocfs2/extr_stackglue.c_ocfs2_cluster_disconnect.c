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
struct ocfs2_cluster_connection {int dummy; } ;
struct TYPE_4__ {TYPE_1__* sp_ops; } ;
struct TYPE_3__ {int (* disconnect ) (struct ocfs2_cluster_connection*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 TYPE_2__* active_stack ; 
 int /*<<< orphan*/  kfree (struct ocfs2_cluster_connection*) ; 
 int /*<<< orphan*/  ocfs2_stack_driver_put () ; 
 int stub1 (struct ocfs2_cluster_connection*) ; 

int ocfs2_cluster_disconnect(struct ocfs2_cluster_connection *conn,
			     int hangup_pending)
{
	int ret;

	BUG_ON(conn == NULL);

	ret = active_stack->sp_ops->disconnect(conn);

	/* XXX Should we free it anyway? */
	if (!ret) {
		kfree(conn);
		if (!hangup_pending)
			ocfs2_stack_driver_put();
	}

	return ret;
}