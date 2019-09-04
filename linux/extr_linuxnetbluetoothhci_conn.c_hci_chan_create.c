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
struct hci_dev {int /*<<< orphan*/  name; } ;
struct hci_conn {int /*<<< orphan*/  chan_list; int /*<<< orphan*/  flags; struct hci_dev* hdev; } ;
struct hci_chan {int /*<<< orphan*/  list; int /*<<< orphan*/  state; int /*<<< orphan*/  data_q; int /*<<< orphan*/  conn; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_CONNECTED ; 
 int /*<<< orphan*/  BT_DBG (char*,...) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HCI_CONN_DROP ; 
 int /*<<< orphan*/  hci_conn_get (struct hci_conn*) ; 
 struct hci_chan* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

struct hci_chan *hci_chan_create(struct hci_conn *conn)
{
	struct hci_dev *hdev = conn->hdev;
	struct hci_chan *chan;

	BT_DBG("%s hcon %p", hdev->name, conn);

	if (test_bit(HCI_CONN_DROP, &conn->flags)) {
		BT_DBG("Refusing to create new hci_chan");
		return NULL;
	}

	chan = kzalloc(sizeof(*chan), GFP_KERNEL);
	if (!chan)
		return NULL;

	chan->conn = hci_conn_get(conn);
	skb_queue_head_init(&chan->data_q);
	chan->state = BT_CONNECTED;

	list_add_rcu(&chan->list, &conn->chan_list);

	return chan;
}