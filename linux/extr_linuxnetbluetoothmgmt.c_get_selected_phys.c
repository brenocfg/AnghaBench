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
struct hci_dev {int pkt_type; int le_tx_def_phys; int le_rx_def_phys; } ;

/* Variables and functions */
 int HCI_2DH1 ; 
 int HCI_2DH3 ; 
 int HCI_2DH5 ; 
 int HCI_3DH1 ; 
 int HCI_3DH3 ; 
 int HCI_3DH5 ; 
 int HCI_DH3 ; 
 int HCI_DH5 ; 
 int HCI_DM3 ; 
 int HCI_DM5 ; 
 int HCI_LE_SET_PHY_1M ; 
 int HCI_LE_SET_PHY_2M ; 
 int HCI_LE_SET_PHY_CODED ; 
 int /*<<< orphan*/  MGMT_PHY_BR_1M_1SLOT ; 
 int /*<<< orphan*/  MGMT_PHY_BR_1M_3SLOT ; 
 int /*<<< orphan*/  MGMT_PHY_BR_1M_5SLOT ; 
 int /*<<< orphan*/  MGMT_PHY_EDR_2M_1SLOT ; 
 int /*<<< orphan*/  MGMT_PHY_EDR_2M_3SLOT ; 
 int /*<<< orphan*/  MGMT_PHY_EDR_2M_5SLOT ; 
 int /*<<< orphan*/  MGMT_PHY_EDR_3M_1SLOT ; 
 int /*<<< orphan*/  MGMT_PHY_EDR_3M_3SLOT ; 
 int /*<<< orphan*/  MGMT_PHY_EDR_3M_5SLOT ; 
 int /*<<< orphan*/  MGMT_PHY_LE_1M_RX ; 
 int /*<<< orphan*/  MGMT_PHY_LE_1M_TX ; 
 int /*<<< orphan*/  MGMT_PHY_LE_2M_RX ; 
 int /*<<< orphan*/  MGMT_PHY_LE_2M_TX ; 
 int /*<<< orphan*/  MGMT_PHY_LE_CODED_RX ; 
 int /*<<< orphan*/  MGMT_PHY_LE_CODED_TX ; 
 scalar_t__ lmp_bredr_capable (struct hci_dev*) ; 
 scalar_t__ lmp_edr_2m_capable (struct hci_dev*) ; 
 scalar_t__ lmp_edr_3m_capable (struct hci_dev*) ; 
 scalar_t__ lmp_edr_3slot_capable (struct hci_dev*) ; 
 scalar_t__ lmp_edr_5slot_capable (struct hci_dev*) ; 
 scalar_t__ lmp_le_capable (struct hci_dev*) ; 

__attribute__((used)) static u32 get_selected_phys(struct hci_dev *hdev)
{
	u32 selected_phys = 0;

	if (lmp_bredr_capable(hdev)) {
		selected_phys |= MGMT_PHY_BR_1M_1SLOT;

		if (hdev->pkt_type & (HCI_DM3 | HCI_DH3))
			selected_phys |= MGMT_PHY_BR_1M_3SLOT;

		if (hdev->pkt_type & (HCI_DM5 | HCI_DH5))
			selected_phys |= MGMT_PHY_BR_1M_5SLOT;

		if (lmp_edr_2m_capable(hdev)) {
			if (!(hdev->pkt_type & HCI_2DH1))
				selected_phys |= MGMT_PHY_EDR_2M_1SLOT;

			if (lmp_edr_3slot_capable(hdev) &&
			    !(hdev->pkt_type & HCI_2DH3))
				selected_phys |= MGMT_PHY_EDR_2M_3SLOT;

			if (lmp_edr_5slot_capable(hdev) &&
			    !(hdev->pkt_type & HCI_2DH5))
				selected_phys |= MGMT_PHY_EDR_2M_5SLOT;

			if (lmp_edr_3m_capable(hdev)) {
				if (!(hdev->pkt_type & HCI_3DH1))
					selected_phys |= MGMT_PHY_EDR_3M_1SLOT;

				if (lmp_edr_3slot_capable(hdev) &&
				    !(hdev->pkt_type & HCI_3DH3))
					selected_phys |= MGMT_PHY_EDR_3M_3SLOT;

				if (lmp_edr_5slot_capable(hdev) &&
				    !(hdev->pkt_type & HCI_3DH5))
					selected_phys |= MGMT_PHY_EDR_3M_5SLOT;
			}
		}
	}

	if (lmp_le_capable(hdev)) {
		if (hdev->le_tx_def_phys & HCI_LE_SET_PHY_1M)
			selected_phys |= MGMT_PHY_LE_1M_TX;

		if (hdev->le_rx_def_phys & HCI_LE_SET_PHY_1M)
			selected_phys |= MGMT_PHY_LE_1M_RX;

		if (hdev->le_tx_def_phys & HCI_LE_SET_PHY_2M)
			selected_phys |= MGMT_PHY_LE_2M_TX;

		if (hdev->le_rx_def_phys & HCI_LE_SET_PHY_2M)
			selected_phys |= MGMT_PHY_LE_2M_RX;

		if (hdev->le_tx_def_phys & HCI_LE_SET_PHY_CODED)
			selected_phys |= MGMT_PHY_LE_CODED_TX;

		if (hdev->le_rx_def_phys & HCI_LE_SET_PHY_CODED)
			selected_phys |= MGMT_PHY_LE_CODED_RX;
	}

	return selected_phys;
}