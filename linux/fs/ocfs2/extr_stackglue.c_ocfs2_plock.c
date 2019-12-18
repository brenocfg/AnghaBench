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
typedef  int /*<<< orphan*/  u64 ;
struct ocfs2_cluster_connection {int dummy; } ;
struct file_lock {int dummy; } ;
struct file {int dummy; } ;
struct TYPE_4__ {TYPE_1__* sp_ops; } ;
struct TYPE_3__ {int (* plock ) (struct ocfs2_cluster_connection*,int /*<<< orphan*/ ,struct file*,int,struct file_lock*) ;} ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 TYPE_2__* active_stack ; 
 int stub1 (struct ocfs2_cluster_connection*,int /*<<< orphan*/ ,struct file*,int,struct file_lock*) ; 

int ocfs2_plock(struct ocfs2_cluster_connection *conn, u64 ino,
		struct file *file, int cmd, struct file_lock *fl)
{
	WARN_ON_ONCE(active_stack->sp_ops->plock == NULL);
	if (active_stack->sp_ops->plock)
		return active_stack->sp_ops->plock(conn, ino, file, cmd, fl);
	return -EOPNOTSUPP;
}