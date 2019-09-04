#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * rd; } ;
struct qtnf_bus {scalar_t__ fw_state; TYPE_1__ hw_info; scalar_t__ workqueue; } ;

/* Variables and functions */
 scalar_t__ QTNF_FW_STATE_ACTIVE ; 
 scalar_t__ QTNF_FW_STATE_DETACHED ; 
 unsigned int QTNF_MAX_MAC ; 
 int /*<<< orphan*/  destroy_workqueue (scalar_t__) ; 
 int /*<<< orphan*/  flush_workqueue (scalar_t__) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qtnf_bus_data_rx_stop (struct qtnf_bus*) ; 
 int /*<<< orphan*/  qtnf_cmd_send_deinit_fw (struct qtnf_bus*) ; 
 int /*<<< orphan*/  qtnf_core_mac_detach (struct qtnf_bus*,unsigned int) ; 
 int /*<<< orphan*/  qtnf_trans_free (struct qtnf_bus*) ; 

void qtnf_core_detach(struct qtnf_bus *bus)
{
	unsigned int macid;

	qtnf_bus_data_rx_stop(bus);

	for (macid = 0; macid < QTNF_MAX_MAC; macid++)
		qtnf_core_mac_detach(bus, macid);

	if (bus->fw_state == QTNF_FW_STATE_ACTIVE)
		qtnf_cmd_send_deinit_fw(bus);

	bus->fw_state = QTNF_FW_STATE_DETACHED;

	if (bus->workqueue) {
		flush_workqueue(bus->workqueue);
		destroy_workqueue(bus->workqueue);
	}

	kfree(bus->hw_info.rd);
	bus->hw_info.rd = NULL;

	qtnf_trans_free(bus);
}