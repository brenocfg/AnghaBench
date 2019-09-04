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
struct efx_nic {struct efx_loopback_state* loopback_selftest; } ;
struct efx_loopback_state {scalar_t__ packet_count; int /*<<< orphan*/  rx_good; } ;

/* Variables and functions */
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int efx_poll_loopback(struct efx_nic *efx)
{
	struct efx_loopback_state *state = efx->loopback_selftest;

	return atomic_read(&state->rx_good) == state->packet_count;
}