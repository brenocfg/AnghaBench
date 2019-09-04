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
struct efx_channel {scalar_t__ sync_events_state; } ;

/* Variables and functions */
 scalar_t__ SYNC_EVENTS_VALID ; 
 int /*<<< orphan*/  __efx_rx_skb_attach_timestamp (struct efx_channel*,struct sk_buff*) ; 

__attribute__((used)) static inline void efx_rx_skb_attach_timestamp(struct efx_channel *channel,
					       struct sk_buff *skb)
{
	if (channel->sync_events_state == SYNC_EVENTS_VALID)
		__efx_rx_skb_attach_timestamp(channel, skb);
}