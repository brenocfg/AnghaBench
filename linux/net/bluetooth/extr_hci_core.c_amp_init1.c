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
struct TYPE_2__ {int /*<<< orphan*/  flow_ctl_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCI_FLOW_CTL_MODE_BLOCK_BASED ; 
 int /*<<< orphan*/  HCI_OP_READ_DATA_BLOCK_SIZE ; 
 int /*<<< orphan*/  HCI_OP_READ_FLOW_CONTROL_MODE ; 
 int /*<<< orphan*/  HCI_OP_READ_LOCAL_AMP_INFO ; 
 int /*<<< orphan*/  HCI_OP_READ_LOCAL_COMMANDS ; 
 int /*<<< orphan*/  HCI_OP_READ_LOCAL_VERSION ; 
 int /*<<< orphan*/  HCI_OP_READ_LOCATION_DATA ; 
 int /*<<< orphan*/  hci_req_add (struct hci_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void amp_init1(struct hci_request *req)
{
	req->hdev->flow_ctl_mode = HCI_FLOW_CTL_MODE_BLOCK_BASED;

	/* Read Local Version */
	hci_req_add(req, HCI_OP_READ_LOCAL_VERSION, 0, NULL);

	/* Read Local Supported Commands */
	hci_req_add(req, HCI_OP_READ_LOCAL_COMMANDS, 0, NULL);

	/* Read Local AMP Info */
	hci_req_add(req, HCI_OP_READ_LOCAL_AMP_INFO, 0, NULL);

	/* Read Data Blk size */
	hci_req_add(req, HCI_OP_READ_DATA_BLOCK_SIZE, 0, NULL);

	/* Read Flow Control Mode */
	hci_req_add(req, HCI_OP_READ_FLOW_CONTROL_MODE, 0, NULL);

	/* Read Location Data */
	hci_req_add(req, HCI_OP_READ_LOCATION_DATA, 0, NULL);
}