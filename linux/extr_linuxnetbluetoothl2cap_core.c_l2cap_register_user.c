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
struct l2cap_user {int (* probe ) (struct l2cap_conn*,struct l2cap_user*) ;int /*<<< orphan*/  list; } ;
struct l2cap_conn {int /*<<< orphan*/  users; int /*<<< orphan*/  hchan; TYPE_1__* hcon; } ;
struct hci_dev {int dummy; } ;
struct TYPE_2__ {struct hci_dev* hdev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  hci_dev_lock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_dev_unlock (struct hci_dev*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int stub1 (struct l2cap_conn*,struct l2cap_user*) ; 

int l2cap_register_user(struct l2cap_conn *conn, struct l2cap_user *user)
{
	struct hci_dev *hdev = conn->hcon->hdev;
	int ret;

	/* We need to check whether l2cap_conn is registered. If it is not, we
	 * must not register the l2cap_user. l2cap_conn_del() is unregisters
	 * l2cap_conn objects, but doesn't provide its own locking. Instead, it
	 * relies on the parent hci_conn object to be locked. This itself relies
	 * on the hci_dev object to be locked. So we must lock the hci device
	 * here, too. */

	hci_dev_lock(hdev);

	if (!list_empty(&user->list)) {
		ret = -EINVAL;
		goto out_unlock;
	}

	/* conn->hchan is NULL after l2cap_conn_del() was called */
	if (!conn->hchan) {
		ret = -ENODEV;
		goto out_unlock;
	}

	ret = user->probe(conn, user);
	if (ret)
		goto out_unlock;

	list_add(&user->list, &conn->users);
	ret = 0;

out_unlock:
	hci_dev_unlock(hdev);
	return ret;
}