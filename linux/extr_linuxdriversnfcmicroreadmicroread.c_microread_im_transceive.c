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
typedef  int u16 ;
struct sk_buff {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct nfc_target {int hci_reader_gate; } ;
struct nfc_hci_dev {int dummy; } ;
struct microread_info {void* async_cb_context; int /*<<< orphan*/  async_cb; int /*<<< orphan*/  async_cb_type; } ;
typedef  int /*<<< orphan*/  data_exchange_cb_t ;

/* Variables and functions */
 int /*<<< orphan*/  MICROREAD_CB_TYPE_READER_ALL ; 
 int /*<<< orphan*/  MICROREAD_CMD_MREAD_EXCHANGE ; 
 int /*<<< orphan*/  MICROREAD_EVT_P2P_INITIATOR_EXCHANGE_TO_RF ; 
#define  MICROREAD_GATE_ID_MREAD_ISO_A 132 
#define  MICROREAD_GATE_ID_MREAD_ISO_A_3 131 
#define  MICROREAD_GATE_ID_MREAD_ISO_B 130 
#define  MICROREAD_GATE_ID_MREAD_NFC_T1 129 
#define  MICROREAD_GATE_ID_MREAD_NFC_T3 128 
 int MICROREAD_GATE_ID_P2P_INITIATOR ; 
 int crc_ccitt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  microread_im_transceive_cb ; 
 struct microread_info* nfc_hci_get_clientdata (struct nfc_hci_dev*) ; 
 int nfc_hci_send_cmd_async (struct nfc_hci_dev*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct microread_info*) ; 
 int nfc_hci_send_event (struct nfc_hci_dev*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,int) ; 
 scalar_t__ skb_push (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_put_u8 (struct sk_buff*,int) ; 

__attribute__((used)) static int microread_im_transceive(struct nfc_hci_dev *hdev,
				   struct nfc_target *target,
				   struct sk_buff *skb, data_exchange_cb_t cb,
				   void *cb_context)
{
	struct microread_info *info = nfc_hci_get_clientdata(hdev);
	u8 control_bits;
	u16 crc;

	pr_info("data exchange to gate 0x%x\n", target->hci_reader_gate);

	if (target->hci_reader_gate == MICROREAD_GATE_ID_P2P_INITIATOR) {
		*(u8 *)skb_push(skb, 1) = 0;

		return nfc_hci_send_event(hdev, target->hci_reader_gate,
				     MICROREAD_EVT_P2P_INITIATOR_EXCHANGE_TO_RF,
				     skb->data, skb->len);
	}

	switch (target->hci_reader_gate) {
	case MICROREAD_GATE_ID_MREAD_ISO_A:
		control_bits = 0xCB;
		break;
	case MICROREAD_GATE_ID_MREAD_ISO_A_3:
		control_bits = 0xCB;
		break;
	case MICROREAD_GATE_ID_MREAD_ISO_B:
		control_bits = 0xCB;
		break;
	case MICROREAD_GATE_ID_MREAD_NFC_T1:
		control_bits = 0x1B;

		crc = crc_ccitt(0xffff, skb->data, skb->len);
		crc = ~crc;
		skb_put_u8(skb, crc & 0xff);
		skb_put_u8(skb, crc >> 8);
		break;
	case MICROREAD_GATE_ID_MREAD_NFC_T3:
		control_bits = 0xDB;
		break;
	default:
		pr_info("Abort im_transceive to invalid gate 0x%x\n",
			target->hci_reader_gate);
		return 1;
	}

	*(u8 *)skb_push(skb, 1) = control_bits;

	info->async_cb_type = MICROREAD_CB_TYPE_READER_ALL;
	info->async_cb = cb;
	info->async_cb_context = cb_context;

	return nfc_hci_send_cmd_async(hdev, target->hci_reader_gate,
				      MICROREAD_CMD_MREAD_EXCHANGE,
				      skb->data, skb->len,
				      microread_im_transceive_cb, info);
}