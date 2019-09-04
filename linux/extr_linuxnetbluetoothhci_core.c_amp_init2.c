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
struct TYPE_2__ {int* commands; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCI_OP_READ_LOCAL_FEATURES ; 
 int /*<<< orphan*/  hci_req_add (struct hci_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int amp_init2(struct hci_request *req)
{
	/* Read Local Supported Features. Not all AMP controllers
	 * support this so it's placed conditionally in the second
	 * stage init.
	 */
	if (req->hdev->commands[14] & 0x20)
		hci_req_add(req, HCI_OP_READ_LOCAL_FEATURES, 0, NULL);

	return 0;
}