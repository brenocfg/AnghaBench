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
struct hci_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCI_OP_LE_CLEAR_ADV_SETS ; 
 int /*<<< orphan*/  hci_req_add (struct hci_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void __hci_req_clear_ext_adv_sets(struct hci_request *req)
{
	hci_req_add(req, HCI_OP_LE_CLEAR_ADV_SETS, 0, NULL);
}