#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tgtaddr ;
struct TYPE_4__ {int port_role; int /*<<< orphan*/  port_name; int /*<<< orphan*/  node_name; } ;
struct nvme_fc_rport {TYPE_1__ remoteport; } ;
struct TYPE_5__ {int /*<<< orphan*/  port_name; int /*<<< orphan*/  node_name; } ;
struct nvme_fc_lport {TYPE_2__ localport; } ;
typedef  int /*<<< orphan*/  hostaddr ;
struct TYPE_6__ {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int FCNVME_TRADDR_LENGTH ; 
 int FC_PORT_ROLE_NVME_DISCOVERY ; 
 int /*<<< orphan*/  KOBJ_CHANGE ; 
 TYPE_3__* fc_udev_device ; 
 int /*<<< orphan*/  kobject_uevent_env (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nvme_fc_signal_discovery_scan(struct nvme_fc_lport *lport,
		struct nvme_fc_rport *rport)
{
	char hostaddr[FCNVME_TRADDR_LENGTH];	/* NVMEFC_HOST_TRADDR=...*/
	char tgtaddr[FCNVME_TRADDR_LENGTH];	/* NVMEFC_TRADDR=...*/
	char *envp[4] = { "FC_EVENT=nvmediscovery", hostaddr, tgtaddr, NULL };

	if (!(rport->remoteport.port_role & FC_PORT_ROLE_NVME_DISCOVERY))
		return;

	snprintf(hostaddr, sizeof(hostaddr),
		"NVMEFC_HOST_TRADDR=nn-0x%016llx:pn-0x%016llx",
		lport->localport.node_name, lport->localport.port_name);
	snprintf(tgtaddr, sizeof(tgtaddr),
		"NVMEFC_TRADDR=nn-0x%016llx:pn-0x%016llx",
		rport->remoteport.node_name, rport->remoteport.port_name);
	kobject_uevent_env(&fc_udev_device->kobj, KOBJ_CHANGE, envp);
}