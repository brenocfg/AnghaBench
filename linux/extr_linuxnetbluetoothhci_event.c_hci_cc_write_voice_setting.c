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
struct sk_buff {scalar_t__ data; } ;
struct hci_dev {scalar_t__ voice_setting; int /*<<< orphan*/  (* notify ) (struct hci_dev*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  name; } ;
typedef  scalar_t__ __u8 ;
typedef  scalar_t__ __u16 ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  HCI_NOTIFY_VOICE_SETTING ; 
 int /*<<< orphan*/  HCI_OP_WRITE_VOICE_SETTING ; 
 scalar_t__ get_unaligned_le16 (void*) ; 
 void* hci_sent_cmd_data (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct hci_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hci_cc_write_voice_setting(struct hci_dev *hdev,
				       struct sk_buff *skb)
{
	__u8 status = *((__u8 *) skb->data);
	__u16 setting;
	void *sent;

	BT_DBG("%s status 0x%2.2x", hdev->name, status);

	if (status)
		return;

	sent = hci_sent_cmd_data(hdev, HCI_OP_WRITE_VOICE_SETTING);
	if (!sent)
		return;

	setting = get_unaligned_le16(sent);

	if (hdev->voice_setting == setting)
		return;

	hdev->voice_setting = setting;

	BT_DBG("%s voice setting 0x%4.4x", hdev->name, setting);

	if (hdev->notify)
		hdev->notify(hdev, HCI_NOTIFY_VOICE_SETTING);
}