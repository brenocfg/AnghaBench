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
typedef  scalar_t__ u16 ;
struct sk_buff {scalar_t__ len; scalar_t__ data; } ;
struct l2cap_chan {scalar_t__ fcs; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int EBADMSG ; 
 int /*<<< orphan*/  FLAG_EXT_CTRL ; 
 int L2CAP_ENH_HDR_SIZE ; 
 int L2CAP_EXT_HDR_SIZE ; 
 scalar_t__ L2CAP_FCS_CRC16 ; 
 scalar_t__ L2CAP_FCS_SIZE ; 
 scalar_t__ crc16 (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ get_unaligned_le16 (scalar_t__) ; 
 int /*<<< orphan*/  skb_trim (struct sk_buff*,scalar_t__) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int l2cap_check_fcs(struct l2cap_chan *chan,  struct sk_buff *skb)
{
	u16 our_fcs, rcv_fcs;
	int hdr_size;

	if (test_bit(FLAG_EXT_CTRL, &chan->flags))
		hdr_size = L2CAP_EXT_HDR_SIZE;
	else
		hdr_size = L2CAP_ENH_HDR_SIZE;

	if (chan->fcs == L2CAP_FCS_CRC16) {
		skb_trim(skb, skb->len - L2CAP_FCS_SIZE);
		rcv_fcs = get_unaligned_le16(skb->data + skb->len);
		our_fcs = crc16(0, skb->data - hdr_size, skb->len + hdr_size);

		if (our_fcs != rcv_fcs)
			return -EBADMSG;
	}
	return 0;
}