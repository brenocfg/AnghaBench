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
typedef  int /*<<< orphan*/  u32 ;
struct ocfs2_dlm_lksb {int /*<<< orphan*/ * lksb_conn; } ;
struct ocfs2_cluster_connection {int dummy; } ;
struct TYPE_4__ {TYPE_1__* sp_ops; } ;
struct TYPE_3__ {int (* dlm_unlock ) (struct ocfs2_cluster_connection*,struct ocfs2_dlm_lksb*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 TYPE_2__* active_stack ; 
 int stub1 (struct ocfs2_cluster_connection*,struct ocfs2_dlm_lksb*,int /*<<< orphan*/ ) ; 

int ocfs2_dlm_unlock(struct ocfs2_cluster_connection *conn,
		     struct ocfs2_dlm_lksb *lksb,
		     u32 flags)
{
	BUG_ON(lksb->lksb_conn == NULL);

	return active_stack->sp_ops->dlm_unlock(conn, lksb, flags);
}