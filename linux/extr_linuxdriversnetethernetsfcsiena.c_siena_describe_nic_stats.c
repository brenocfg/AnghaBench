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
struct efx_nic {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIENA_STAT_COUNT ; 
 size_t efx_nic_describe_stats (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  siena_stat_desc ; 
 int /*<<< orphan*/  siena_stat_mask ; 

__attribute__((used)) static size_t siena_describe_nic_stats(struct efx_nic *efx, u8 *names)
{
	return efx_nic_describe_stats(siena_stat_desc, SIENA_STAT_COUNT,
				      siena_stat_mask, names);
}