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
struct nci_dev {int /*<<< orphan*/  req_lock; scalar_t__ flags; int /*<<< orphan*/  cmd_wq; int /*<<< orphan*/  cmd_timer; TYPE_1__* ops; int /*<<< orphan*/  cmd_cnt; int /*<<< orphan*/  cmd_q; int /*<<< orphan*/  tx_wq; int /*<<< orphan*/  rx_wq; int /*<<< orphan*/  tx_q; int /*<<< orphan*/  rx_q; int /*<<< orphan*/  data_timer; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* close ) (struct nci_dev*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 int /*<<< orphan*/  NCI_INIT ; 
 int /*<<< orphan*/  NCI_RESET_TIMEOUT ; 
 int /*<<< orphan*/  NCI_UP ; 
 int /*<<< orphan*/  __nci_request (struct nci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nci_req_cancel (struct nci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nci_reset_req ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct nci_dev*) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static int nci_close_device(struct nci_dev *ndev)
{
	nci_req_cancel(ndev, ENODEV);
	mutex_lock(&ndev->req_lock);

	if (!test_and_clear_bit(NCI_UP, &ndev->flags)) {
		del_timer_sync(&ndev->cmd_timer);
		del_timer_sync(&ndev->data_timer);
		mutex_unlock(&ndev->req_lock);
		return 0;
	}

	/* Drop RX and TX queues */
	skb_queue_purge(&ndev->rx_q);
	skb_queue_purge(&ndev->tx_q);

	/* Flush RX and TX wq */
	flush_workqueue(ndev->rx_wq);
	flush_workqueue(ndev->tx_wq);

	/* Reset device */
	skb_queue_purge(&ndev->cmd_q);
	atomic_set(&ndev->cmd_cnt, 1);

	set_bit(NCI_INIT, &ndev->flags);
	__nci_request(ndev, nci_reset_req, 0,
		      msecs_to_jiffies(NCI_RESET_TIMEOUT));

	/* After this point our queues are empty
	 * and no works are scheduled.
	 */
	ndev->ops->close(ndev);

	clear_bit(NCI_INIT, &ndev->flags);

	del_timer_sync(&ndev->cmd_timer);

	/* Flush cmd wq */
	flush_workqueue(ndev->cmd_wq);

	/* Clear flags */
	ndev->flags = 0;

	mutex_unlock(&ndev->req_lock);

	return 0;
}