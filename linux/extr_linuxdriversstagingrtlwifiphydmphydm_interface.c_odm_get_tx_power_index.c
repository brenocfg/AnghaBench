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
typedef  scalar_t__ u8 ;
struct phy_dm_struct {void* adapter; } ;
typedef  enum odm_rf_radio_path { ____Placeholder_odm_rf_radio_path } odm_rf_radio_path ;

/* Variables and functions */
 scalar_t__ phy_get_tx_power_index (void*,int,scalar_t__,scalar_t__,scalar_t__) ; 

u8 odm_get_tx_power_index(struct phy_dm_struct *dm, u8 rf_path, u8 tx_rate,
			  u8 band_width, u8 channel)
{
	void *adapter = dm->adapter;

	return phy_get_tx_power_index(adapter, (enum odm_rf_radio_path)rf_path,
				      tx_rate, band_width, channel);
}