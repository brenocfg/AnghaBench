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
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int csum_unnecessary; } ;

/* Variables and functions */
 int /*<<< orphan*/  skb_shared (struct sk_buff*) ; 
 TYPE_1__* udp_skb_scratch (struct sk_buff*) ; 

__attribute__((used)) static void udp_skb_csum_unnecessary_set(struct sk_buff *skb)
{
	/* We come here after udp_lib_checksum_complete() returned 0.
	 * This means that __skb_checksum_complete() might have
	 * set skb->csum_valid to 1.
	 * On 64bit platforms, we can set csum_unnecessary
	 * to true, but only if the skb is not shared.
	 */
#if BITS_PER_LONG == 64
	if (!skb_shared(skb))
		udp_skb_scratch(skb)->csum_unnecessary = true;
#endif
}