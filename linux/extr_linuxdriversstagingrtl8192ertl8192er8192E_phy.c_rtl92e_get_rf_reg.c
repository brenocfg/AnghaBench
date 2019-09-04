#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct r8192_priv {scalar_t__ Rf_Mode; int /*<<< orphan*/  rf_mutex; int /*<<< orphan*/  being_init_adapter; TYPE_1__* rtllib; } ;
struct net_device {int dummy; } ;
typedef  enum rf90_radio_path { ____Placeholder_rf90_radio_path } rf90_radio_path ;
struct TYPE_2__ {scalar_t__ eRFPowerState; } ;

/* Variables and functions */
 scalar_t__ RF_OP_By_FW ; 
 int _rtl92e_calculate_bit_shift (int) ; 
 int _rtl92e_phy_rf_fw_read (struct net_device*,int,int) ; 
 int _rtl92e_phy_rf_read (struct net_device*,int,int) ; 
 scalar_t__ eRfOn ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtl92e_is_legal_rf_path (struct net_device*,int) ; 
 struct r8192_priv* rtllib_priv (struct net_device*) ; 
 int /*<<< orphan*/  udelay (int) ; 

u32 rtl92e_get_rf_reg(struct net_device *dev, enum rf90_radio_path eRFPath,
		      u32 RegAddr, u32 BitMask)
{
	u32 Original_Value, Readback_Value, BitShift;
	struct r8192_priv *priv = rtllib_priv(dev);

	if (!rtl92e_is_legal_rf_path(dev, eRFPath))
		return 0;
	if (priv->rtllib->eRFPowerState != eRfOn && !priv->being_init_adapter)
		return	0;
	mutex_lock(&priv->rf_mutex);
	if (priv->Rf_Mode == RF_OP_By_FW) {
		Original_Value = _rtl92e_phy_rf_fw_read(dev, eRFPath, RegAddr);
		udelay(200);
	} else {
		Original_Value = _rtl92e_phy_rf_read(dev, eRFPath, RegAddr);
	}
	BitShift =  _rtl92e_calculate_bit_shift(BitMask);
	Readback_Value = (Original_Value & BitMask) >> BitShift;
	mutex_unlock(&priv->rf_mutex);
	return Readback_Value;
}