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
struct smp_ltk {scalar_t__ ediv; scalar_t__ rand; int enc_size; scalar_t__ type; int /*<<< orphan*/  list; int /*<<< orphan*/  val; } ;
struct sk_buff {scalar_t__ data; } ;
struct hci_ev_le_ltk_req {scalar_t__ ediv; scalar_t__ rand; int /*<<< orphan*/  handle; } ;
struct hci_dev {int /*<<< orphan*/  name; } ;
struct hci_cp_le_ltk_reply {int /*<<< orphan*/  handle; int /*<<< orphan*/  ltk; } ;
struct hci_cp_le_ltk_neg_reply {int /*<<< orphan*/  handle; int /*<<< orphan*/  ltk; } ;
struct hci_conn {int enc_key_size; int /*<<< orphan*/  flags; int /*<<< orphan*/  pending_sec_level; int /*<<< orphan*/  handle; int /*<<< orphan*/  role; int /*<<< orphan*/  dst_type; int /*<<< orphan*/  dst; } ;
typedef  int /*<<< orphan*/  neg ;
typedef  int /*<<< orphan*/  cp ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HCI_CONN_STK_ENCRYPT ; 
 int /*<<< orphan*/  HCI_OP_LE_LTK_NEG_REPLY ; 
 int /*<<< orphan*/  HCI_OP_LE_LTK_REPLY ; 
 scalar_t__ SMP_STK ; 
 int /*<<< orphan*/  __le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 struct hci_conn* hci_conn_hash_lookup_handle (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_dev_lock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_dev_unlock (struct hci_dev*) ; 
 struct smp_ltk* hci_find_ltk (struct hci_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_send_cmd (struct hci_dev*,int /*<<< orphan*/ ,int,struct hci_cp_le_ltk_reply*) ; 
 int /*<<< orphan*/  kfree_rcu (struct smp_ltk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rcu ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ smp_ltk_is_sc (struct smp_ltk*) ; 
 int /*<<< orphan*/  smp_ltk_sec_level (struct smp_ltk*) ; 

__attribute__((used)) static void hci_le_ltk_request_evt(struct hci_dev *hdev, struct sk_buff *skb)
{
	struct hci_ev_le_ltk_req *ev = (void *) skb->data;
	struct hci_cp_le_ltk_reply cp;
	struct hci_cp_le_ltk_neg_reply neg;
	struct hci_conn *conn;
	struct smp_ltk *ltk;

	BT_DBG("%s handle 0x%4.4x", hdev->name, __le16_to_cpu(ev->handle));

	hci_dev_lock(hdev);

	conn = hci_conn_hash_lookup_handle(hdev, __le16_to_cpu(ev->handle));
	if (conn == NULL)
		goto not_found;

	ltk = hci_find_ltk(hdev, &conn->dst, conn->dst_type, conn->role);
	if (!ltk)
		goto not_found;

	if (smp_ltk_is_sc(ltk)) {
		/* With SC both EDiv and Rand are set to zero */
		if (ev->ediv || ev->rand)
			goto not_found;
	} else {
		/* For non-SC keys check that EDiv and Rand match */
		if (ev->ediv != ltk->ediv || ev->rand != ltk->rand)
			goto not_found;
	}

	memcpy(cp.ltk, ltk->val, ltk->enc_size);
	memset(cp.ltk + ltk->enc_size, 0, sizeof(cp.ltk) - ltk->enc_size);
	cp.handle = cpu_to_le16(conn->handle);

	conn->pending_sec_level = smp_ltk_sec_level(ltk);

	conn->enc_key_size = ltk->enc_size;

	hci_send_cmd(hdev, HCI_OP_LE_LTK_REPLY, sizeof(cp), &cp);

	/* Ref. Bluetooth Core SPEC pages 1975 and 2004. STK is a
	 * temporary key used to encrypt a connection following
	 * pairing. It is used during the Encrypted Session Setup to
	 * distribute the keys. Later, security can be re-established
	 * using a distributed LTK.
	 */
	if (ltk->type == SMP_STK) {
		set_bit(HCI_CONN_STK_ENCRYPT, &conn->flags);
		list_del_rcu(&ltk->list);
		kfree_rcu(ltk, rcu);
	} else {
		clear_bit(HCI_CONN_STK_ENCRYPT, &conn->flags);
	}

	hci_dev_unlock(hdev);

	return;

not_found:
	neg.handle = ev->handle;
	hci_send_cmd(hdev, HCI_OP_LE_LTK_NEG_REPLY, sizeof(neg), &neg);
	hci_dev_unlock(hdev);
}