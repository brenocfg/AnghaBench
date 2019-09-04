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
struct nvmefc_ls_req {int dummy; } ;
struct nvme_fc_remote_port {int dummy; } ;
struct nvme_fc_local_port {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void
fcloop_ls_abort(struct nvme_fc_local_port *localport,
			struct nvme_fc_remote_port *remoteport,
				struct nvmefc_ls_req *lsreq)
{
}