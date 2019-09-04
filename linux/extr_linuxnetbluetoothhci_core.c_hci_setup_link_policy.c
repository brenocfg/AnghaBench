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
typedef  int /*<<< orphan*/  u16 ;
struct hci_request {struct hci_dev* hdev; } ;
struct hci_dev {int dummy; } ;
struct hci_cp_write_def_link_policy {int /*<<< orphan*/  policy; } ;
typedef  int /*<<< orphan*/  cp ;

/* Variables and functions */
 int /*<<< orphan*/  HCI_LP_HOLD ; 
 int /*<<< orphan*/  HCI_LP_PARK ; 
 int /*<<< orphan*/  HCI_LP_RSWITCH ; 
 int /*<<< orphan*/  HCI_LP_SNIFF ; 
 int /*<<< orphan*/  HCI_OP_WRITE_DEF_LINK_POLICY ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_req_add (struct hci_request*,int /*<<< orphan*/ ,int,struct hci_cp_write_def_link_policy*) ; 
 scalar_t__ lmp_hold_capable (struct hci_dev*) ; 
 scalar_t__ lmp_park_capable (struct hci_dev*) ; 
 scalar_t__ lmp_rswitch_capable (struct hci_dev*) ; 
 scalar_t__ lmp_sniff_capable (struct hci_dev*) ; 

__attribute__((used)) static void hci_setup_link_policy(struct hci_request *req)
{
	struct hci_dev *hdev = req->hdev;
	struct hci_cp_write_def_link_policy cp;
	u16 link_policy = 0;

	if (lmp_rswitch_capable(hdev))
		link_policy |= HCI_LP_RSWITCH;
	if (lmp_hold_capable(hdev))
		link_policy |= HCI_LP_HOLD;
	if (lmp_sniff_capable(hdev))
		link_policy |= HCI_LP_SNIFF;
	if (lmp_park_capable(hdev))
		link_policy |= HCI_LP_PARK;

	cp.policy = cpu_to_le16(link_policy);
	hci_req_add(req, HCI_OP_WRITE_DEF_LINK_POLICY, sizeof(cp), &cp);
}