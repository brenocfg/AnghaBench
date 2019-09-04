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
struct timer_list {int dummy; } ;
struct nfc_hci_dev {int /*<<< orphan*/  msg_tx_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  cmd_timer ; 
 struct nfc_hci_dev* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 struct nfc_hci_dev* hdev ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nfc_hci_cmd_timeout(struct timer_list *t)
{
	struct nfc_hci_dev *hdev = from_timer(hdev, t, cmd_timer);

	schedule_work(&hdev->msg_tx_work);
}