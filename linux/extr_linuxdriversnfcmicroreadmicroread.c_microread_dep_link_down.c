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
struct nfc_hci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MICROREAD_EVT_MREAD_DISCOVERY_STOP ; 
 int /*<<< orphan*/  MICROREAD_GATE_ID_P2P_INITIATOR ; 
 int nfc_hci_send_event (struct nfc_hci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int microread_dep_link_down(struct nfc_hci_dev *hdev)
{
	return nfc_hci_send_event(hdev, MICROREAD_GATE_ID_P2P_INITIATOR,
				  MICROREAD_EVT_MREAD_DISCOVERY_STOP, NULL, 0);
}