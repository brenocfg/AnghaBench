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
struct xlgmac_pdata {unsigned int channel_count; struct xlgmac_channel* channel_head; } ;
struct xlgmac_channel {int /*<<< orphan*/  tx_timer; int /*<<< orphan*/  tx_ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void xlgmac_stop_timers(struct xlgmac_pdata *pdata)
{
	struct xlgmac_channel *channel;
	unsigned int i;

	channel = pdata->channel_head;
	for (i = 0; i < pdata->channel_count; i++, channel++) {
		if (!channel->tx_ring)
			break;

		del_timer_sync(&channel->tx_timer);
	}
}