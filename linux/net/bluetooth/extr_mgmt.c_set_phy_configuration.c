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
typedef  int u32 ;
typedef  int u16 ;
struct sock {int dummy; } ;
struct mgmt_pending_cmd {int dummy; } ;
struct mgmt_cp_set_phy_confguration {int /*<<< orphan*/  selected_phys; } ;
struct hci_request {int dummy; } ;
struct hci_dev {int pkt_type; int /*<<< orphan*/  id; int /*<<< orphan*/  name; } ;
struct hci_cp_le_set_default_phy {int all_phys; int /*<<< orphan*/  rx_phys; int /*<<< orphan*/  tx_phys; } ;
typedef  int /*<<< orphan*/  cp_phy ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct sock*,int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int HCI_2DH1 ; 
 int HCI_2DH3 ; 
 int HCI_2DH5 ; 
 int HCI_3DH1 ; 
 int HCI_3DH3 ; 
 int HCI_3DH5 ; 
 int HCI_DH1 ; 
 int HCI_DH3 ; 
 int HCI_DH5 ; 
 int HCI_DM1 ; 
 int HCI_DM3 ; 
 int HCI_DM5 ; 
 int /*<<< orphan*/  HCI_LE_SET_PHY_1M ; 
 int /*<<< orphan*/  HCI_LE_SET_PHY_2M ; 
 int /*<<< orphan*/  HCI_LE_SET_PHY_CODED ; 
 int /*<<< orphan*/  HCI_OP_LE_SET_DEFAULT_PHY ; 
 int /*<<< orphan*/  MGMT_OP_SET_PHY_CONFIGURATION ; 
 int MGMT_PHY_BR_1M_3SLOT ; 
 int MGMT_PHY_BR_1M_5SLOT ; 
 int MGMT_PHY_EDR_2M_1SLOT ; 
 int MGMT_PHY_EDR_2M_3SLOT ; 
 int MGMT_PHY_EDR_2M_5SLOT ; 
 int MGMT_PHY_EDR_3M_1SLOT ; 
 int MGMT_PHY_EDR_3M_3SLOT ; 
 int MGMT_PHY_EDR_3M_5SLOT ; 
 int MGMT_PHY_LE_1M_RX ; 
 int MGMT_PHY_LE_1M_TX ; 
 int MGMT_PHY_LE_2M_RX ; 
 int MGMT_PHY_LE_2M_TX ; 
 int MGMT_PHY_LE_CODED_RX ; 
 int MGMT_PHY_LE_CODED_TX ; 
 int MGMT_PHY_LE_MASK ; 
 int MGMT_PHY_LE_RX_MASK ; 
 int MGMT_PHY_LE_TX_MASK ; 
 int /*<<< orphan*/  MGMT_STATUS_BUSY ; 
 int /*<<< orphan*/  MGMT_STATUS_INVALID_PARAMS ; 
 int /*<<< orphan*/  MGMT_STATUS_REJECTED ; 
 int __le32_to_cpu (int /*<<< orphan*/ ) ; 
 int get_configurable_phys (struct hci_dev*) ; 
 int get_selected_phys (struct hci_dev*) ; 
 int get_supported_phys (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_dev_lock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_dev_unlock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_req_add (struct hci_request*,int /*<<< orphan*/ ,int,struct hci_cp_le_set_default_phy*) ; 
 int /*<<< orphan*/  hci_req_init (struct hci_request*,struct hci_dev*) ; 
 int hci_req_run_skb (struct hci_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdev_is_powered (struct hci_dev*) ; 
 int /*<<< orphan*/  memset (struct hci_cp_le_set_default_phy*,int /*<<< orphan*/ ,int) ; 
 int mgmt_cmd_complete (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int mgmt_cmd_status (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mgmt_pending_cmd* mgmt_pending_add (struct sock*,int /*<<< orphan*/ ,struct hci_dev*,void*,int) ; 
 int /*<<< orphan*/  mgmt_pending_remove (struct mgmt_pending_cmd*) ; 
 int /*<<< orphan*/  mgmt_phy_configuration_changed (struct hci_dev*,struct sock*) ; 
 scalar_t__ pending_find (int /*<<< orphan*/ ,struct hci_dev*) ; 
 int /*<<< orphan*/  set_default_phy_complete ; 

__attribute__((used)) static int set_phy_configuration(struct sock *sk, struct hci_dev *hdev,
				 void *data, u16 len)
{
	struct mgmt_cp_set_phy_confguration *cp = data;
	struct hci_cp_le_set_default_phy cp_phy;
	struct mgmt_pending_cmd *cmd;
	struct hci_request req;
	u32 selected_phys, configurable_phys, supported_phys, unconfigure_phys;
	u16 pkt_type = (HCI_DH1 | HCI_DM1);
	bool changed = false;
	int err;

	BT_DBG("sock %p %s", sk, hdev->name);

	configurable_phys = get_configurable_phys(hdev);
	supported_phys = get_supported_phys(hdev);
	selected_phys = __le32_to_cpu(cp->selected_phys);

	if (selected_phys & ~supported_phys)
		return mgmt_cmd_status(sk, hdev->id,
				       MGMT_OP_SET_PHY_CONFIGURATION,
				       MGMT_STATUS_INVALID_PARAMS);

	unconfigure_phys = supported_phys & ~configurable_phys;

	if ((selected_phys & unconfigure_phys) != unconfigure_phys)
		return mgmt_cmd_status(sk, hdev->id,
				       MGMT_OP_SET_PHY_CONFIGURATION,
				       MGMT_STATUS_INVALID_PARAMS);

	if (selected_phys == get_selected_phys(hdev))
		return mgmt_cmd_complete(sk, hdev->id,
					 MGMT_OP_SET_PHY_CONFIGURATION,
					 0, NULL, 0);

	hci_dev_lock(hdev);

	if (!hdev_is_powered(hdev)) {
		err = mgmt_cmd_status(sk, hdev->id,
				      MGMT_OP_SET_PHY_CONFIGURATION,
				      MGMT_STATUS_REJECTED);
		goto unlock;
	}

	if (pending_find(MGMT_OP_SET_PHY_CONFIGURATION, hdev)) {
		err = mgmt_cmd_status(sk, hdev->id,
				      MGMT_OP_SET_PHY_CONFIGURATION,
				      MGMT_STATUS_BUSY);
		goto unlock;
	}

	if (selected_phys & MGMT_PHY_BR_1M_3SLOT)
		pkt_type |= (HCI_DH3 | HCI_DM3);
	else
		pkt_type &= ~(HCI_DH3 | HCI_DM3);

	if (selected_phys & MGMT_PHY_BR_1M_5SLOT)
		pkt_type |= (HCI_DH5 | HCI_DM5);
	else
		pkt_type &= ~(HCI_DH5 | HCI_DM5);

	if (selected_phys & MGMT_PHY_EDR_2M_1SLOT)
		pkt_type &= ~HCI_2DH1;
	else
		pkt_type |= HCI_2DH1;

	if (selected_phys & MGMT_PHY_EDR_2M_3SLOT)
		pkt_type &= ~HCI_2DH3;
	else
		pkt_type |= HCI_2DH3;

	if (selected_phys & MGMT_PHY_EDR_2M_5SLOT)
		pkt_type &= ~HCI_2DH5;
	else
		pkt_type |= HCI_2DH5;

	if (selected_phys & MGMT_PHY_EDR_3M_1SLOT)
		pkt_type &= ~HCI_3DH1;
	else
		pkt_type |= HCI_3DH1;

	if (selected_phys & MGMT_PHY_EDR_3M_3SLOT)
		pkt_type &= ~HCI_3DH3;
	else
		pkt_type |= HCI_3DH3;

	if (selected_phys & MGMT_PHY_EDR_3M_5SLOT)
		pkt_type &= ~HCI_3DH5;
	else
		pkt_type |= HCI_3DH5;

	if (pkt_type != hdev->pkt_type) {
		hdev->pkt_type = pkt_type;
		changed = true;
	}

	if ((selected_phys & MGMT_PHY_LE_MASK) ==
	    (get_selected_phys(hdev) & MGMT_PHY_LE_MASK)) {
		if (changed)
			mgmt_phy_configuration_changed(hdev, sk);

		err = mgmt_cmd_complete(sk, hdev->id,
					MGMT_OP_SET_PHY_CONFIGURATION,
					0, NULL, 0);

		goto unlock;
	}

	cmd = mgmt_pending_add(sk, MGMT_OP_SET_PHY_CONFIGURATION, hdev, data,
			       len);
	if (!cmd) {
		err = -ENOMEM;
		goto unlock;
	}

	hci_req_init(&req, hdev);

	memset(&cp_phy, 0, sizeof(cp_phy));

	if (!(selected_phys & MGMT_PHY_LE_TX_MASK))
		cp_phy.all_phys |= 0x01;

	if (!(selected_phys & MGMT_PHY_LE_RX_MASK))
		cp_phy.all_phys |= 0x02;

	if (selected_phys & MGMT_PHY_LE_1M_TX)
		cp_phy.tx_phys |= HCI_LE_SET_PHY_1M;

	if (selected_phys & MGMT_PHY_LE_2M_TX)
		cp_phy.tx_phys |= HCI_LE_SET_PHY_2M;

	if (selected_phys & MGMT_PHY_LE_CODED_TX)
		cp_phy.tx_phys |= HCI_LE_SET_PHY_CODED;

	if (selected_phys & MGMT_PHY_LE_1M_RX)
		cp_phy.rx_phys |= HCI_LE_SET_PHY_1M;

	if (selected_phys & MGMT_PHY_LE_2M_RX)
		cp_phy.rx_phys |= HCI_LE_SET_PHY_2M;

	if (selected_phys & MGMT_PHY_LE_CODED_RX)
		cp_phy.rx_phys |= HCI_LE_SET_PHY_CODED;

	hci_req_add(&req, HCI_OP_LE_SET_DEFAULT_PHY, sizeof(cp_phy), &cp_phy);

	err = hci_req_run_skb(&req, set_default_phy_complete);
	if (err < 0)
		mgmt_pending_remove(cmd);

unlock:
	hci_dev_unlock(hdev);

	return err;
}