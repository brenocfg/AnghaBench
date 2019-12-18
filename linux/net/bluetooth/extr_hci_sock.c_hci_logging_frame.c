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
typedef  int u16 ;
struct sock {int dummy; } ;
struct sk_buff {int* data; } ;
struct msghdr {int msg_flags; } ;
struct hci_mon_hdr {int /*<<< orphan*/  opcode; int /*<<< orphan*/  index; int /*<<< orphan*/  len; } ;
struct hci_dev {int dummy; } ;
typedef  int __u8 ;

/* Variables and functions */
 int EFAULT ; 
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  HCI_CHANNEL_MONITOR ; 
 int /*<<< orphan*/  HCI_MON_USER_LOGGING ; 
 int /*<<< orphan*/  HCI_SOCK_TRUSTED ; 
 int MGMT_INDEX_NONE ; 
 int MSG_DONTWAIT ; 
 int __le16_to_cpu (int /*<<< orphan*/ ) ; 
 struct sk_buff* bt_skb_send_alloc (struct sock*,int,int,int*) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 struct hci_dev* hci_dev_get (int) ; 
 int /*<<< orphan*/  hci_dev_put (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_send_to_channel (int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 scalar_t__ memcpy_from_msg (int /*<<< orphan*/ ,struct msghdr*,int) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 

__attribute__((used)) static int hci_logging_frame(struct sock *sk, struct msghdr *msg, int len)
{
	struct hci_mon_hdr *hdr;
	struct sk_buff *skb;
	struct hci_dev *hdev;
	u16 index;
	int err;

	/* The logging frame consists at minimum of the standard header,
	 * the priority byte, the ident length byte and at least one string
	 * terminator NUL byte. Anything shorter are invalid packets.
	 */
	if (len < sizeof(*hdr) + 3)
		return -EINVAL;

	skb = bt_skb_send_alloc(sk, len, msg->msg_flags & MSG_DONTWAIT, &err);
	if (!skb)
		return err;

	if (memcpy_from_msg(skb_put(skb, len), msg, len)) {
		err = -EFAULT;
		goto drop;
	}

	hdr = (void *)skb->data;

	if (__le16_to_cpu(hdr->len) != len - sizeof(*hdr)) {
		err = -EINVAL;
		goto drop;
	}

	if (__le16_to_cpu(hdr->opcode) == 0x0000) {
		__u8 priority = skb->data[sizeof(*hdr)];
		__u8 ident_len = skb->data[sizeof(*hdr) + 1];

		/* Only the priorities 0-7 are valid and with that any other
		 * value results in an invalid packet.
		 *
		 * The priority byte is followed by an ident length byte and
		 * the NUL terminated ident string. Check that the ident
		 * length is not overflowing the packet and also that the
		 * ident string itself is NUL terminated. In case the ident
		 * length is zero, the length value actually doubles as NUL
		 * terminator identifier.
		 *
		 * The message follows the ident string (if present) and
		 * must be NUL terminated. Otherwise it is not a valid packet.
		 */
		if (priority > 7 || skb->data[len - 1] != 0x00 ||
		    ident_len > len - sizeof(*hdr) - 3 ||
		    skb->data[sizeof(*hdr) + ident_len + 1] != 0x00) {
			err = -EINVAL;
			goto drop;
		}
	} else {
		err = -EINVAL;
		goto drop;
	}

	index = __le16_to_cpu(hdr->index);

	if (index != MGMT_INDEX_NONE) {
		hdev = hci_dev_get(index);
		if (!hdev) {
			err = -ENODEV;
			goto drop;
		}
	} else {
		hdev = NULL;
	}

	hdr->opcode = cpu_to_le16(HCI_MON_USER_LOGGING);

	hci_send_to_channel(HCI_CHANNEL_MONITOR, skb, HCI_SOCK_TRUSTED, NULL);
	err = len;

	if (hdev)
		hci_dev_put(hdev);

drop:
	kfree_skb(skb);
	return err;
}