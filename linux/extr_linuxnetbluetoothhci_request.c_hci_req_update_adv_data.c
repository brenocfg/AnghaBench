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
struct hci_request {int dummy; } ;
struct hci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __hci_req_update_adv_data (struct hci_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_req_init (struct hci_request*,struct hci_dev*) ; 
 int hci_req_run (struct hci_request*,int /*<<< orphan*/ *) ; 

int hci_req_update_adv_data(struct hci_dev *hdev, u8 instance)
{
	struct hci_request req;

	hci_req_init(&req, hdev);
	__hci_req_update_adv_data(&req, instance);

	return hci_req_run(&req, NULL);
}