#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {int /*<<< orphan*/  devfn; int /*<<< orphan*/  subsystem_device; int /*<<< orphan*/  subsystem_vendor; int /*<<< orphan*/  device; int /*<<< orphan*/  vendor; int /*<<< orphan*/  dev; } ;
struct hpi_response {int dummy; } ;
struct hpi_pci {int /*<<< orphan*/ * ap_mem_base; } ;
struct TYPE_5__ {scalar_t__ parameter2; scalar_t__ parameter1; int /*<<< orphan*/  property; } ;
struct TYPE_6__ {TYPE_1__ property_set; } ;
struct TYPE_7__ {TYPE_2__ ax; } ;
struct hpi_message {int /*<<< orphan*/  adapter_index; TYPE_3__ u; } ;
struct hpi_adapter {TYPE_4__* adapter; int /*<<< orphan*/  p_buffer; scalar_t__ irq; } ;
struct TYPE_8__ {int /*<<< orphan*/  index; struct hpi_pci pci; } ;

/* Variables and functions */
 int /*<<< orphan*/  HOWNER_KERNEL ; 
 int /*<<< orphan*/  HPI_ADAPTER_DELETE ; 
 int /*<<< orphan*/  HPI_ADAPTER_PROPERTY_IRQ_RATE ; 
 int /*<<< orphan*/  HPI_ADAPTER_SET_PROPERTY ; 
 int HPI_MAX_ADAPTER_MEM_SPACES ; 
 int /*<<< orphan*/  HPI_OBJ_ADAPTER ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct hpi_adapter*) ; 
 int /*<<< orphan*/  hpi_init_message_response (struct hpi_message*,struct hpi_response*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpi_send_recv_ex (struct hpi_message*,struct hpi_response*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct hpi_adapter*,int /*<<< orphan*/ ,int) ; 
 struct hpi_adapter* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ ) ; 

void asihpi_adapter_remove(struct pci_dev *pci_dev)
{
	int idx;
	struct hpi_message hm;
	struct hpi_response hr;
	struct hpi_adapter *pa;
	struct hpi_pci pci;

	pa = pci_get_drvdata(pci_dev);
	pci = pa->adapter->pci;

	/* Disable IRQ generation on DSP side */
	hpi_init_message_response(&hm, &hr, HPI_OBJ_ADAPTER,
		HPI_ADAPTER_SET_PROPERTY);
	hm.adapter_index = pa->adapter->index;
	hm.u.ax.property_set.property = HPI_ADAPTER_PROPERTY_IRQ_RATE;
	hm.u.ax.property_set.parameter1 = 0;
	hm.u.ax.property_set.parameter2 = 0;
	hpi_send_recv_ex(&hm, &hr, HOWNER_KERNEL);

	hpi_init_message_response(&hm, &hr, HPI_OBJ_ADAPTER,
		HPI_ADAPTER_DELETE);
	hm.adapter_index = pa->adapter->index;
	hpi_send_recv_ex(&hm, &hr, HOWNER_KERNEL);

	/* unmap PCI memory space, mapped during device init. */
	for (idx = 0; idx < HPI_MAX_ADAPTER_MEM_SPACES; ++idx)
		iounmap(pci.ap_mem_base[idx]);

	if (pa->irq)
		free_irq(pa->irq, pa);

	vfree(pa->p_buffer);

	if (1)
		dev_info(&pci_dev->dev,
			 "remove %04x:%04x,%04x:%04x,%04x, HPI index %d\n",
			 pci_dev->vendor, pci_dev->device,
			 pci_dev->subsystem_vendor, pci_dev->subsystem_device,
			 pci_dev->devfn, pa->adapter->index);

	memset(pa, 0, sizeof(*pa));
}