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
struct sk_buff {scalar_t__ data; } ;
struct hci_ev_hardware_error {int /*<<< orphan*/  code; } ;
struct hci_dev {int /*<<< orphan*/  error_reset; int /*<<< orphan*/  req_workqueue; int /*<<< orphan*/  hw_error_code; } ;

/* Variables and functions */
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hci_hardware_error_evt(struct hci_dev *hdev, struct sk_buff *skb)
{
	struct hci_ev_hardware_error *ev = (void *) skb->data;

	hdev->hw_error_code = ev->code;

	queue_work(hdev->req_workqueue, &hdev->error_reset);
}