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
struct sk_buff {int dummy; } ;
struct nfc_hci_dev {int dummy; } ;
struct hcp_exec_waiter {int exec_complete; scalar_t__ exec_result; struct sk_buff* result_skb; int /*<<< orphan*/ * wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_WAIT_QUEUE_HEAD_ONSTACK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX_FWI ; 
 int /*<<< orphan*/  NFC_HCI_HCP_COMMAND ; 
 int /*<<< orphan*/  ew_wq ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  nfc_hci_execute_cb ; 
 scalar_t__ nfc_hci_hcp_message_tx (struct nfc_hci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ ,struct hcp_exec_waiter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int nfc_hci_execute_cmd(struct nfc_hci_dev *hdev, u8 pipe, u8 cmd,
			       const u8 *param, size_t param_len,
			       struct sk_buff **skb)
{
	DECLARE_WAIT_QUEUE_HEAD_ONSTACK(ew_wq);
	struct hcp_exec_waiter hcp_ew;
	hcp_ew.wq = &ew_wq;
	hcp_ew.exec_complete = false;
	hcp_ew.result_skb = NULL;

	pr_debug("exec cmd sync through pipe=%d, cmd=%d, plen=%zd\n", pipe,
		 cmd, param_len);

	/* TODO: Define hci cmd execution delay. Should it be the same
	 * for all commands?
	 */
	hcp_ew.exec_result = nfc_hci_hcp_message_tx(hdev, pipe,
						    NFC_HCI_HCP_COMMAND, cmd,
						    param, param_len,
						    nfc_hci_execute_cb, &hcp_ew,
						    MAX_FWI);
	if (hcp_ew.exec_result < 0)
		return hcp_ew.exec_result;

	wait_event(ew_wq, hcp_ew.exec_complete == true);

	if (hcp_ew.exec_result == 0) {
		if (skb)
			*skb = hcp_ew.result_skb;
		else
			kfree_skb(hcp_ew.result_skb);
	}

	return hcp_ew.exec_result;
}