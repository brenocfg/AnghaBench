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
typedef  void* u8 ;
struct sk_buff {scalar_t__ data; } ;
struct nfc_hci_dev {int dummy; } ;
struct hci_create_pipe_resp {void* pipe; } ;
struct hci_create_pipe_params {void* dest_gate; void* dest_host; int /*<<< orphan*/  src_gate; } ;
typedef  int /*<<< orphan*/  params ;

/* Variables and functions */
 int /*<<< orphan*/  NFC_HCI_ADMIN_GATE ; 
 int /*<<< orphan*/  NFC_HCI_ADMIN_PIPE ; 
 int /*<<< orphan*/  NFC_HCI_ADM_CREATE_PIPE ; 
 void* NFC_HCI_INVALID_PIPE ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int nfc_hci_execute_cmd (struct nfc_hci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**,int,struct sk_buff**) ; 
 int /*<<< orphan*/  pr_debug (char*,void*) ; 

__attribute__((used)) static u8 nfc_hci_create_pipe(struct nfc_hci_dev *hdev, u8 dest_host,
			      u8 dest_gate, int *result)
{
	struct sk_buff *skb;
	struct hci_create_pipe_params params;
	struct hci_create_pipe_resp *resp;
	u8 pipe;

	pr_debug("gate=%d\n", dest_gate);

	params.src_gate = NFC_HCI_ADMIN_GATE;
	params.dest_host = dest_host;
	params.dest_gate = dest_gate;

	*result = nfc_hci_execute_cmd(hdev, NFC_HCI_ADMIN_PIPE,
				      NFC_HCI_ADM_CREATE_PIPE,
				      (u8 *) &params, sizeof(params), &skb);
	if (*result < 0)
		return NFC_HCI_INVALID_PIPE;

	resp = (struct hci_create_pipe_resp *)skb->data;
	pipe = resp->pipe;
	kfree_skb(skb);

	pr_debug("pipe created=%d\n", pipe);

	return pipe;
}