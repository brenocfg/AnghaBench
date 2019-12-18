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
struct l2cap_ctrl {int dummy; } ;
struct l2cap_chan {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLAG_EXT_CTRL ; 
 scalar_t__ L2CAP_HDR_SIZE ; 
 int /*<<< orphan*/  __pack_enhanced_control (struct l2cap_ctrl*) ; 
 int /*<<< orphan*/  __pack_extended_control (struct l2cap_ctrl*) ; 
 int /*<<< orphan*/  put_unaligned_le16 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  put_unaligned_le32 (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void __pack_control(struct l2cap_chan *chan,
				  struct l2cap_ctrl *control,
				  struct sk_buff *skb)
{
	if (test_bit(FLAG_EXT_CTRL, &chan->flags)) {
		put_unaligned_le32(__pack_extended_control(control),
				   skb->data + L2CAP_HDR_SIZE);
	} else {
		put_unaligned_le16(__pack_enhanced_control(control),
				   skb->data + L2CAP_HDR_SIZE);
	}
}