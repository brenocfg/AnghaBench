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
typedef  int u32 ;
struct tcpm_port {scalar_t__ vdm_state; int vdo_retry; int /*<<< orphan*/  vdm_state_machine; int /*<<< orphan*/  wq; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int CMDT_INIT ; 
 scalar_t__ CMDT_RSP_BUSY ; 
 int /*<<< orphan*/  PD_T_VDM_BUSY ; 
 scalar_t__ PD_VDO_CMDT (int) ; 
 scalar_t__ PD_VDO_SVDM (int) ; 
 scalar_t__ VDM_STATE_BUSY ; 
 scalar_t__ VDM_STATE_DONE ; 
 scalar_t__ VDM_STATE_WAIT_RSP_BUSY ; 
 int VDO_CMDT_MASK ; 
 int le32_to_cpu (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  mod_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int tcpm_pd_svdm (struct tcpm_port*,int /*<<< orphan*/  const*,int,int*) ; 
 int /*<<< orphan*/  tcpm_queue_vdm (struct tcpm_port*,int,int*,int) ; 

__attribute__((used)) static void tcpm_handle_vdm_request(struct tcpm_port *port,
				    const __le32 *payload, int cnt)
{
	int rlen = 0;
	u32 response[8] = { };
	u32 p0 = le32_to_cpu(payload[0]);

	if (port->vdm_state == VDM_STATE_BUSY) {
		/* If UFP responded busy retry after timeout */
		if (PD_VDO_CMDT(p0) == CMDT_RSP_BUSY) {
			port->vdm_state = VDM_STATE_WAIT_RSP_BUSY;
			port->vdo_retry = (p0 & ~VDO_CMDT_MASK) |
				CMDT_INIT;
			mod_delayed_work(port->wq, &port->vdm_state_machine,
					 msecs_to_jiffies(PD_T_VDM_BUSY));
			return;
		}
		port->vdm_state = VDM_STATE_DONE;
	}

	if (PD_VDO_SVDM(p0))
		rlen = tcpm_pd_svdm(port, payload, cnt, response);

	if (rlen > 0) {
		tcpm_queue_vdm(port, response[0], &response[1], rlen - 1);
		mod_delayed_work(port->wq, &port->vdm_state_machine, 0);
	}
}