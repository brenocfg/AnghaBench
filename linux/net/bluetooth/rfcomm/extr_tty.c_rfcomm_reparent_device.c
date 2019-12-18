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
struct rfcomm_dev {int /*<<< orphan*/  tty_dev; int /*<<< orphan*/  dst; int /*<<< orphan*/  src; } ;
struct hci_dev {int dummy; } ;
struct hci_conn {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACL_LINK ; 
 int /*<<< orphan*/  BDADDR_BREDR ; 
 int /*<<< orphan*/  DPM_ORDER_DEV_AFTER_PARENT ; 
 scalar_t__ device_is_registered (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_move (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct hci_conn* hci_conn_hash_lookup_ba (struct hci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hci_dev_lock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_dev_put (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_dev_unlock (struct hci_dev*) ; 
 struct hci_dev* hci_get_route (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rfcomm_reparent_device(struct rfcomm_dev *dev)
{
	struct hci_dev *hdev;
	struct hci_conn *conn;

	hdev = hci_get_route(&dev->dst, &dev->src, BDADDR_BREDR);
	if (!hdev)
		return;

	/* The lookup results are unsafe to access without the
	 * hci device lock (FIXME: why is this not documented?)
	 */
	hci_dev_lock(hdev);
	conn = hci_conn_hash_lookup_ba(hdev, ACL_LINK, &dev->dst);

	/* Just because the acl link is in the hash table is no
	 * guarantee the sysfs device has been added ...
	 */
	if (conn && device_is_registered(&conn->dev))
		device_move(dev->tty_dev, &conn->dev, DPM_ORDER_DEV_AFTER_PARENT);

	hci_dev_unlock(hdev);
	hci_dev_put(hdev);
}