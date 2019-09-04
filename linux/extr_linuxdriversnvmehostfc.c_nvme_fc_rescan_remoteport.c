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
struct nvme_fc_rport {int /*<<< orphan*/  lport; } ;
struct nvme_fc_remote_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvme_fc_signal_discovery_scan (int /*<<< orphan*/ ,struct nvme_fc_rport*) ; 
 struct nvme_fc_rport* remoteport_to_rport (struct nvme_fc_remote_port*) ; 

void
nvme_fc_rescan_remoteport(struct nvme_fc_remote_port *remoteport)
{
	struct nvme_fc_rport *rport = remoteport_to_rport(remoteport);

	nvme_fc_signal_discovery_scan(rport->lport, rport);
}