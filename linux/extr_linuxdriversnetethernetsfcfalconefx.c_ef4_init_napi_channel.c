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
struct ef4_nic {int /*<<< orphan*/  net_dev; } ;
struct ef4_channel {int /*<<< orphan*/  napi_str; int /*<<< orphan*/  napi_dev; struct ef4_nic* efx; } ;

/* Variables and functions */
 int /*<<< orphan*/  ef4_poll ; 
 int /*<<< orphan*/  napi_weight ; 
 int /*<<< orphan*/  netif_napi_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ef4_init_napi_channel(struct ef4_channel *channel)
{
	struct ef4_nic *efx = channel->efx;

	channel->napi_dev = efx->net_dev;
	netif_napi_add(channel->napi_dev, &channel->napi_str,
		       ef4_poll, napi_weight);
}