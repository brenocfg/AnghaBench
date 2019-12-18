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
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {scalar_t__* data; } ;

/* Variables and functions */
 scalar_t__ GARP_END_MARK ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 

__attribute__((used)) static int garp_pdu_parse_end_mark(struct sk_buff *skb)
{
	if (!pskb_may_pull(skb, sizeof(u8)))
		return -1;
	if (*skb->data == GARP_END_MARK) {
		skb_pull(skb, sizeof(u8));
		return -1;
	}
	return 0;
}