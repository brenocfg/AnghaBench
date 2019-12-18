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
struct smp_cmd_ident_addr_info {scalar_t__ addr_type; int /*<<< orphan*/  bdaddr; } ;
struct smp_chan {int remote_key_dist; scalar_t__ id_addr_type; int /*<<< orphan*/  irk; int /*<<< orphan*/  id_addr; int /*<<< orphan*/  remote_irk; } ;
struct sk_buff {int len; scalar_t__ data; } ;
struct l2cap_conn {struct hci_conn* hcon; struct l2cap_chan* smp; } ;
struct l2cap_chan {struct smp_chan* data; } ;
struct hci_conn {scalar_t__ dst_type; int /*<<< orphan*/  hdev; int /*<<< orphan*/  dst; } ;
typedef  int /*<<< orphan*/  bdaddr_t ;

/* Variables and functions */
 int /*<<< orphan*/ * BDADDR_ANY ; 
 int /*<<< orphan*/  BT_DBG (char*) ; 
 int KEY_DIST_MASK ; 
 int /*<<< orphan*/  SMP_ALLOW_CMD (struct smp_chan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SMP_CMD_SIGN_INFO ; 
 int SMP_DIST_ID_KEY ; 
 int SMP_DIST_SIGN ; 
 int SMP_INVALID_PARAMS ; 
 scalar_t__ bacmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bacpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bt_dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  hci_add_irk (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ hci_bdaddr_is_rpa (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ hci_is_identity_address (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  smp_distribute_keys (struct smp_chan*) ; 

__attribute__((used)) static int smp_cmd_ident_addr_info(struct l2cap_conn *conn,
				   struct sk_buff *skb)
{
	struct smp_cmd_ident_addr_info *info = (void *) skb->data;
	struct l2cap_chan *chan = conn->smp;
	struct smp_chan *smp = chan->data;
	struct hci_conn *hcon = conn->hcon;
	bdaddr_t rpa;

	BT_DBG("");

	if (skb->len < sizeof(*info))
		return SMP_INVALID_PARAMS;

	/* Mark the information as received */
	smp->remote_key_dist &= ~SMP_DIST_ID_KEY;

	if (smp->remote_key_dist & SMP_DIST_SIGN)
		SMP_ALLOW_CMD(smp, SMP_CMD_SIGN_INFO);

	skb_pull(skb, sizeof(*info));

	/* Strictly speaking the Core Specification (4.1) allows sending
	 * an empty address which would force us to rely on just the IRK
	 * as "identity information". However, since such
	 * implementations are not known of and in order to not over
	 * complicate our implementation, simply pretend that we never
	 * received an IRK for such a device.
	 *
	 * The Identity Address must also be a Static Random or Public
	 * Address, which hci_is_identity_address() checks for.
	 */
	if (!bacmp(&info->bdaddr, BDADDR_ANY) ||
	    !hci_is_identity_address(&info->bdaddr, info->addr_type)) {
		bt_dev_err(hcon->hdev, "ignoring IRK with no identity address");
		goto distribute;
	}

	/* Drop IRK if peer is using identity address during pairing but is
	 * providing different address as identity information.
	 *
	 * Microsoft Surface Precision Mouse is known to have this bug.
	 */
	if (hci_is_identity_address(&hcon->dst, hcon->dst_type) &&
	    (bacmp(&info->bdaddr, &hcon->dst) ||
	     info->addr_type != hcon->dst_type)) {
		bt_dev_err(hcon->hdev,
			   "ignoring IRK with invalid identity address");
		goto distribute;
	}

	bacpy(&smp->id_addr, &info->bdaddr);
	smp->id_addr_type = info->addr_type;

	if (hci_bdaddr_is_rpa(&hcon->dst, hcon->dst_type))
		bacpy(&rpa, &hcon->dst);
	else
		bacpy(&rpa, BDADDR_ANY);

	smp->remote_irk = hci_add_irk(conn->hcon->hdev, &smp->id_addr,
				      smp->id_addr_type, smp->irk, &rpa);

distribute:
	if (!(smp->remote_key_dist & KEY_DIST_MASK))
		smp_distribute_keys(smp);

	return 0;
}