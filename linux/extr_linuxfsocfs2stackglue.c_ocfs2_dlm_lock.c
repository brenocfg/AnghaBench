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
struct ocfs2_dlm_lksb {struct ocfs2_cluster_connection* lksb_conn; } ;
struct ocfs2_cluster_connection {int dummy; } ;
struct TYPE_4__ {TYPE_1__* sp_ops; } ;
struct TYPE_3__ {int (* dlm_lock ) (struct ocfs2_cluster_connection*,int,struct ocfs2_dlm_lksb*,int /*<<< orphan*/ ,void*,unsigned int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 TYPE_2__* active_stack ; 
 int stub1 (struct ocfs2_cluster_connection*,int,struct ocfs2_dlm_lksb*,int /*<<< orphan*/ ,void*,unsigned int) ; 

int ocfs2_dlm_lock(struct ocfs2_cluster_connection *conn,
		   int mode,
		   struct ocfs2_dlm_lksb *lksb,
		   u32 flags,
		   void *name,
		   unsigned int namelen)
{
	if (!lksb->lksb_conn)
		lksb->lksb_conn = conn;
	else
		BUG_ON(lksb->lksb_conn != conn);
	return active_stack->sp_ops->dlm_lock(conn, mode, lksb, flags,
					      name, namelen);
}