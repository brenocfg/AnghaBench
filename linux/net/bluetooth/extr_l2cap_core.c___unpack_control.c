#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int /*<<< orphan*/  data; } ;
struct l2cap_chan {int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  l2cap; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLAG_EXT_CTRL ; 
 int /*<<< orphan*/  L2CAP_ENH_CTRL_SIZE ; 
 int /*<<< orphan*/  L2CAP_EXT_CTRL_SIZE ; 
 int /*<<< orphan*/  __unpack_enhanced_control (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __unpack_extended_control (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* bt_cb (struct sk_buff*) ; 
 int /*<<< orphan*/  get_unaligned_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_unaligned_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void __unpack_control(struct l2cap_chan *chan,
				    struct sk_buff *skb)
{
	if (test_bit(FLAG_EXT_CTRL, &chan->flags)) {
		__unpack_extended_control(get_unaligned_le32(skb->data),
					  &bt_cb(skb)->l2cap);
		skb_pull(skb, L2CAP_EXT_CTRL_SIZE);
	} else {
		__unpack_enhanced_control(get_unaligned_le16(skb->data),
					  &bt_cb(skb)->l2cap);
		skb_pull(skb, L2CAP_ENH_CTRL_SIZE);
	}
}