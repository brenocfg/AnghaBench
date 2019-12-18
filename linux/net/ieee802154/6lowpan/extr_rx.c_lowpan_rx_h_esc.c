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
struct sk_buff {TYPE_1__* dev; } ;
typedef  int /*<<< orphan*/  lowpan_rx_result ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  RX_CONTINUE ; 
 int /*<<< orphan*/  RX_DROP_UNUSABLE ; 
 int /*<<< orphan*/  lowpan_is_esc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  net_warn_ratelimited (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * skb_network_header (struct sk_buff*) ; 

__attribute__((used)) static lowpan_rx_result lowpan_rx_h_esc(struct sk_buff *skb)
{
	if (!lowpan_is_esc(*skb_network_header(skb)))
		return RX_CONTINUE;

	net_warn_ratelimited("%s: %s\n", skb->dev->name,
			     "6LoWPAN ESC not supported\n");

	return RX_DROP_UNUSABLE;
}