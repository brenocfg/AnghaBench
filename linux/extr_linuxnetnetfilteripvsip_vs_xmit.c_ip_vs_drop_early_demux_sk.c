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
struct sk_buff {scalar_t__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  skb_orphan (struct sk_buff*) ; 

__attribute__((used)) static inline void ip_vs_drop_early_demux_sk(struct sk_buff *skb)
{
	/* If dev is set, the packet came from the LOCAL_IN callback and
	 * not from a local TCP socket.
	 */
	if (skb->dev)
		skb_orphan(skb);
}