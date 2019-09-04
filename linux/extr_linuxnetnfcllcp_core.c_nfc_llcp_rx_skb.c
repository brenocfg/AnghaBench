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
typedef  int u8 ;
struct sk_buff {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct nfc_llcp_local {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUMP_PREFIX_OFFSET ; 
#define  LLCP_PDU_AGF 138 
#define  LLCP_PDU_CC 137 
#define  LLCP_PDU_CONNECT 136 
#define  LLCP_PDU_DISC 135 
#define  LLCP_PDU_DM 134 
#define  LLCP_PDU_I 133 
#define  LLCP_PDU_RNR 132 
#define  LLCP_PDU_RR 131 
#define  LLCP_PDU_SNL 130 
#define  LLCP_PDU_SYMM 129 
#define  LLCP_PDU_UI 128 
 int nfc_llcp_dsap (struct sk_buff*) ; 
 int nfc_llcp_ptype (struct sk_buff*) ; 
 int /*<<< orphan*/  nfc_llcp_recv_agf (struct nfc_llcp_local*,struct sk_buff*) ; 
 int /*<<< orphan*/  nfc_llcp_recv_cc (struct nfc_llcp_local*,struct sk_buff*) ; 
 int /*<<< orphan*/  nfc_llcp_recv_connect (struct nfc_llcp_local*,struct sk_buff*) ; 
 int /*<<< orphan*/  nfc_llcp_recv_disc (struct nfc_llcp_local*,struct sk_buff*) ; 
 int /*<<< orphan*/  nfc_llcp_recv_dm (struct nfc_llcp_local*,struct sk_buff*) ; 
 int /*<<< orphan*/  nfc_llcp_recv_hdlc (struct nfc_llcp_local*,struct sk_buff*) ; 
 int /*<<< orphan*/  nfc_llcp_recv_snl (struct nfc_llcp_local*,struct sk_buff*) ; 
 int /*<<< orphan*/  nfc_llcp_recv_ui (struct nfc_llcp_local*,struct sk_buff*) ; 
 int nfc_llcp_ssap (struct sk_buff*) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  print_hex_dump_debug (char*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void nfc_llcp_rx_skb(struct nfc_llcp_local *local, struct sk_buff *skb)
{
	u8 dsap, ssap, ptype;

	ptype = nfc_llcp_ptype(skb);
	dsap = nfc_llcp_dsap(skb);
	ssap = nfc_llcp_ssap(skb);

	pr_debug("ptype 0x%x dsap 0x%x ssap 0x%x\n", ptype, dsap, ssap);

	if (ptype != LLCP_PDU_SYMM)
		print_hex_dump_debug("LLCP Rx: ", DUMP_PREFIX_OFFSET, 16, 1,
				     skb->data, skb->len, true);

	switch (ptype) {
	case LLCP_PDU_SYMM:
		pr_debug("SYMM\n");
		break;

	case LLCP_PDU_UI:
		pr_debug("UI\n");
		nfc_llcp_recv_ui(local, skb);
		break;

	case LLCP_PDU_CONNECT:
		pr_debug("CONNECT\n");
		nfc_llcp_recv_connect(local, skb);
		break;

	case LLCP_PDU_DISC:
		pr_debug("DISC\n");
		nfc_llcp_recv_disc(local, skb);
		break;

	case LLCP_PDU_CC:
		pr_debug("CC\n");
		nfc_llcp_recv_cc(local, skb);
		break;

	case LLCP_PDU_DM:
		pr_debug("DM\n");
		nfc_llcp_recv_dm(local, skb);
		break;

	case LLCP_PDU_SNL:
		pr_debug("SNL\n");
		nfc_llcp_recv_snl(local, skb);
		break;

	case LLCP_PDU_I:
	case LLCP_PDU_RR:
	case LLCP_PDU_RNR:
		pr_debug("I frame\n");
		nfc_llcp_recv_hdlc(local, skb);
		break;

	case LLCP_PDU_AGF:
		pr_debug("AGF frame\n");
		nfc_llcp_recv_agf(local, skb);
		break;
	}
}