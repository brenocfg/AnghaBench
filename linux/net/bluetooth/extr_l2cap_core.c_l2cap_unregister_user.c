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
struct l2cap_user {int /*<<< orphan*/  (* remove ) (struct l2cap_conn*,struct l2cap_user*) ;int /*<<< orphan*/  list; } ;
struct l2cap_conn {TYPE_1__* hcon; } ;
struct hci_dev {int dummy; } ;
struct TYPE_2__ {struct hci_dev* hdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  hci_dev_lock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_dev_unlock (struct hci_dev*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct l2cap_conn*,struct l2cap_user*) ; 

void l2cap_unregister_user(struct l2cap_conn *conn, struct l2cap_user *user)
{
	struct hci_dev *hdev = conn->hcon->hdev;

	hci_dev_lock(hdev);

	if (list_empty(&user->list))
		goto out_unlock;

	list_del_init(&user->list);
	user->remove(conn, user);

out_unlock:
	hci_dev_unlock(hdev);
}