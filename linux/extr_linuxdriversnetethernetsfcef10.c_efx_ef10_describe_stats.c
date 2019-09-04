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
 int /*<<< orphan*/  DECLARE_BITMAP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EF10_STAT_COUNT ; 
 int /*<<< orphan*/  efx_ef10_get_stat_mask (struct efx_nic*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efx_ef10_stat_desc ; 
 size_t efx_nic_describe_stats (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mask ; 

__attribute__((used)) static size_t efx_ef10_describe_stats(struct efx_nic *efx, u8 *names)
{
	DECLARE_BITMAP(mask, EF10_STAT_COUNT);

	efx_ef10_get_stat_mask(efx, mask);
	return efx_nic_describe_stats(efx_ef10_stat_desc, EF10_STAT_COUNT,
				      mask, names);
}