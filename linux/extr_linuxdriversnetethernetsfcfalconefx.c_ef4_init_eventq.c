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
struct ef4_nic {TYPE_1__* type; int /*<<< orphan*/  net_dev; } ;
struct ef4_channel {int eventq_init; scalar_t__ eventq_read_ptr; int /*<<< orphan*/  channel; struct ef4_nic* efx; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* push_irq_moderation ) (struct ef4_channel*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  EF4_WARN_ON_PARANOID (int) ; 
 int /*<<< orphan*/  drv ; 
 int ef4_nic_init_eventq (struct ef4_channel*) ; 
 int /*<<< orphan*/  netif_dbg (struct ef4_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct ef4_channel*) ; 

__attribute__((used)) static int ef4_init_eventq(struct ef4_channel *channel)
{
	struct ef4_nic *efx = channel->efx;
	int rc;

	EF4_WARN_ON_PARANOID(channel->eventq_init);

	netif_dbg(efx, drv, efx->net_dev,
		  "chan %d init event queue\n", channel->channel);

	rc = ef4_nic_init_eventq(channel);
	if (rc == 0) {
		efx->type->push_irq_moderation(channel);
		channel->eventq_read_ptr = 0;
		channel->eventq_init = true;
	}
	return rc;
}