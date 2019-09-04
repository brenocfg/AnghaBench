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
struct xenvif_queue {int /*<<< orphan*/  inflight_packets; } ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tx_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  SKBTX_DEV_ZEROCOPY ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 

void xenvif_skb_zerocopy_prepare(struct xenvif_queue *queue,
				 struct sk_buff *skb)
{
	skb_shinfo(skb)->tx_flags |= SKBTX_DEV_ZEROCOPY;
	atomic_inc(&queue->inflight_packets);
}