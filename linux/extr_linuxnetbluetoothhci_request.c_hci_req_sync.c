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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct hci_dev {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int ENETDOWN ; 
 int /*<<< orphan*/  HCI_UP ; 
 int __hci_req_sync (struct hci_dev*,int (*) (struct hci_request*,unsigned long),unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hci_req_sync_lock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_req_sync_unlock (struct hci_dev*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int hci_req_sync(struct hci_dev *hdev, int (*req)(struct hci_request *req,
						  unsigned long opt),
		 unsigned long opt, u32 timeout, u8 *hci_status)
{
	int ret;

	if (!test_bit(HCI_UP, &hdev->flags))
		return -ENETDOWN;

	/* Serialize all requests */
	hci_req_sync_lock(hdev);
	ret = __hci_req_sync(hdev, req, opt, timeout, hci_status);
	hci_req_sync_unlock(hdev);

	return ret;
}