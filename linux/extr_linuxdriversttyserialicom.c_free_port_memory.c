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
struct pci_dev {int dummy; } ;
struct icom_port {int /*<<< orphan*/ * xmitRestart; int /*<<< orphan*/  xmitRestart_pci; int /*<<< orphan*/ * statStg; int /*<<< orphan*/  statStg_pci; int /*<<< orphan*/ * xmit_buf; int /*<<< orphan*/  xmit_buf_pci; int /*<<< orphan*/ * recv_buf; int /*<<< orphan*/  recv_buf_pci; TYPE_1__* adapter; } ;
struct TYPE_2__ {struct pci_dev* pci_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_free_consistent (struct pci_dev*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace (struct icom_port*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_port_memory(struct icom_port *icom_port)
{
	struct pci_dev *dev = icom_port->adapter->pci_dev;

	trace(icom_port, "RET_PORT_MEM", 0);
	if (icom_port->recv_buf) {
		pci_free_consistent(dev, 4096, icom_port->recv_buf,
				    icom_port->recv_buf_pci);
		icom_port->recv_buf = NULL;
	}
	if (icom_port->xmit_buf) {
		pci_free_consistent(dev, 4096, icom_port->xmit_buf,
				    icom_port->xmit_buf_pci);
		icom_port->xmit_buf = NULL;
	}
	if (icom_port->statStg) {
		pci_free_consistent(dev, 4096, icom_port->statStg,
				    icom_port->statStg_pci);
		icom_port->statStg = NULL;
	}

	if (icom_port->xmitRestart) {
		pci_free_consistent(dev, 4096, icom_port->xmitRestart,
				    icom_port->xmitRestart_pci);
		icom_port->xmitRestart = NULL;
	}
}