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
struct vhost_scsi_cmd {int /*<<< orphan*/  tvc_completion_list; struct vhost_scsi* tvc_vhost; } ;
struct vhost_scsi {int /*<<< orphan*/  vs_completion_work; int /*<<< orphan*/  dev; int /*<<< orphan*/  vs_completion_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  llist_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vhost_work_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vhost_scsi_complete_cmd(struct vhost_scsi_cmd *cmd)
{
	struct vhost_scsi *vs = cmd->tvc_vhost;

	llist_add(&cmd->tvc_completion_list, &vs->vs_completion_list);

	vhost_work_queue(&vs->dev, &vs->vs_completion_work);
}