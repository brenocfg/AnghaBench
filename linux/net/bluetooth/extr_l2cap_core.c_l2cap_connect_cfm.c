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
typedef  scalar_t__ u8 ;
struct l2cap_conn {int dummy; } ;
struct l2cap_chan {scalar_t__ dst_type; int /*<<< orphan*/  src_type; int /*<<< orphan*/  dst; int /*<<< orphan*/  src; TYPE_1__* ops; int /*<<< orphan*/  scid; } ;
struct hci_dev {int /*<<< orphan*/  blacklist; } ;
struct hci_conn {scalar_t__ type; int /*<<< orphan*/  dst; int /*<<< orphan*/  src; struct hci_dev* hdev; } ;
struct TYPE_2__ {struct l2cap_chan* (* new_connection ) (struct l2cap_chan*) ;} ;

/* Variables and functions */
 scalar_t__ ACL_LINK ; 
 int /*<<< orphan*/  BT_DBG (char*,struct hci_conn*,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ LE_LINK ; 
 int /*<<< orphan*/  __l2cap_chan_add (struct l2cap_conn*,struct l2cap_chan*) ; 
 scalar_t__ __l2cap_get_chan_by_dcid (struct l2cap_conn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bacpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ bdaddr_dst_type (struct hci_conn*) ; 
 int /*<<< orphan*/  bdaddr_src_type (struct hci_conn*) ; 
 int /*<<< orphan*/  bt_to_errno (scalar_t__) ; 
 scalar_t__ hci_bdaddr_list_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  l2cap_chan_lock (struct l2cap_chan*) ; 
 int /*<<< orphan*/  l2cap_chan_put (struct l2cap_chan*) ; 
 int /*<<< orphan*/  l2cap_chan_unlock (struct l2cap_chan*) ; 
 struct l2cap_conn* l2cap_conn_add (struct hci_conn*) ; 
 int /*<<< orphan*/  l2cap_conn_del (struct hci_conn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2cap_conn_ready (struct l2cap_conn*) ; 
 struct l2cap_chan* l2cap_global_fixed_chan (struct l2cap_chan*,struct hci_conn*) ; 
 struct l2cap_chan* stub1 (struct l2cap_chan*) ; 

__attribute__((used)) static void l2cap_connect_cfm(struct hci_conn *hcon, u8 status)
{
	struct hci_dev *hdev = hcon->hdev;
	struct l2cap_conn *conn;
	struct l2cap_chan *pchan;
	u8 dst_type;

	if (hcon->type != ACL_LINK && hcon->type != LE_LINK)
		return;

	BT_DBG("hcon %p bdaddr %pMR status %d", hcon, &hcon->dst, status);

	if (status) {
		l2cap_conn_del(hcon, bt_to_errno(status));
		return;
	}

	conn = l2cap_conn_add(hcon);
	if (!conn)
		return;

	dst_type = bdaddr_dst_type(hcon);

	/* If device is blocked, do not create channels for it */
	if (hci_bdaddr_list_lookup(&hdev->blacklist, &hcon->dst, dst_type))
		return;

	/* Find fixed channels and notify them of the new connection. We
	 * use multiple individual lookups, continuing each time where
	 * we left off, because the list lock would prevent calling the
	 * potentially sleeping l2cap_chan_lock() function.
	 */
	pchan = l2cap_global_fixed_chan(NULL, hcon);
	while (pchan) {
		struct l2cap_chan *chan, *next;

		/* Client fixed channels should override server ones */
		if (__l2cap_get_chan_by_dcid(conn, pchan->scid))
			goto next;

		l2cap_chan_lock(pchan);
		chan = pchan->ops->new_connection(pchan);
		if (chan) {
			bacpy(&chan->src, &hcon->src);
			bacpy(&chan->dst, &hcon->dst);
			chan->src_type = bdaddr_src_type(hcon);
			chan->dst_type = dst_type;

			__l2cap_chan_add(conn, chan);
		}

		l2cap_chan_unlock(pchan);
next:
		next = l2cap_global_fixed_chan(pchan, hcon);
		l2cap_chan_put(pchan);
		pchan = next;
	}

	l2cap_conn_ready(conn);
}