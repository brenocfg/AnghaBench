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
struct nfc_hci_dev {int /*<<< orphan*/  ndev; int /*<<< orphan*/  msg_rx_queue; int /*<<< orphan*/  msg_rx_work; int /*<<< orphan*/  rx_hcp_frags; int /*<<< orphan*/  cmd_timer; int /*<<< orphan*/  msg_tx_work; int /*<<< orphan*/  msg_tx_queue; int /*<<< orphan*/  msg_tx_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfc_hci_cmd_timeout ; 
 int /*<<< orphan*/  nfc_hci_msg_rx_work ; 
 int /*<<< orphan*/  nfc_hci_msg_tx_work ; 
 int nfc_register_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int nfc_hci_register_device(struct nfc_hci_dev *hdev)
{
	mutex_init(&hdev->msg_tx_mutex);

	INIT_LIST_HEAD(&hdev->msg_tx_queue);

	INIT_WORK(&hdev->msg_tx_work, nfc_hci_msg_tx_work);

	timer_setup(&hdev->cmd_timer, nfc_hci_cmd_timeout, 0);

	skb_queue_head_init(&hdev->rx_hcp_frags);

	INIT_WORK(&hdev->msg_rx_work, nfc_hci_msg_rx_work);

	skb_queue_head_init(&hdev->msg_rx_queue);

	return nfc_register_device(hdev->ndev);
}