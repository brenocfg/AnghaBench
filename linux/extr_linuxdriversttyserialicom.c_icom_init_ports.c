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
typedef  scalar_t__ u32 ;
struct icom_port {int port; void* status; void* imbed_modem; } ;
struct icom_adapter {scalar_t__ subsystem_id; scalar_t__ version; int numb_ports; struct icom_port* port_info; } ;

/* Variables and functions */
 scalar_t__ ADAPTER_V1 ; 
 void* ICOM_IMBED_MODEM ; 
 void* ICOM_PORT_ACTIVE ; 
 void* ICOM_PORT_OFF ; 
 void* ICOM_RVX ; 
 void* ICOM_UNKNOWN ; 
 scalar_t__ PCI_DEVICE_ID_IBM_ICOM_FOUR_PORT_MODEL ; 
 scalar_t__ PCI_DEVICE_ID_IBM_ICOM_V2_ONE_PORT_RVX_ONE_PORT_MDM ; 

__attribute__((used)) static int icom_init_ports(struct icom_adapter *icom_adapter)
{
	u32 subsystem_id = icom_adapter->subsystem_id;
	int i;
	struct icom_port *icom_port;

	if (icom_adapter->version == ADAPTER_V1) {
		icom_adapter->numb_ports = 2;

		for (i = 0; i < 2; i++) {
			icom_port = &icom_adapter->port_info[i];
			icom_port->port = i;
			icom_port->status = ICOM_PORT_ACTIVE;
			icom_port->imbed_modem = ICOM_UNKNOWN;
		}
	} else {
		if (subsystem_id == PCI_DEVICE_ID_IBM_ICOM_FOUR_PORT_MODEL) {
			icom_adapter->numb_ports = 4;

			for (i = 0; i < 4; i++) {
				icom_port = &icom_adapter->port_info[i];

				icom_port->port = i;
				icom_port->status = ICOM_PORT_ACTIVE;
				icom_port->imbed_modem = ICOM_IMBED_MODEM;
			}
		} else {
			icom_adapter->numb_ports = 4;

			icom_adapter->port_info[0].port = 0;
			icom_adapter->port_info[0].status = ICOM_PORT_ACTIVE;

			if (subsystem_id ==
			    PCI_DEVICE_ID_IBM_ICOM_V2_ONE_PORT_RVX_ONE_PORT_MDM) {
				icom_adapter->port_info[0].imbed_modem = ICOM_IMBED_MODEM;
			} else {
				icom_adapter->port_info[0].imbed_modem = ICOM_RVX;
			}

			icom_adapter->port_info[1].status = ICOM_PORT_OFF;

			icom_adapter->port_info[2].port = 2;
			icom_adapter->port_info[2].status = ICOM_PORT_ACTIVE;
			icom_adapter->port_info[2].imbed_modem = ICOM_RVX;
			icom_adapter->port_info[3].status = ICOM_PORT_OFF;
		}
	}

	return 0;
}