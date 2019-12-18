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
struct hci_cp_le_add_to_white_list {int /*<<< orphan*/  bdaddr; int /*<<< orphan*/  bdaddr_type; } ;
struct hci_conn_params {int /*<<< orphan*/  addr; int /*<<< orphan*/  addr_type; } ;
typedef  int /*<<< orphan*/  cp ;

/* Variables and functions */
 int /*<<< orphan*/  HCI_OP_LE_ADD_TO_WHITE_LIST ; 
 int /*<<< orphan*/  bacpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hci_req_add (struct hci_request*,int /*<<< orphan*/ ,int,struct hci_cp_le_add_to_white_list*) ; 

__attribute__((used)) static void add_to_white_list(struct hci_request *req,
			      struct hci_conn_params *params)
{
	struct hci_cp_le_add_to_white_list cp;

	cp.bdaddr_type = params->addr_type;
	bacpy(&cp.bdaddr, &params->addr);

	hci_req_add(req, HCI_OP_LE_ADD_TO_WHITE_LIST, sizeof(cp), &cp);
}