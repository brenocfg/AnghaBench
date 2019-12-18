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
struct sk_buff {int /*<<< orphan*/  data; } ;
struct nci_dev {int dummy; } ;
typedef  int __u16 ;

/* Variables and functions */
 int /*<<< orphan*/  ENOTSUPP ; 
 int /*<<< orphan*/  NCI_CTRL_HDR_SIZE ; 
 scalar_t__ NCI_GID_PROPRIETARY ; 
#define  NCI_OP_CORE_CONN_CREDITS_NTF 135 
#define  NCI_OP_CORE_GENERIC_ERROR_NTF 134 
#define  NCI_OP_CORE_INTF_ERROR_NTF 133 
#define  NCI_OP_NFCEE_DISCOVER_NTF 132 
#define  NCI_OP_RF_DEACTIVATE_NTF 131 
#define  NCI_OP_RF_DISCOVER_NTF 130 
#define  NCI_OP_RF_INTF_ACTIVATED_NTF 129 
#define  NCI_OP_RF_NFCEE_ACTION_NTF 128 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  nci_core_conn_credits_ntf_packet (struct nci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  nci_core_conn_intf_error_ntf_packet (struct nci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  nci_core_generic_error_ntf_packet (struct nci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  nci_core_ntf_packet (struct nci_dev*,int,struct sk_buff*) ; 
 int /*<<< orphan*/  nci_nfcee_action_ntf_packet (struct nci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  nci_nfcee_discover_ntf_packet (struct nci_dev*,struct sk_buff*) ; 
 int nci_opcode (int /*<<< orphan*/ ) ; 
 scalar_t__ nci_opcode_gid (int) ; 
 int /*<<< orphan*/  nci_opcode_oid (int) ; 
 int /*<<< orphan*/  nci_pbf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nci_plen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nci_prop_ntf_packet (struct nci_dev*,int,struct sk_buff*) ; 
 int /*<<< orphan*/  nci_rf_deactivate_ntf_packet (struct nci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  nci_rf_discover_ntf_packet (struct nci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  nci_rf_intf_activated_ntf_packet (struct nci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int /*<<< orphan*/ ) ; 

void nci_ntf_packet(struct nci_dev *ndev, struct sk_buff *skb)
{
	__u16 ntf_opcode = nci_opcode(skb->data);

	pr_debug("NCI RX: MT=ntf, PBF=%d, GID=0x%x, OID=0x%x, plen=%d\n",
		 nci_pbf(skb->data),
		 nci_opcode_gid(ntf_opcode),
		 nci_opcode_oid(ntf_opcode),
		 nci_plen(skb->data));

	/* strip the nci control header */
	skb_pull(skb, NCI_CTRL_HDR_SIZE);

	if (nci_opcode_gid(ntf_opcode) == NCI_GID_PROPRIETARY) {
		if (nci_prop_ntf_packet(ndev, ntf_opcode, skb) == -ENOTSUPP) {
			pr_err("unsupported ntf opcode 0x%x\n",
			       ntf_opcode);
		}

		goto end;
	}

	switch (ntf_opcode) {
	case NCI_OP_CORE_CONN_CREDITS_NTF:
		nci_core_conn_credits_ntf_packet(ndev, skb);
		break;

	case NCI_OP_CORE_GENERIC_ERROR_NTF:
		nci_core_generic_error_ntf_packet(ndev, skb);
		break;

	case NCI_OP_CORE_INTF_ERROR_NTF:
		nci_core_conn_intf_error_ntf_packet(ndev, skb);
		break;

	case NCI_OP_RF_DISCOVER_NTF:
		nci_rf_discover_ntf_packet(ndev, skb);
		break;

	case NCI_OP_RF_INTF_ACTIVATED_NTF:
		nci_rf_intf_activated_ntf_packet(ndev, skb);
		break;

	case NCI_OP_RF_DEACTIVATE_NTF:
		nci_rf_deactivate_ntf_packet(ndev, skb);
		break;

	case NCI_OP_NFCEE_DISCOVER_NTF:
		nci_nfcee_discover_ntf_packet(ndev, skb);
		break;

	case NCI_OP_RF_NFCEE_ACTION_NTF:
		nci_nfcee_action_ntf_packet(ndev, skb);
		break;

	default:
		pr_err("unknown ntf opcode 0x%x\n", ntf_opcode);
		break;
	}

	nci_core_ntf_packet(ndev, ntf_opcode, skb);
end:
	kfree_skb(skb);
}