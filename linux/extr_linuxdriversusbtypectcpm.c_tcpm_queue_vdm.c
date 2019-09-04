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
typedef  int /*<<< orphan*/  u32 ;
struct tcpm_port {int vdo_count; int /*<<< orphan*/  vdm_state; scalar_t__ vdm_retries; int /*<<< orphan*/ * vdo_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  VDM_STATE_READY ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static void tcpm_queue_vdm(struct tcpm_port *port, const u32 header,
			   const u32 *data, int cnt)
{
	port->vdo_count = cnt + 1;
	port->vdo_data[0] = header;
	memcpy(&port->vdo_data[1], data, sizeof(u32) * cnt);
	/* Set ready, vdm state machine will actually send */
	port->vdm_retries = 0;
	port->vdm_state = VDM_STATE_READY;
}