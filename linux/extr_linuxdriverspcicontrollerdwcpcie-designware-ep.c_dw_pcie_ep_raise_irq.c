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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct pci_epc {int dummy; } ;
struct dw_pcie_ep {TYPE_1__* ops; } ;
typedef  enum pci_epc_irq_type { ____Placeholder_pci_epc_irq_type } pci_epc_irq_type ;
struct TYPE_2__ {int (* raise_irq ) (struct dw_pcie_ep*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EINVAL ; 
 struct dw_pcie_ep* epc_get_drvdata (struct pci_epc*) ; 
 int stub1 (struct dw_pcie_ep*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dw_pcie_ep_raise_irq(struct pci_epc *epc, u8 func_no,
				enum pci_epc_irq_type type, u16 interrupt_num)
{
	struct dw_pcie_ep *ep = epc_get_drvdata(epc);

	if (!ep->ops->raise_irq)
		return -EINVAL;

	return ep->ops->raise_irq(ep, func_no, type, interrupt_num);
}