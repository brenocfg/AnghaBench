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
struct l2cap_chan {int /*<<< orphan*/  remote_flush_to; int /*<<< orphan*/  remote_acc_lat; int /*<<< orphan*/  remote_sdu_itime; int /*<<< orphan*/  remote_msdu; int /*<<< orphan*/  remote_stype; int /*<<< orphan*/  remote_id; int /*<<< orphan*/  local_flush_to; int /*<<< orphan*/  local_acc_lat; int /*<<< orphan*/  local_sdu_itime; int /*<<< orphan*/  local_msdu; int /*<<< orphan*/  local_stype; int /*<<< orphan*/  local_id; struct hci_conn* hs_hcon; TYPE_2__* conn; } ;
struct hci_dev {int dummy; } ;
struct TYPE_8__ {void* flush_to; void* acc_lat; void* sdu_itime; void* msdu; int /*<<< orphan*/  stype; int /*<<< orphan*/  id; } ;
struct TYPE_7__ {void* flush_to; void* acc_lat; void* sdu_itime; void* msdu; int /*<<< orphan*/  stype; int /*<<< orphan*/  id; } ;
struct hci_cp_create_accept_logical_link {TYPE_4__ rx_flow_spec; TYPE_3__ tx_flow_spec; int /*<<< orphan*/  phy_handle; } ;
struct hci_conn {scalar_t__ out; int /*<<< orphan*/  handle; int /*<<< orphan*/  hdev; } ;
typedef  int /*<<< orphan*/  cp ;
struct TYPE_6__ {TYPE_1__* hcon; } ;
struct TYPE_5__ {int /*<<< orphan*/  dst; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct l2cap_chan*,struct hci_conn*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HCI_OP_ACCEPT_LOGICAL_LINK ; 
 int /*<<< orphan*/  HCI_OP_CREATE_LOGICAL_LINK ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 struct hci_dev* hci_dev_hold (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_dev_put (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_send_cmd (struct hci_dev*,int /*<<< orphan*/ ,int,struct hci_cp_create_accept_logical_link*) ; 

void amp_create_logical_link(struct l2cap_chan *chan)
{
	struct hci_conn *hs_hcon = chan->hs_hcon;
	struct hci_cp_create_accept_logical_link cp;
	struct hci_dev *hdev;

	BT_DBG("chan %p hs_hcon %p dst %pMR", chan, hs_hcon,
	       &chan->conn->hcon->dst);

	if (!hs_hcon)
		return;

	hdev = hci_dev_hold(chan->hs_hcon->hdev);
	if (!hdev)
		return;

	cp.phy_handle = hs_hcon->handle;

	cp.tx_flow_spec.id = chan->local_id;
	cp.tx_flow_spec.stype = chan->local_stype;
	cp.tx_flow_spec.msdu = cpu_to_le16(chan->local_msdu);
	cp.tx_flow_spec.sdu_itime = cpu_to_le32(chan->local_sdu_itime);
	cp.tx_flow_spec.acc_lat = cpu_to_le32(chan->local_acc_lat);
	cp.tx_flow_spec.flush_to = cpu_to_le32(chan->local_flush_to);

	cp.rx_flow_spec.id = chan->remote_id;
	cp.rx_flow_spec.stype = chan->remote_stype;
	cp.rx_flow_spec.msdu = cpu_to_le16(chan->remote_msdu);
	cp.rx_flow_spec.sdu_itime = cpu_to_le32(chan->remote_sdu_itime);
	cp.rx_flow_spec.acc_lat = cpu_to_le32(chan->remote_acc_lat);
	cp.rx_flow_spec.flush_to = cpu_to_le32(chan->remote_flush_to);

	if (hs_hcon->out)
		hci_send_cmd(hdev, HCI_OP_CREATE_LOGICAL_LINK, sizeof(cp),
			     &cp);
	else
		hci_send_cmd(hdev, HCI_OP_ACCEPT_LOGICAL_LINK, sizeof(cp),
			     &cp);

	hci_dev_put(hdev);
}