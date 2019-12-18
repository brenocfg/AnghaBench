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
struct smp_chan {TYPE_1__* remote_irk; TYPE_1__* slave_ltk; TYPE_1__* ltk; int /*<<< orphan*/  tfm_ecdh; int /*<<< orphan*/  tfm_cmac; struct smp_chan* link_key; struct smp_chan* slave_csrk; struct smp_chan* csrk; int /*<<< orphan*/  flags; int /*<<< orphan*/  security_timer; } ;
struct l2cap_conn {struct hci_conn* hcon; struct l2cap_chan* smp; } ;
struct l2cap_chan {struct smp_chan* data; } ;
struct hci_conn {int /*<<< orphan*/  hdev; } ;
struct TYPE_2__ {scalar_t__ type; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  HCI_KEEP_DEBUG_KEYS ; 
 int /*<<< orphan*/  SMP_FLAG_COMPLETE ; 
 scalar_t__ SMP_LTK_P256_DEBUG ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crypto_free_kpp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_free_shash (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_conn_drop (struct hci_conn*) ; 
 int /*<<< orphan*/  hci_dev_test_flag (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_rcu (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kzfree (struct smp_chan*) ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mgmt_smp_complete (struct hci_conn*,int) ; 
 int /*<<< orphan*/  rcu ; 
 int test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void smp_chan_destroy(struct l2cap_conn *conn)
{
	struct l2cap_chan *chan = conn->smp;
	struct smp_chan *smp = chan->data;
	struct hci_conn *hcon = conn->hcon;
	bool complete;

	BUG_ON(!smp);

	cancel_delayed_work_sync(&smp->security_timer);

	complete = test_bit(SMP_FLAG_COMPLETE, &smp->flags);
	mgmt_smp_complete(hcon, complete);

	kzfree(smp->csrk);
	kzfree(smp->slave_csrk);
	kzfree(smp->link_key);

	crypto_free_shash(smp->tfm_cmac);
	crypto_free_kpp(smp->tfm_ecdh);

	/* Ensure that we don't leave any debug key around if debug key
	 * support hasn't been explicitly enabled.
	 */
	if (smp->ltk && smp->ltk->type == SMP_LTK_P256_DEBUG &&
	    !hci_dev_test_flag(hcon->hdev, HCI_KEEP_DEBUG_KEYS)) {
		list_del_rcu(&smp->ltk->list);
		kfree_rcu(smp->ltk, rcu);
		smp->ltk = NULL;
	}

	/* If pairing failed clean up any keys we might have */
	if (!complete) {
		if (smp->ltk) {
			list_del_rcu(&smp->ltk->list);
			kfree_rcu(smp->ltk, rcu);
		}

		if (smp->slave_ltk) {
			list_del_rcu(&smp->slave_ltk->list);
			kfree_rcu(smp->slave_ltk, rcu);
		}

		if (smp->remote_irk) {
			list_del_rcu(&smp->remote_irk->list);
			kfree_rcu(smp->remote_irk, rcu);
		}
	}

	chan->data = NULL;
	kzfree(smp);
	hci_conn_drop(hcon);
}