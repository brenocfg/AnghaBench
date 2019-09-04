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
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int* data; } ;
struct nfc_target {int hci_reader_gate; int sel_res; int nfcid1_len; int /*<<< orphan*/  nfcid1; void* supported_protocols; void* sens_res; } ;
struct nfc_hci_dev {int /*<<< orphan*/  ndev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t MICROREAD_EMCF_A3_ATQA ; 
 size_t MICROREAD_EMCF_A3_LEN ; 
 size_t MICROREAD_EMCF_A3_SAK ; 
 size_t MICROREAD_EMCF_A3_UID ; 
 size_t MICROREAD_EMCF_A_ATQA ; 
 size_t MICROREAD_EMCF_A_LEN ; 
 size_t MICROREAD_EMCF_A_SAK ; 
 size_t MICROREAD_EMCF_A_UID ; 
 size_t MICROREAD_EMCF_B_UID ; 
 size_t MICROREAD_EMCF_T1_ATQA ; 
 size_t MICROREAD_EMCF_T1_UID ; 
 size_t MICROREAD_EMCF_T3_UID ; 
#define  MICROREAD_GATE_ID_MREAD_ISO_A 132 
#define  MICROREAD_GATE_ID_MREAD_ISO_A_3 131 
#define  MICROREAD_GATE_ID_MREAD_ISO_B 130 
#define  MICROREAD_GATE_ID_MREAD_NFC_T1 129 
#define  MICROREAD_GATE_ID_MREAD_NFC_T3 128 
 void* NFC_PROTO_FELICA_MASK ; 
 void* NFC_PROTO_ISO14443_B_MASK ; 
 void* NFC_PROTO_JEWEL_MASK ; 
 void* be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct nfc_target*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct nfc_target* kzalloc (int,int /*<<< orphan*/ ) ; 
 void* le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int) ; 
 void* nfc_hci_sak_to_protocol (int) ; 
 int nfc_targets_found (int /*<<< orphan*/ ,struct nfc_target*,int) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  pr_info (char*,int) ; 

__attribute__((used)) static void microread_target_discovered(struct nfc_hci_dev *hdev, u8 gate,
					struct sk_buff *skb)
{
	struct nfc_target *targets;
	int r = 0;

	pr_info("target discovered to gate 0x%x\n", gate);

	targets = kzalloc(sizeof(struct nfc_target), GFP_KERNEL);
	if (targets == NULL) {
		r = -ENOMEM;
		goto exit;
	}

	targets->hci_reader_gate = gate;

	switch (gate) {
	case MICROREAD_GATE_ID_MREAD_ISO_A:
		targets->supported_protocols =
		      nfc_hci_sak_to_protocol(skb->data[MICROREAD_EMCF_A_SAK]);
		targets->sens_res =
			 be16_to_cpu(*(u16 *)&skb->data[MICROREAD_EMCF_A_ATQA]);
		targets->sel_res = skb->data[MICROREAD_EMCF_A_SAK];
		targets->nfcid1_len = skb->data[MICROREAD_EMCF_A_LEN];
		if (targets->nfcid1_len > sizeof(targets->nfcid1)) {
			r = -EINVAL;
			goto exit_free;
		}
		memcpy(targets->nfcid1, &skb->data[MICROREAD_EMCF_A_UID],
		       targets->nfcid1_len);
		break;
	case MICROREAD_GATE_ID_MREAD_ISO_A_3:
		targets->supported_protocols =
		      nfc_hci_sak_to_protocol(skb->data[MICROREAD_EMCF_A3_SAK]);
		targets->sens_res =
			 be16_to_cpu(*(u16 *)&skb->data[MICROREAD_EMCF_A3_ATQA]);
		targets->sel_res = skb->data[MICROREAD_EMCF_A3_SAK];
		targets->nfcid1_len = skb->data[MICROREAD_EMCF_A3_LEN];
		if (targets->nfcid1_len > sizeof(targets->nfcid1)) {
			r = -EINVAL;
			goto exit_free;
		}
		memcpy(targets->nfcid1, &skb->data[MICROREAD_EMCF_A3_UID],
		       targets->nfcid1_len);
		break;
	case MICROREAD_GATE_ID_MREAD_ISO_B:
		targets->supported_protocols = NFC_PROTO_ISO14443_B_MASK;
		memcpy(targets->nfcid1, &skb->data[MICROREAD_EMCF_B_UID], 4);
		targets->nfcid1_len = 4;
		break;
	case MICROREAD_GATE_ID_MREAD_NFC_T1:
		targets->supported_protocols = NFC_PROTO_JEWEL_MASK;
		targets->sens_res =
			le16_to_cpu(*(u16 *)&skb->data[MICROREAD_EMCF_T1_ATQA]);
		memcpy(targets->nfcid1, &skb->data[MICROREAD_EMCF_T1_UID], 4);
		targets->nfcid1_len = 4;
		break;
	case MICROREAD_GATE_ID_MREAD_NFC_T3:
		targets->supported_protocols = NFC_PROTO_FELICA_MASK;
		memcpy(targets->nfcid1, &skb->data[MICROREAD_EMCF_T3_UID], 8);
		targets->nfcid1_len = 8;
		break;
	default:
		pr_info("discard target discovered to gate 0x%x\n", gate);
		goto exit_free;
	}

	r = nfc_targets_found(hdev->ndev, targets, 1);

exit_free:
	kfree(targets);

exit:
	kfree_skb(skb);

	if (r)
		pr_err("Failed to handle discovered target err=%d\n", r);
}