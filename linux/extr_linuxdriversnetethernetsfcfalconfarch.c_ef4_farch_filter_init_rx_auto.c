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
struct ef4_nic {scalar_t__ rx_scatter; } ;
struct ef4_farch_filter_spec {int flags; scalar_t__ dmaq_id; int /*<<< orphan*/  priority; } ;

/* Variables and functions */
 int EF4_FILTER_FLAG_RX ; 
 int EF4_FILTER_FLAG_RX_RSS ; 
 int EF4_FILTER_FLAG_RX_SCATTER ; 
 int /*<<< orphan*/  EF4_FILTER_PRI_AUTO ; 
 scalar_t__ ef4_rss_enabled (struct ef4_nic*) ; 

__attribute__((used)) static void
ef4_farch_filter_init_rx_auto(struct ef4_nic *efx,
			      struct ef4_farch_filter_spec *spec)
{
	/* If there's only one channel then disable RSS for non VF
	 * traffic, thereby allowing VFs to use RSS when the PF can't.
	 */
	spec->priority = EF4_FILTER_PRI_AUTO;
	spec->flags = (EF4_FILTER_FLAG_RX |
		       (ef4_rss_enabled(efx) ? EF4_FILTER_FLAG_RX_RSS : 0) |
		       (efx->rx_scatter ? EF4_FILTER_FLAG_RX_SCATTER : 0));
	spec->dmaq_id = 0;
}