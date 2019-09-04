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
struct ssusb_mtk {int /*<<< orphan*/  u3_ports; int /*<<< orphan*/  u2_ports; int /*<<< orphan*/  dev; int /*<<< orphan*/  ippc_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  SSUSB_IP_XHCI_U2_PORT_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSUSB_IP_XHCI_U3_PORT_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  U3D_SSUSB_IP_XHCI_CAP ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtu3_readl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void host_ports_num_get(struct ssusb_mtk *ssusb)
{
	u32 xhci_cap;

	xhci_cap = mtu3_readl(ssusb->ippc_base, U3D_SSUSB_IP_XHCI_CAP);
	ssusb->u2_ports = SSUSB_IP_XHCI_U2_PORT_NUM(xhci_cap);
	ssusb->u3_ports = SSUSB_IP_XHCI_U3_PORT_NUM(xhci_cap);

	dev_dbg(ssusb->dev, "host - u2_ports:%d, u3_ports:%d\n",
		 ssusb->u2_ports, ssusb->u3_ports);
}