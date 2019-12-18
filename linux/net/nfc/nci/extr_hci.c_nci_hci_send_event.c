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
typedef  size_t u8 ;
struct nci_dev {TYPE_1__* hci_dev; } ;
struct TYPE_2__ {size_t* gate2pipe; } ;

/* Variables and functions */
 int EADDRNOTAVAIL ; 
 int /*<<< orphan*/  NCI_HCI_HCP_EVENT ; 
 size_t NCI_HCI_INVALID_PIPE ; 
 int /*<<< orphan*/  NCI_HCP_HEADER (int /*<<< orphan*/ ,size_t) ; 
 int nci_hci_send_data (struct nci_dev*,size_t,int /*<<< orphan*/ ,size_t const*,size_t) ; 

int nci_hci_send_event(struct nci_dev *ndev, u8 gate, u8 event,
		       const u8 *param, size_t param_len)
{
	u8 pipe = ndev->hci_dev->gate2pipe[gate];

	if (pipe == NCI_HCI_INVALID_PIPE)
		return -EADDRNOTAVAIL;

	return nci_hci_send_data(ndev, pipe,
			NCI_HCP_HEADER(NCI_HCI_HCP_EVENT, event),
			param, param_len);
}