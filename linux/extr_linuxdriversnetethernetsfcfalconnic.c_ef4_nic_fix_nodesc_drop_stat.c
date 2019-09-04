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
typedef  scalar_t__ u64 ;
struct ef4_nic {int rx_nodesc_drops_prev_state; scalar_t__ rx_nodesc_drops_while_down; TYPE_1__* net_dev; scalar_t__ rx_nodesc_drops_total; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int IFF_UP ; 

void ef4_nic_fix_nodesc_drop_stat(struct ef4_nic *efx, u64 *rx_nodesc_drops)
{
	/* if down, or this is the first update after coming up */
	if (!(efx->net_dev->flags & IFF_UP) || !efx->rx_nodesc_drops_prev_state)
		efx->rx_nodesc_drops_while_down +=
			*rx_nodesc_drops - efx->rx_nodesc_drops_total;
	efx->rx_nodesc_drops_total = *rx_nodesc_drops;
	efx->rx_nodesc_drops_prev_state = !!(efx->net_dev->flags & IFF_UP);
	*rx_nodesc_drops -= efx->rx_nodesc_drops_while_down;
}