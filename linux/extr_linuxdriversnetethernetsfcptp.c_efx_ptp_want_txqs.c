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
struct efx_channel {int /*<<< orphan*/  efx; } ;

/* Variables and functions */
 int efx_ptp_use_mac_tx_timestamps (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool efx_ptp_want_txqs(struct efx_channel *channel)
{
	return efx_ptp_use_mac_tx_timestamps(channel->efx);
}