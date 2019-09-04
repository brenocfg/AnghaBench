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
struct phy_dm_struct {void* adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  phy_set_tx_power_index_by_rs (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void odm_set_tx_power_index_by_rate_section(struct phy_dm_struct *dm,
					    u8 rf_path, u8 channel,
					    u8 rate_section)
{
	void *adapter = dm->adapter;

	phy_set_tx_power_index_by_rs(adapter, channel, rf_path, rate_section);
}