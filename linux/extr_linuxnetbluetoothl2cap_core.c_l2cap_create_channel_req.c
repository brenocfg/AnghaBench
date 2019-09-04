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
typedef  int u16 ;
struct l2cap_create_chan_rsp {void* status; void* result; void* scid; scalar_t__ dcid; } ;
struct l2cap_create_chan_req {scalar_t__ amp_id; int /*<<< orphan*/  scid; int /*<<< orphan*/  psm; } ;
struct l2cap_conn {int local_fixed_chan; int /*<<< orphan*/  mtu; TYPE_1__* hcon; } ;
struct l2cap_cmd_hdr {int /*<<< orphan*/  ident; } ;
struct l2cap_chan {int /*<<< orphan*/  fcs; struct hci_conn* hs_hcon; int /*<<< orphan*/  dcid; int /*<<< orphan*/  scid; } ;
struct hci_dev {scalar_t__ dev_type; int /*<<< orphan*/  block_mtu; int /*<<< orphan*/  flags; } ;
struct hci_conn {int dummy; } ;
struct amp_mgr {struct l2cap_chan* bredr_chan; } ;
typedef  int /*<<< orphan*/  rsp ;
struct TYPE_2__ {int /*<<< orphan*/  dst; struct amp_mgr* amp_mgr; } ;

/* Variables and functions */
 scalar_t__ AMP_ID_BREDR ; 
 int /*<<< orphan*/  AMP_LINK ; 
 int /*<<< orphan*/  BT_DBG (char*,...) ; 
 int EINVAL ; 
 int EPROTO ; 
 scalar_t__ HCI_AMP ; 
 int /*<<< orphan*/  HCI_UP ; 
 int /*<<< orphan*/  L2CAP_CREATE_CHAN_RSP ; 
 int L2CAP_CR_BAD_AMP ; 
 int L2CAP_CS_NO_INFO ; 
 int /*<<< orphan*/  L2CAP_FCS_NONE ; 
 int L2CAP_FC_A2MP ; 
 int /*<<< orphan*/  cmd_reject_invalid_cid (struct l2cap_conn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* cpu_to_le16 (int) ; 
 struct hci_conn* hci_conn_hash_lookup_ba (struct hci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct hci_dev* hci_dev_get (scalar_t__) ; 
 int /*<<< orphan*/  hci_dev_put (struct hci_dev*) ; 
 struct l2cap_chan* l2cap_connect (struct l2cap_conn*,struct l2cap_cmd_hdr*,void*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  l2cap_send_cmd (struct l2cap_conn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct l2cap_create_chan_rsp*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int l2cap_create_channel_req(struct l2cap_conn *conn,
				    struct l2cap_cmd_hdr *cmd,
				    u16 cmd_len, void *data)
{
	struct l2cap_create_chan_req *req = data;
	struct l2cap_create_chan_rsp rsp;
	struct l2cap_chan *chan;
	struct hci_dev *hdev;
	u16 psm, scid;

	if (cmd_len != sizeof(*req))
		return -EPROTO;

	if (!(conn->local_fixed_chan & L2CAP_FC_A2MP))
		return -EINVAL;

	psm = le16_to_cpu(req->psm);
	scid = le16_to_cpu(req->scid);

	BT_DBG("psm 0x%2.2x, scid 0x%4.4x, amp_id %d", psm, scid, req->amp_id);

	/* For controller id 0 make BR/EDR connection */
	if (req->amp_id == AMP_ID_BREDR) {
		l2cap_connect(conn, cmd, data, L2CAP_CREATE_CHAN_RSP,
			      req->amp_id);
		return 0;
	}

	/* Validate AMP controller id */
	hdev = hci_dev_get(req->amp_id);
	if (!hdev)
		goto error;

	if (hdev->dev_type != HCI_AMP || !test_bit(HCI_UP, &hdev->flags)) {
		hci_dev_put(hdev);
		goto error;
	}

	chan = l2cap_connect(conn, cmd, data, L2CAP_CREATE_CHAN_RSP,
			     req->amp_id);
	if (chan) {
		struct amp_mgr *mgr = conn->hcon->amp_mgr;
		struct hci_conn *hs_hcon;

		hs_hcon = hci_conn_hash_lookup_ba(hdev, AMP_LINK,
						  &conn->hcon->dst);
		if (!hs_hcon) {
			hci_dev_put(hdev);
			cmd_reject_invalid_cid(conn, cmd->ident, chan->scid,
					       chan->dcid);
			return 0;
		}

		BT_DBG("mgr %p bredr_chan %p hs_hcon %p", mgr, chan, hs_hcon);

		mgr->bredr_chan = chan;
		chan->hs_hcon = hs_hcon;
		chan->fcs = L2CAP_FCS_NONE;
		conn->mtu = hdev->block_mtu;
	}

	hci_dev_put(hdev);

	return 0;

error:
	rsp.dcid = 0;
	rsp.scid = cpu_to_le16(scid);
	rsp.result = cpu_to_le16(L2CAP_CR_BAD_AMP);
	rsp.status = cpu_to_le16(L2CAP_CS_NO_INFO);

	l2cap_send_cmd(conn, cmd->ident, L2CAP_CREATE_CHAN_RSP,
		       sizeof(rsp), &rsp);

	return 0;
}