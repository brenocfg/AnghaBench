#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct l2cap_conn {int local_fixed_chan; int /*<<< orphan*/  disc_reason; int /*<<< orphan*/  id_addr_update_work; int /*<<< orphan*/  pending_rx_work; int /*<<< orphan*/  pending_rx; int /*<<< orphan*/  info_timer; int /*<<< orphan*/  users; int /*<<< orphan*/  chan_l; int /*<<< orphan*/  chan_lock; int /*<<< orphan*/  ident_lock; scalar_t__ feat_mask; int /*<<< orphan*/  mtu; struct hci_chan* hchan; int /*<<< orphan*/  hcon; int /*<<< orphan*/  ref; } ;
struct hci_conn {int type; TYPE_1__* hdev; struct l2cap_conn* l2cap_data; } ;
struct hci_chan {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  acl_mtu; int /*<<< orphan*/  le_mtu; } ;

/* Variables and functions */
 int ACL_LINK ; 
 int /*<<< orphan*/  BT_DBG (char*,struct hci_conn*,struct l2cap_conn*,struct hci_chan*) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HCI_ERROR_REMOTE_USER_TERM ; 
 int /*<<< orphan*/  HCI_FORCE_BREDR_SMP ; 
 int /*<<< orphan*/  HCI_HS_ENABLED ; 
 int /*<<< orphan*/  HCI_LE_ENABLED ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int L2CAP_FC_A2MP ; 
 int L2CAP_FC_CONNLESS ; 
 int L2CAP_FC_SIG_BREDR ; 
 int L2CAP_FC_SMP_BREDR ; 
#define  LE_LINK 128 
 scalar_t__ bredr_sc_enabled (TYPE_1__*) ; 
 struct hci_chan* hci_chan_create (struct hci_conn*) ; 
 int /*<<< orphan*/  hci_chan_del (struct hci_chan*) ; 
 int /*<<< orphan*/  hci_conn_get (struct hci_conn*) ; 
 scalar_t__ hci_dev_test_flag (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct l2cap_conn* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2cap_conn_update_id_addr ; 
 int /*<<< orphan*/  l2cap_info_timeout ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  process_pending_rx ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct l2cap_conn *l2cap_conn_add(struct hci_conn *hcon)
{
	struct l2cap_conn *conn = hcon->l2cap_data;
	struct hci_chan *hchan;

	if (conn)
		return conn;

	hchan = hci_chan_create(hcon);
	if (!hchan)
		return NULL;

	conn = kzalloc(sizeof(*conn), GFP_KERNEL);
	if (!conn) {
		hci_chan_del(hchan);
		return NULL;
	}

	kref_init(&conn->ref);
	hcon->l2cap_data = conn;
	conn->hcon = hci_conn_get(hcon);
	conn->hchan = hchan;

	BT_DBG("hcon %p conn %p hchan %p", hcon, conn, hchan);

	switch (hcon->type) {
	case LE_LINK:
		if (hcon->hdev->le_mtu) {
			conn->mtu = hcon->hdev->le_mtu;
			break;
		}
		/* fall through */
	default:
		conn->mtu = hcon->hdev->acl_mtu;
		break;
	}

	conn->feat_mask = 0;

	conn->local_fixed_chan = L2CAP_FC_SIG_BREDR | L2CAP_FC_CONNLESS;

	if (hcon->type == ACL_LINK &&
	    hci_dev_test_flag(hcon->hdev, HCI_HS_ENABLED))
		conn->local_fixed_chan |= L2CAP_FC_A2MP;

	if (hci_dev_test_flag(hcon->hdev, HCI_LE_ENABLED) &&
	    (bredr_sc_enabled(hcon->hdev) ||
	     hci_dev_test_flag(hcon->hdev, HCI_FORCE_BREDR_SMP)))
		conn->local_fixed_chan |= L2CAP_FC_SMP_BREDR;

	mutex_init(&conn->ident_lock);
	mutex_init(&conn->chan_lock);

	INIT_LIST_HEAD(&conn->chan_l);
	INIT_LIST_HEAD(&conn->users);

	INIT_DELAYED_WORK(&conn->info_timer, l2cap_info_timeout);

	skb_queue_head_init(&conn->pending_rx);
	INIT_WORK(&conn->pending_rx_work, process_pending_rx);
	INIT_WORK(&conn->id_addr_update_work, l2cap_conn_update_id_addr);

	conn->disc_reason = HCI_ERROR_REMOTE_USER_TERM;

	return conn;
}