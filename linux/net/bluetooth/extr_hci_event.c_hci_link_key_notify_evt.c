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
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {scalar_t__ data; } ;
struct link_key {scalar_t__ type; int /*<<< orphan*/  list; int /*<<< orphan*/  pin_len; } ;
struct hci_ev_link_key_notify {scalar_t__ key_type; int /*<<< orphan*/  link_key; int /*<<< orphan*/  bdaddr; } ;
struct hci_dev {int /*<<< orphan*/  name; } ;
struct hci_conn {int /*<<< orphan*/  flags; int /*<<< orphan*/  pin_length; int /*<<< orphan*/  disc_timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACL_LINK ; 
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HCI_CONN_FLUSH_KEY ; 
 int /*<<< orphan*/  HCI_CONN_NEW_LINK_KEY ; 
 int /*<<< orphan*/  HCI_DISCONN_TIMEOUT ; 
 int /*<<< orphan*/  HCI_KEEP_DEBUG_KEYS ; 
 scalar_t__ HCI_LK_CHANGED_COMBINATION ; 
 scalar_t__ HCI_LK_DEBUG_COMBINATION ; 
 int /*<<< orphan*/  HCI_MGMT ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  conn_set_key (struct hci_conn*,scalar_t__,int /*<<< orphan*/ ) ; 
 struct link_key* hci_add_link_key (struct hci_dev*,struct hci_conn*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  hci_conn_drop (struct hci_conn*) ; 
 struct hci_conn* hci_conn_hash_lookup_ba (struct hci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hci_conn_hold (struct hci_conn*) ; 
 int /*<<< orphan*/  hci_dev_lock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_dev_test_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_dev_unlock (struct hci_dev*) ; 
 int /*<<< orphan*/  kfree_rcu (struct link_key*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mgmt_new_link_key (struct hci_dev*,struct link_key*,int) ; 
 int /*<<< orphan*/  rcu ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hci_link_key_notify_evt(struct hci_dev *hdev, struct sk_buff *skb)
{
	struct hci_ev_link_key_notify *ev = (void *) skb->data;
	struct hci_conn *conn;
	struct link_key *key;
	bool persistent;
	u8 pin_len = 0;

	BT_DBG("%s", hdev->name);

	hci_dev_lock(hdev);

	conn = hci_conn_hash_lookup_ba(hdev, ACL_LINK, &ev->bdaddr);
	if (!conn)
		goto unlock;

	hci_conn_hold(conn);
	conn->disc_timeout = HCI_DISCONN_TIMEOUT;
	hci_conn_drop(conn);

	set_bit(HCI_CONN_NEW_LINK_KEY, &conn->flags);
	conn_set_key(conn, ev->key_type, conn->pin_length);

	if (!hci_dev_test_flag(hdev, HCI_MGMT))
		goto unlock;

	key = hci_add_link_key(hdev, conn, &ev->bdaddr, ev->link_key,
			        ev->key_type, pin_len, &persistent);
	if (!key)
		goto unlock;

	/* Update connection information since adding the key will have
	 * fixed up the type in the case of changed combination keys.
	 */
	if (ev->key_type == HCI_LK_CHANGED_COMBINATION)
		conn_set_key(conn, key->type, key->pin_len);

	mgmt_new_link_key(hdev, key, persistent);

	/* Keep debug keys around only if the HCI_KEEP_DEBUG_KEYS flag
	 * is set. If it's not set simply remove the key from the kernel
	 * list (we've still notified user space about it but with
	 * store_hint being 0).
	 */
	if (key->type == HCI_LK_DEBUG_COMBINATION &&
	    !hci_dev_test_flag(hdev, HCI_KEEP_DEBUG_KEYS)) {
		list_del_rcu(&key->list);
		kfree_rcu(key, rcu);
		goto unlock;
	}

	if (persistent)
		clear_bit(HCI_CONN_FLUSH_KEY, &conn->flags);
	else
		set_bit(HCI_CONN_FLUSH_KEY, &conn->flags);

unlock:
	hci_dev_unlock(hdev);
}