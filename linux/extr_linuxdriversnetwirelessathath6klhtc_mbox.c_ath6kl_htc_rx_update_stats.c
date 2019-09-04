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
struct TYPE_2__ {int /*<<< orphan*/  rx_bundle_lkahd; int /*<<< orphan*/  rx_lkahds; int /*<<< orphan*/  rx_pkts; } ;
struct htc_endpoint {TYPE_1__ ep_st; } ;

/* Variables and functions */

__attribute__((used)) static inline void ath6kl_htc_rx_update_stats(struct htc_endpoint *endpoint,
					      int n_look_ahds)
{
	endpoint->ep_st.rx_pkts++;
	if (n_look_ahds == 1)
		endpoint->ep_st.rx_lkahds++;
	else if (n_look_ahds > 1)
		endpoint->ep_st.rx_bundle_lkahd++;
}