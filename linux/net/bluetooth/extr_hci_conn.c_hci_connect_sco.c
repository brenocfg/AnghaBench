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
struct hci_dev {int dummy; } ;
struct hci_conn {scalar_t__ state; int /*<<< orphan*/  flags; int /*<<< orphan*/  setting; struct hci_conn* link; } ;
typedef  int /*<<< orphan*/  bdaddr_t ;
typedef  int /*<<< orphan*/  __u16 ;

/* Variables and functions */
 scalar_t__ BT_CLOSED ; 
 scalar_t__ BT_CONNECTED ; 
 scalar_t__ BT_OPEN ; 
 int /*<<< orphan*/  BT_POWER_FORCE_ACTIVE_ON ; 
 int /*<<< orphan*/  BT_SECURITY_LOW ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct hci_conn* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HCI_AT_NO_BONDING ; 
 int /*<<< orphan*/  HCI_CONN_MODE_CHANGE_PEND ; 
 int /*<<< orphan*/  HCI_CONN_POWER_SAVE ; 
 int /*<<< orphan*/  HCI_CONN_SCO_SETUP_PEND ; 
 int /*<<< orphan*/  HCI_ROLE_MASTER ; 
 scalar_t__ IS_ERR (struct hci_conn*) ; 
 struct hci_conn* hci_conn_add (struct hci_dev*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_conn_drop (struct hci_conn*) ; 
 int /*<<< orphan*/  hci_conn_enter_active_mode (struct hci_conn*,int /*<<< orphan*/ ) ; 
 struct hci_conn* hci_conn_hash_lookup_ba (struct hci_dev*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hci_conn_hold (struct hci_conn*) ; 
 struct hci_conn* hci_connect_acl (struct hci_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_sco_setup (struct hci_conn*,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

struct hci_conn *hci_connect_sco(struct hci_dev *hdev, int type, bdaddr_t *dst,
				 __u16 setting)
{
	struct hci_conn *acl;
	struct hci_conn *sco;

	acl = hci_connect_acl(hdev, dst, BT_SECURITY_LOW, HCI_AT_NO_BONDING);
	if (IS_ERR(acl))
		return acl;

	sco = hci_conn_hash_lookup_ba(hdev, type, dst);
	if (!sco) {
		sco = hci_conn_add(hdev, type, dst, HCI_ROLE_MASTER);
		if (!sco) {
			hci_conn_drop(acl);
			return ERR_PTR(-ENOMEM);
		}
	}

	acl->link = sco;
	sco->link = acl;

	hci_conn_hold(sco);

	sco->setting = setting;

	if (acl->state == BT_CONNECTED &&
	    (sco->state == BT_OPEN || sco->state == BT_CLOSED)) {
		set_bit(HCI_CONN_POWER_SAVE, &acl->flags);
		hci_conn_enter_active_mode(acl, BT_POWER_FORCE_ACTIVE_ON);

		if (test_bit(HCI_CONN_MODE_CHANGE_PEND, &acl->flags)) {
			/* defer SCO setup until mode change completed */
			set_bit(HCI_CONN_SCO_SETUP_PEND, &acl->flags);
			return sco;
		}

		hci_sco_setup(acl, 0x00);
	}

	return sco;
}