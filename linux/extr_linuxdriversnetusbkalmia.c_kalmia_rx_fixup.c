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
struct usbnet {int /*<<< orphan*/  net; } ;
struct sk_buff {int len; int* data; } ;
typedef  int /*<<< orphan*/  HEADER_END_OF_USB_PACKET ;
typedef  int /*<<< orphan*/  EXPECTED_UNKNOWN_HEADER_2 ;
typedef  int /*<<< orphan*/  EXPECTED_UNKNOWN_HEADER_1 ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int KALMIA_HEADER_LENGTH ; 
 int get_unaligned_le16 (int*) ; 
 scalar_t__ memcmp (int*,int const*,int) ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,int*,int) ; 
 struct sk_buff* skb_clone (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_trim (struct sk_buff*,int) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  usbnet_skb_return (struct usbnet*,struct sk_buff*) ; 

__attribute__((used)) static int
kalmia_rx_fixup(struct usbnet *dev, struct sk_buff *skb)
{
	/*
	 * Our task here is to strip off framing, leaving skb with one
	 * data frame for the usbnet framework code to process.
	 */
	static const u8 HEADER_END_OF_USB_PACKET[] =
		{ 0x57, 0x5a, 0x00, 0x00, 0x08, 0x00 };
	static const u8 EXPECTED_UNKNOWN_HEADER_1[] =
		{ 0x57, 0x43, 0x1e, 0x00, 0x15, 0x02 };
	static const u8 EXPECTED_UNKNOWN_HEADER_2[] =
		{ 0x57, 0x50, 0x0e, 0x00, 0x00, 0x00 };
	int i = 0;

	/* incomplete header? */
	if (skb->len < KALMIA_HEADER_LENGTH)
		return 0;

	do {
		struct sk_buff *skb2 = NULL;
		u8 *header_start;
		u16 usb_packet_length, ether_packet_length;
		int is_last;

		header_start = skb->data;

		if (unlikely(header_start[0] != 0x57 || header_start[1] != 0x44)) {
			if (!memcmp(header_start, EXPECTED_UNKNOWN_HEADER_1,
				sizeof(EXPECTED_UNKNOWN_HEADER_1)) || !memcmp(
				header_start, EXPECTED_UNKNOWN_HEADER_2,
				sizeof(EXPECTED_UNKNOWN_HEADER_2))) {
				netdev_dbg(dev->net,
					"Received expected unknown frame header: %6phC. Package length: %i\n",
					header_start,
					skb->len - KALMIA_HEADER_LENGTH);
			}
			else {
				netdev_err(dev->net,
					"Received unknown frame header: %6phC. Package length: %i\n",
					header_start,
					skb->len - KALMIA_HEADER_LENGTH);
				return 0;
			}
		}
		else
			netdev_dbg(dev->net,
				"Received header: %6phC. Package length: %i\n",
				header_start, skb->len - KALMIA_HEADER_LENGTH);

		/* subtract start header and end header */
		usb_packet_length = skb->len - (2 * KALMIA_HEADER_LENGTH);
		ether_packet_length = get_unaligned_le16(&header_start[2]);
		skb_pull(skb, KALMIA_HEADER_LENGTH);

		/* Some small packets misses end marker */
		if (usb_packet_length < ether_packet_length) {
			ether_packet_length = usb_packet_length
				+ KALMIA_HEADER_LENGTH;
			is_last = true;
		}
		else {
			netdev_dbg(dev->net, "Correct package length #%i", i
				+ 1);

			is_last = (memcmp(skb->data + ether_packet_length,
				HEADER_END_OF_USB_PACKET,
				sizeof(HEADER_END_OF_USB_PACKET)) == 0);
			if (!is_last) {
				header_start = skb->data + ether_packet_length;
				netdev_dbg(dev->net,
					"End header: %6phC. Package length: %i\n",
					header_start,
					skb->len - KALMIA_HEADER_LENGTH);
			}
		}

		if (is_last) {
			skb2 = skb;
		}
		else {
			skb2 = skb_clone(skb, GFP_ATOMIC);
			if (unlikely(!skb2))
				return 0;
		}

		skb_trim(skb2, ether_packet_length);

		if (is_last) {
			return 1;
		}
		else {
			usbnet_skb_return(dev, skb2);
			skb_pull(skb, ether_packet_length);
		}

		i++;
	}
	while (skb->len);

	return 1;
}