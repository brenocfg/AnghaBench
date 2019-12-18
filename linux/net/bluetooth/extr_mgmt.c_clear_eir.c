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
struct hci_request {struct hci_dev* hdev; } ;
struct hci_dev {struct hci_cp_write_eir* eir; } ;
struct hci_cp_write_eir {int dummy; } ;
typedef  int /*<<< orphan*/  cp ;

/* Variables and functions */
 int /*<<< orphan*/  HCI_OP_WRITE_EIR ; 
 int /*<<< orphan*/  hci_req_add (struct hci_request*,int /*<<< orphan*/ ,int,struct hci_cp_write_eir*) ; 
 int /*<<< orphan*/  lmp_ext_inq_capable (struct hci_dev*) ; 
 int /*<<< orphan*/  memset (struct hci_cp_write_eir*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void clear_eir(struct hci_request *req)
{
	struct hci_dev *hdev = req->hdev;
	struct hci_cp_write_eir cp;

	if (!lmp_ext_inq_capable(hdev))
		return;

	memset(hdev->eir, 0, sizeof(hdev->eir));

	memset(&cp, 0, sizeof(cp));

	hci_req_add(req, HCI_OP_WRITE_EIR, sizeof(cp), &cp);
}