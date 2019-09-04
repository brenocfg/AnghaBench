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
typedef  int /*<<< orphan*/  u16 ;
struct hci_dev {int dummy; } ;
struct hci_cp_le_conn_param_req_neg_reply {int /*<<< orphan*/  reason; int /*<<< orphan*/  handle; } ;
typedef  int /*<<< orphan*/  cp ;

/* Variables and functions */
 int /*<<< orphan*/  HCI_OP_LE_CONN_PARAM_REQ_NEG_REPLY ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_send_cmd (struct hci_dev*,int /*<<< orphan*/ ,int,struct hci_cp_le_conn_param_req_neg_reply*) ; 

__attribute__((used)) static void send_conn_param_neg_reply(struct hci_dev *hdev, u16 handle,
				      u8 reason)
{
	struct hci_cp_le_conn_param_req_neg_reply cp;

	cp.handle = cpu_to_le16(handle);
	cp.reason = reason;

	hci_send_cmd(hdev, HCI_OP_LE_CONN_PARAM_REQ_NEG_REPLY, sizeof(cp),
		     &cp);
}