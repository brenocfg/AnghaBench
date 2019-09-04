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
struct sk_buff {int dummy; } ;
struct l2cap_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct sk_buff* bt_skb_alloc (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sk_buff *chan_alloc_skb_cb(struct l2cap_chan *chan,
					 unsigned long hdr_len,
					 unsigned long len, int nb)
{
	/* Note that we must allocate using GFP_ATOMIC here as
	 * this function is called originally from netdev hard xmit
	 * function in atomic context.
	 */
	return bt_skb_alloc(hdr_len + len, GFP_ATOMIC);
}