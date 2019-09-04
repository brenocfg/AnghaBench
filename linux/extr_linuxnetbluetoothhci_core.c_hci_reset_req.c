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
struct hci_request {TYPE_1__* hdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  HCI_OP_RESET ; 
 int /*<<< orphan*/  HCI_RESET ; 
 int /*<<< orphan*/  hci_req_add (struct hci_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hci_reset_req(struct hci_request *req, unsigned long opt)
{
	BT_DBG("%s %ld", req->hdev->name, opt);

	/* Reset device */
	set_bit(HCI_RESET, &req->hdev->flags);
	hci_req_add(req, HCI_OP_RESET, 0, NULL);
	return 0;
}