#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_10__ {int /*<<< orphan*/  slot; } ;
struct TYPE_9__ {int /*<<< orphan*/  type; } ;
struct pci_resources_assigned2 {TYPE_4__ wslot; TYPE_3__ message_type; } ;
struct TYPE_8__ {int /*<<< orphan*/  slot; } ;
struct TYPE_7__ {int /*<<< orphan*/  type; } ;
struct pci_resources_assigned {TYPE_2__ wslot; TYPE_1__ message_type; } ;
struct pci_packet {int /*<<< orphan*/  message; struct hv_pci_compl* compl_ctxt; int /*<<< orphan*/  completion_func; } ;
struct hv_pcibus_device {int dummy; } ;
struct TYPE_11__ {int /*<<< orphan*/  slot; } ;
struct TYPE_12__ {TYPE_5__ win_slot; } ;
struct hv_pci_dev {TYPE_6__ desc; } ;
struct hv_pci_compl {scalar_t__ completion_status; int /*<<< orphan*/  host_event; } ;
struct hv_device {int /*<<< orphan*/  device; int /*<<< orphan*/  channel; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EPROTO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ PCI_PROTOCOL_VERSION_1_2 ; 
 int /*<<< orphan*/  PCI_RESOURCES_ASSIGNED ; 
 int /*<<< orphan*/  PCI_RESOURCES_ASSIGNED2 ; 
 int /*<<< orphan*/  VMBUS_DATA_PACKET_FLAG_COMPLETION_REQUESTED ; 
 int /*<<< orphan*/  VM_PKT_DATA_INBAND ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 struct hv_pci_dev* get_pcichild_wslot (struct hv_pcibus_device*,int) ; 
 struct hv_pcibus_device* hv_get_drvdata (struct hv_device*) ; 
 int /*<<< orphan*/  hv_pci_generic_compl ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct pci_packet*) ; 
 struct pci_packet* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct pci_packet*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ pci_protocol_version ; 
 int /*<<< orphan*/  put_pcichild (struct hv_pci_dev*) ; 
 int vmbus_sendpacket (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int wait_for_response (struct hv_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hv_send_resources_allocated(struct hv_device *hdev)
{
	struct hv_pcibus_device *hbus = hv_get_drvdata(hdev);
	struct pci_resources_assigned *res_assigned;
	struct pci_resources_assigned2 *res_assigned2;
	struct hv_pci_compl comp_pkt;
	struct hv_pci_dev *hpdev;
	struct pci_packet *pkt;
	size_t size_res;
	u32 wslot;
	int ret;

	size_res = (pci_protocol_version < PCI_PROTOCOL_VERSION_1_2)
			? sizeof(*res_assigned) : sizeof(*res_assigned2);

	pkt = kmalloc(sizeof(*pkt) + size_res, GFP_KERNEL);
	if (!pkt)
		return -ENOMEM;

	ret = 0;

	for (wslot = 0; wslot < 256; wslot++) {
		hpdev = get_pcichild_wslot(hbus, wslot);
		if (!hpdev)
			continue;

		memset(pkt, 0, sizeof(*pkt) + size_res);
		init_completion(&comp_pkt.host_event);
		pkt->completion_func = hv_pci_generic_compl;
		pkt->compl_ctxt = &comp_pkt;

		if (pci_protocol_version < PCI_PROTOCOL_VERSION_1_2) {
			res_assigned =
				(struct pci_resources_assigned *)&pkt->message;
			res_assigned->message_type.type =
				PCI_RESOURCES_ASSIGNED;
			res_assigned->wslot.slot = hpdev->desc.win_slot.slot;
		} else {
			res_assigned2 =
				(struct pci_resources_assigned2 *)&pkt->message;
			res_assigned2->message_type.type =
				PCI_RESOURCES_ASSIGNED2;
			res_assigned2->wslot.slot = hpdev->desc.win_slot.slot;
		}
		put_pcichild(hpdev);

		ret = vmbus_sendpacket(hdev->channel, &pkt->message,
				size_res, (unsigned long)pkt,
				VM_PKT_DATA_INBAND,
				VMBUS_DATA_PACKET_FLAG_COMPLETION_REQUESTED);
		if (!ret)
			ret = wait_for_response(hdev, &comp_pkt.host_event);
		if (ret)
			break;

		if (comp_pkt.completion_status < 0) {
			ret = -EPROTO;
			dev_err(&hdev->device,
				"resource allocated returned 0x%x",
				comp_pkt.completion_status);
			break;
		}
	}

	kfree(pkt);
	return ret;
}