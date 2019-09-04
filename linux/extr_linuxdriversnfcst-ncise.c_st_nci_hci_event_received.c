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
typedef  size_t u8 ;
struct sk_buff {int dummy; } ;
struct nci_dev {TYPE_2__* hci_dev; } ;
struct TYPE_4__ {TYPE_1__* pipes; } ;
struct TYPE_3__ {size_t gate; size_t host; } ;

/* Variables and functions */
#define  NCI_HCI_ADMIN_GATE 130 
#define  ST_NCI_APDU_READER_GATE 129 
#define  ST_NCI_CONNECTIVITY_GATE 128 
 int /*<<< orphan*/  st_nci_hci_admin_event_received (struct nci_dev*,size_t,struct sk_buff*) ; 
 int /*<<< orphan*/  st_nci_hci_apdu_reader_event_received (struct nci_dev*,size_t,struct sk_buff*) ; 
 int /*<<< orphan*/  st_nci_hci_connectivity_event_received (struct nci_dev*,size_t,size_t,struct sk_buff*) ; 

void st_nci_hci_event_received(struct nci_dev *ndev, u8 pipe,
				 u8 event, struct sk_buff *skb)
{
	u8 gate = ndev->hci_dev->pipes[pipe].gate;
	u8 host = ndev->hci_dev->pipes[pipe].host;

	switch (gate) {
	case NCI_HCI_ADMIN_GATE:
		st_nci_hci_admin_event_received(ndev, event, skb);
	break;
	case ST_NCI_APDU_READER_GATE:
		st_nci_hci_apdu_reader_event_received(ndev, event, skb);
	break;
	case ST_NCI_CONNECTIVITY_GATE:
		st_nci_hci_connectivity_event_received(ndev, host, event, skb);
	break;
	}
}