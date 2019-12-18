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
struct hci_dev {scalar_t__ req_status; } ;

/* Variables and functions */
 scalar_t__ HCI_REQ_PEND ; 

bool hci_req_status_pend(struct hci_dev *hdev)
{
	return hdev->req_status == HCI_REQ_PEND;
}