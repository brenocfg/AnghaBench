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
typedef  int /*<<< orphan*/  u8 ;
struct efx_nic {int /*<<< orphan*/  ptp_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  PTP_STAT_COUNT ; 
 size_t efx_nic_describe_stats (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efx_ptp_stat_desc ; 
 int /*<<< orphan*/  efx_ptp_stat_mask ; 

size_t efx_ptp_describe_stats(struct efx_nic *efx, u8 *strings)
{
	if (!efx->ptp_data)
		return 0;

	return efx_nic_describe_stats(efx_ptp_stat_desc, PTP_STAT_COUNT,
				      efx_ptp_stat_mask, strings);
}