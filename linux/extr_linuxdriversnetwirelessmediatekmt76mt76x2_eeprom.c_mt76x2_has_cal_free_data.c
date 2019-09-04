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
typedef  int u16 ;
struct mt76x2_dev {int dummy; } ;

/* Variables and functions */
 size_t MT_EE_NIC_CONF_0 ; 
 size_t MT_EE_TX_POWER_0_GRP3_TX_POWER_DELTA ; 
 size_t MT_EE_TX_POWER_0_GRP4_TSSI_SLOPE ; 
 size_t MT_EE_TX_POWER_0_START_2G ; 
 size_t MT_EE_TX_POWER_DELTA_BW40 ; 
 size_t MT_EE_XTAL_TRIM_1 ; 

__attribute__((used)) static bool
mt76x2_has_cal_free_data(struct mt76x2_dev *dev, u8 *efuse)
{
	u16 *efuse_w = (u16 *) efuse;

	if (efuse_w[MT_EE_NIC_CONF_0] != 0)
		return false;

	if (efuse_w[MT_EE_XTAL_TRIM_1] == 0xffff)
		return false;

	if (efuse_w[MT_EE_TX_POWER_DELTA_BW40] != 0)
		return false;

	if (efuse_w[MT_EE_TX_POWER_0_START_2G] == 0xffff)
		return false;

	if (efuse_w[MT_EE_TX_POWER_0_GRP3_TX_POWER_DELTA] != 0)
		return false;

	if (efuse_w[MT_EE_TX_POWER_0_GRP4_TSSI_SLOPE] == 0xffff)
		return false;

	return true;
}