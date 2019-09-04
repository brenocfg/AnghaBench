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
struct icom_port {scalar_t__ status; int port; struct icom_adapter* adapter; scalar_t__ dram; } ;
struct icom_adapter {int numb_ports; TYPE_1__* pci_dev; scalar_t__ base_addr; struct icom_port* port_info; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ ICOM_PORT_ACTIVE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ get_port_memory (struct icom_port*) ; 
 int /*<<< orphan*/  icom_port_active (struct icom_port*,struct icom_adapter*,int) ; 

__attribute__((used)) static int icom_load_ports(struct icom_adapter *icom_adapter)
{
	struct icom_port *icom_port;
	int port_num;

	for (port_num = 0; port_num < icom_adapter->numb_ports; port_num++) {

		icom_port = &icom_adapter->port_info[port_num];

		if (icom_port->status == ICOM_PORT_ACTIVE) {
			icom_port_active(icom_port, icom_adapter, port_num);
			icom_port->dram = icom_adapter->base_addr +
					0x2000 * icom_port->port;

			icom_port->adapter = icom_adapter;

			/* get port memory */
			if (get_port_memory(icom_port) != 0) {
				dev_err(&icom_port->adapter->pci_dev->dev,
					"Memory allocation for port FAILED\n");
			}
		}
	}
	return 0;
}