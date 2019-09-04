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
typedef  scalar_t__ u8 ;
typedef  int u16 ;
struct sk_buff {int len; int* data; } ;
struct nfc_llcp_local {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int LLCP_AGF_PDU_HEADER_SIZE ; 
 int LLCP_HEADER_SIZE ; 
 scalar_t__ LLCP_PDU_AGF ; 
 scalar_t__ LLCP_PDU_SYMM ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct sk_buff* nfc_alloc_recv_skb (int,int /*<<< orphan*/ ) ; 
 scalar_t__ nfc_llcp_ptype (struct sk_buff*) ; 
 int /*<<< orphan*/  nfc_llcp_rx_skb (struct nfc_llcp_local*,struct sk_buff*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_put_data (struct sk_buff*,int*,int) ; 

__attribute__((used)) static void nfc_llcp_recv_agf(struct nfc_llcp_local *local, struct sk_buff *skb)
{
	u8 ptype;
	u16 pdu_len;
	struct sk_buff *new_skb;

	if (skb->len <= LLCP_HEADER_SIZE) {
		pr_err("Malformed AGF PDU\n");
		return;
	}

	skb_pull(skb, LLCP_HEADER_SIZE);

	while (skb->len > LLCP_AGF_PDU_HEADER_SIZE) {
		pdu_len = skb->data[0] << 8 | skb->data[1];

		skb_pull(skb, LLCP_AGF_PDU_HEADER_SIZE);

		if (pdu_len < LLCP_HEADER_SIZE || pdu_len > skb->len) {
			pr_err("Malformed AGF PDU\n");
			return;
		}

		ptype = nfc_llcp_ptype(skb);

		if (ptype == LLCP_PDU_SYMM || ptype == LLCP_PDU_AGF)
			goto next;

		new_skb = nfc_alloc_recv_skb(pdu_len, GFP_KERNEL);
		if (new_skb == NULL) {
			pr_err("Could not allocate PDU\n");
			return;
		}

		skb_put_data(new_skb, skb->data, pdu_len);

		nfc_llcp_rx_skb(local, new_skb);

		kfree_skb(new_skb);
next:
		skb_pull(skb, pdu_len);
	}
}