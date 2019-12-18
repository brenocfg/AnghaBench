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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u16 ;
struct l2cap_conn {int /*<<< orphan*/  chan_lock; } ;
struct l2cap_chan {scalar_t__ chan_type; int mode; int state; scalar_t__ sport; TYPE_1__* ops; int /*<<< orphan*/  src_type; int /*<<< orphan*/  src; int /*<<< orphan*/  sec_level; scalar_t__ dcid; int /*<<< orphan*/  psm; int /*<<< orphan*/  dst_type; int /*<<< orphan*/  dst; } ;
struct hci_dev {int dummy; } ;
struct hci_conn {int const state; int /*<<< orphan*/  src; } ;
typedef  int /*<<< orphan*/  bdaddr_t ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_2__ {int /*<<< orphan*/  (* get_sndtimeo ) (struct l2cap_chan*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ADDR_LE_DEV_PUBLIC ; 
 int /*<<< orphan*/  ADDR_LE_DEV_RANDOM ; 
 int /*<<< orphan*/  BDADDR_LE_PUBLIC ; 
#define  BT_BOUND 137 
#define  BT_CONFIG 136 
#define  BT_CONNECT 135 
#define  BT_CONNECT2 134 
#define  BT_CONNECTED 133 
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  BT_OPEN 132 
 int EBADFD ; 
 int EBUSY ; 
 int EHOSTUNREACH ; 
 int EINVAL ; 
 int EISCONN ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  HCI_ADVERTISING ; 
 int /*<<< orphan*/  HCI_LE_CONN_TIMEOUT ; 
 int /*<<< orphan*/  HCI_ROLE_SLAVE ; 
 scalar_t__ IS_ERR (struct hci_conn*) ; 
 scalar_t__ L2CAP_CHAN_CONN_ORIENTED ; 
 scalar_t__ L2CAP_CHAN_FIXED ; 
 scalar_t__ L2CAP_CHAN_RAW ; 
#define  L2CAP_MODE_BASIC 131 
#define  L2CAP_MODE_ERTM 130 
#define  L2CAP_MODE_LE_FLOWCTL 129 
#define  L2CAP_MODE_STREAMING 128 
 int PTR_ERR (struct hci_conn*) ; 
 int /*<<< orphan*/  __clear_chan_timer (struct l2cap_chan*) ; 
 int /*<<< orphan*/  __l2cap_chan_add (struct l2cap_conn*,struct l2cap_chan*) ; 
 scalar_t__ __l2cap_get_chan_by_dcid (struct l2cap_conn*,scalar_t__) ; 
 int /*<<< orphan*/  __le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __set_chan_timer (struct l2cap_chan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bacpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bdaddr_src_type (struct hci_conn*) ; 
 scalar_t__ bdaddr_type_is_le (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chan_list_lock ; 
 int /*<<< orphan*/  disable_ertm ; 
 int /*<<< orphan*/  hci_conn_drop (struct hci_conn*) ; 
 struct hci_conn* hci_connect_acl (struct hci_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct hci_conn* hci_connect_le (struct hci_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct hci_conn* hci_connect_le_scan (struct hci_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_dev_lock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_dev_put (struct hci_dev*) ; 
 scalar_t__ hci_dev_test_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_dev_unlock (struct hci_dev*) ; 
 struct hci_dev* hci_get_route (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_valid_psm (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ l2cap_chan_check_security (struct l2cap_chan*,int) ; 
 int /*<<< orphan*/  l2cap_chan_lock (struct l2cap_chan*) ; 
 int /*<<< orphan*/  l2cap_chan_unlock (struct l2cap_chan*) ; 
 struct l2cap_conn* l2cap_conn_add (struct hci_conn*) ; 
 int /*<<< orphan*/  l2cap_do_start (struct l2cap_chan*) ; 
 int /*<<< orphan*/  l2cap_get_auth_type (struct l2cap_chan*) ; 
 int /*<<< orphan*/  l2cap_state_change (struct l2cap_chan*,int const) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct l2cap_chan*) ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

int l2cap_chan_connect(struct l2cap_chan *chan, __le16 psm, u16 cid,
		       bdaddr_t *dst, u8 dst_type)
{
	struct l2cap_conn *conn;
	struct hci_conn *hcon;
	struct hci_dev *hdev;
	int err;

	BT_DBG("%pMR -> %pMR (type %u) psm 0x%2.2x", &chan->src, dst,
	       dst_type, __le16_to_cpu(psm));

	hdev = hci_get_route(dst, &chan->src, chan->src_type);
	if (!hdev)
		return -EHOSTUNREACH;

	hci_dev_lock(hdev);

	if (!is_valid_psm(__le16_to_cpu(psm), dst_type) && !cid &&
	    chan->chan_type != L2CAP_CHAN_RAW) {
		err = -EINVAL;
		goto done;
	}

	if (chan->chan_type == L2CAP_CHAN_CONN_ORIENTED && !psm) {
		err = -EINVAL;
		goto done;
	}

	if (chan->chan_type == L2CAP_CHAN_FIXED && !cid) {
		err = -EINVAL;
		goto done;
	}

	switch (chan->mode) {
	case L2CAP_MODE_BASIC:
		break;
	case L2CAP_MODE_LE_FLOWCTL:
		break;
	case L2CAP_MODE_ERTM:
	case L2CAP_MODE_STREAMING:
		if (!disable_ertm)
			break;
		/* fall through */
	default:
		err = -EOPNOTSUPP;
		goto done;
	}

	switch (chan->state) {
	case BT_CONNECT:
	case BT_CONNECT2:
	case BT_CONFIG:
		/* Already connecting */
		err = 0;
		goto done;

	case BT_CONNECTED:
		/* Already connected */
		err = -EISCONN;
		goto done;

	case BT_OPEN:
	case BT_BOUND:
		/* Can connect */
		break;

	default:
		err = -EBADFD;
		goto done;
	}

	/* Set destination address and psm */
	bacpy(&chan->dst, dst);
	chan->dst_type = dst_type;

	chan->psm = psm;
	chan->dcid = cid;

	if (bdaddr_type_is_le(dst_type)) {
		/* Convert from L2CAP channel address type to HCI address type
		 */
		if (dst_type == BDADDR_LE_PUBLIC)
			dst_type = ADDR_LE_DEV_PUBLIC;
		else
			dst_type = ADDR_LE_DEV_RANDOM;

		if (hci_dev_test_flag(hdev, HCI_ADVERTISING))
			hcon = hci_connect_le(hdev, dst, dst_type,
					      chan->sec_level,
					      HCI_LE_CONN_TIMEOUT,
					      HCI_ROLE_SLAVE, NULL);
		else
			hcon = hci_connect_le_scan(hdev, dst, dst_type,
						   chan->sec_level,
						   HCI_LE_CONN_TIMEOUT);

	} else {
		u8 auth_type = l2cap_get_auth_type(chan);
		hcon = hci_connect_acl(hdev, dst, chan->sec_level, auth_type);
	}

	if (IS_ERR(hcon)) {
		err = PTR_ERR(hcon);
		goto done;
	}

	conn = l2cap_conn_add(hcon);
	if (!conn) {
		hci_conn_drop(hcon);
		err = -ENOMEM;
		goto done;
	}

	mutex_lock(&conn->chan_lock);
	l2cap_chan_lock(chan);

	if (cid && __l2cap_get_chan_by_dcid(conn, cid)) {
		hci_conn_drop(hcon);
		err = -EBUSY;
		goto chan_unlock;
	}

	/* Update source addr of the socket */
	bacpy(&chan->src, &hcon->src);
	chan->src_type = bdaddr_src_type(hcon);

	__l2cap_chan_add(conn, chan);

	/* l2cap_chan_add takes its own ref so we can drop this one */
	hci_conn_drop(hcon);

	l2cap_state_change(chan, BT_CONNECT);
	__set_chan_timer(chan, chan->ops->get_sndtimeo(chan));

	/* Release chan->sport so that it can be reused by other
	 * sockets (as it's only used for listening sockets).
	 */
	write_lock(&chan_list_lock);
	chan->sport = 0;
	write_unlock(&chan_list_lock);

	if (hcon->state == BT_CONNECTED) {
		if (chan->chan_type != L2CAP_CHAN_CONN_ORIENTED) {
			__clear_chan_timer(chan);
			if (l2cap_chan_check_security(chan, true))
				l2cap_state_change(chan, BT_CONNECTED);
		} else
			l2cap_do_start(chan);
	}

	err = 0;

chan_unlock:
	l2cap_chan_unlock(chan);
	mutex_unlock(&conn->chan_lock);
done:
	hci_dev_unlock(hdev);
	hci_dev_put(hdev);
	return err;
}