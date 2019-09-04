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
struct nvmefc_fcp_req {struct nvme_private* private; } ;
struct nvme_private {int /*<<< orphan*/  abort_work; } ;
struct nvme_fc_remote_port {int dummy; } ;
struct nvme_fc_local_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qla_nvme_abort_work ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void qla_nvme_fcp_abort(struct nvme_fc_local_port *lport,
    struct nvme_fc_remote_port *rport, void *hw_queue_handle,
    struct nvmefc_fcp_req *fd)
{
	struct nvme_private *priv = fd->private;

	INIT_WORK(&priv->abort_work, qla_nvme_abort_work);
	schedule_work(&priv->abort_work);
}