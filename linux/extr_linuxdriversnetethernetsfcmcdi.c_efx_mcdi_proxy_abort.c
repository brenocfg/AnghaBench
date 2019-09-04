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
struct efx_mcdi_iface {scalar_t__ state; int /*<<< orphan*/  proxy_rx_wq; int /*<<< orphan*/  proxy_rx_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINTR ; 
 scalar_t__ MCDI_STATE_PROXY_WAIT ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void efx_mcdi_proxy_abort(struct efx_mcdi_iface *mcdi)
{
	if (mcdi->state == MCDI_STATE_PROXY_WAIT) {
		/* Interrupt the proxy wait. */
		mcdi->proxy_rx_status = -EINTR;
		wake_up(&mcdi->proxy_rx_wq);
	}
}