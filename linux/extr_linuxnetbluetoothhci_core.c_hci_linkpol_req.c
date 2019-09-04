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
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HCI_OP_WRITE_DEF_LINK_POLICY ; 
 int /*<<< orphan*/  cpu_to_le16 (unsigned long) ; 
 int /*<<< orphan*/  hci_req_add (struct hci_request*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hci_linkpol_req(struct hci_request *req, unsigned long opt)
{
	__le16 policy = cpu_to_le16(opt);

	BT_DBG("%s %x", req->hdev->name, policy);

	/* Default link policy */
	hci_req_add(req, HCI_OP_WRITE_DEF_LINK_POLICY, 2, &policy);
	return 0;
}