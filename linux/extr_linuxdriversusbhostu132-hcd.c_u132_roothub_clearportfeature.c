#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct u132_port {int Status; } ;
struct u132 {int num_ports; int hc_control; TYPE_1__* platform_dev; struct u132_port* port; } ;
struct TYPE_4__ {int /*<<< orphan*/ * portstatus; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int EPIPE ; 
 int OHCI_CTRL_HCFS ; 
 int OHCI_USB_OPER ; 
 int /*<<< orphan*/  RH_PS_CCS ; 
 int /*<<< orphan*/  RH_PS_CSC ; 
 int /*<<< orphan*/  RH_PS_LSDA ; 
 int /*<<< orphan*/  RH_PS_OCIC ; 
 int /*<<< orphan*/  RH_PS_PESC ; 
 int /*<<< orphan*/  RH_PS_POCI ; 
 int /*<<< orphan*/  RH_PS_PRSC ; 
 int /*<<< orphan*/  RH_PS_PSSC ; 
#define  USB_PORT_FEAT_C_CONNECTION 135 
#define  USB_PORT_FEAT_C_ENABLE 134 
#define  USB_PORT_FEAT_C_OVER_CURRENT 133 
#define  USB_PORT_FEAT_C_RESET 132 
#define  USB_PORT_FEAT_C_SUSPEND 131 
#define  USB_PORT_FEAT_ENABLE 130 
#define  USB_PORT_FEAT_POWER 129 
#define  USB_PORT_FEAT_SUSPEND 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 TYPE_2__ roothub ; 
 int u132_write_pcimem (struct u132*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int u132_roothub_clearportfeature(struct u132 *u132, u16 wValue,
	u16 wIndex)
{
	if (wIndex == 0 || wIndex > u132->num_ports) {
		return -EINVAL;
	} else {
		int port_index = wIndex - 1;
		u32 temp;
		struct u132_port *port = &u132->port[port_index];
		port->Status &= ~(1 << wValue);
		switch (wValue) {
		case USB_PORT_FEAT_ENABLE:
			temp = RH_PS_CCS;
			break;
		case USB_PORT_FEAT_C_ENABLE:
			temp = RH_PS_PESC;
			break;
		case USB_PORT_FEAT_SUSPEND:
			temp = RH_PS_POCI;
			if ((u132->hc_control & OHCI_CTRL_HCFS)
				!= OHCI_USB_OPER) {
				dev_err(&u132->platform_dev->dev, "TODO resume_"
					"root_hub\n");
			}
			break;
		case USB_PORT_FEAT_C_SUSPEND:
			temp = RH_PS_PSSC;
			break;
		case USB_PORT_FEAT_POWER:
			temp = RH_PS_LSDA;
			break;
		case USB_PORT_FEAT_C_CONNECTION:
			temp = RH_PS_CSC;
			break;
		case USB_PORT_FEAT_C_OVER_CURRENT:
			temp = RH_PS_OCIC;
			break;
		case USB_PORT_FEAT_C_RESET:
			temp = RH_PS_PRSC;
			break;
		default:
			return -EPIPE;
		}
		return u132_write_pcimem(u132, roothub.portstatus[port_index],
		       temp);
	}
}