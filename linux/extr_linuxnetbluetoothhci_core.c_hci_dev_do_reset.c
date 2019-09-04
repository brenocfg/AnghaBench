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
struct hci_dev {scalar_t__ le_cnt; scalar_t__ sco_cnt; scalar_t__ acl_cnt; int /*<<< orphan*/  cmd_cnt; int /*<<< orphan*/  (* flush ) (struct hci_dev*) ;int /*<<< orphan*/  workqueue; int /*<<< orphan*/  cmd_q; int /*<<< orphan*/  rx_q; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,struct hci_dev*) ; 
 int /*<<< orphan*/  HCI_INIT_TIMEOUT ; 
 int __hci_req_sync (struct hci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  drain_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_conn_hash_flush (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_dev_lock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_dev_unlock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_inquiry_cache_flush (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_req_sync_lock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_req_sync_unlock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_reset_req ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct hci_dev*) ; 

__attribute__((used)) static int hci_dev_do_reset(struct hci_dev *hdev)
{
	int ret;

	BT_DBG("%s %p", hdev->name, hdev);

	hci_req_sync_lock(hdev);

	/* Drop queues */
	skb_queue_purge(&hdev->rx_q);
	skb_queue_purge(&hdev->cmd_q);

	/* Avoid potential lockdep warnings from the *_flush() calls by
	 * ensuring the workqueue is empty up front.
	 */
	drain_workqueue(hdev->workqueue);

	hci_dev_lock(hdev);
	hci_inquiry_cache_flush(hdev);
	hci_conn_hash_flush(hdev);
	hci_dev_unlock(hdev);

	if (hdev->flush)
		hdev->flush(hdev);

	atomic_set(&hdev->cmd_cnt, 1);
	hdev->acl_cnt = 0; hdev->sco_cnt = 0; hdev->le_cnt = 0;

	ret = __hci_req_sync(hdev, hci_reset_req, 0, HCI_INIT_TIMEOUT, NULL);

	hci_req_sync_unlock(hdev);
	return ret;
}