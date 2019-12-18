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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int dummy; } ;
struct hci_dev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  bt_dev_err (struct hci_dev*,char*,...) ; 
 int hci_opcode_ogf (int /*<<< orphan*/ ) ; 
 struct sk_buff* hci_prepare_cmd (struct hci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  hci_send_frame (struct hci_dev*,struct sk_buff*) ; 

int __hci_cmd_send(struct hci_dev *hdev, u16 opcode, u32 plen,
		   const void *param)
{
	struct sk_buff *skb;

	if (hci_opcode_ogf(opcode) != 0x3f) {
		/* A controller receiving a command shall respond with either
		 * a Command Status Event or a Command Complete Event.
		 * Therefore, all standard HCI commands must be sent via the
		 * standard API, using hci_send_cmd or hci_cmd_sync helpers.
		 * Some vendors do not comply with this rule for vendor-specific
		 * commands and do not return any event. We want to support
		 * unresponded commands for such cases only.
		 */
		bt_dev_err(hdev, "unresponded command not supported");
		return -EINVAL;
	}

	skb = hci_prepare_cmd(hdev, opcode, plen, param);
	if (!skb) {
		bt_dev_err(hdev, "no memory for command (opcode 0x%4.4x)",
			   opcode);
		return -ENOMEM;
	}

	hci_send_frame(hdev, skb);

	return 0;
}