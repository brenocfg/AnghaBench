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
struct phy_dm_struct {int support_ic_type; } ;
typedef  enum odm_rf_radio_path { ____Placeholder_odm_rf_radio_path } odm_rf_radio_path ;

/* Variables and functions */
 int ODM_RTL8822B ; 
 int /*<<< orphan*/  config_phydm_read_txagc_8822b (struct phy_dm_struct*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8 phydm_api_get_txagc(struct phy_dm_struct *dm,
			      enum odm_rf_radio_path path, u8 hw_rate)
{
	u8 ret = 0;

	if (dm->support_ic_type & ODM_RTL8822B)
		ret = config_phydm_read_txagc_8822b(dm, path, hw_rate);

	return ret;
}