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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct r8192_priv {scalar_t__ rf_type; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int AGCTAB_ArrayLength ; 
 scalar_t__ BaseBand_Config_AGC_TAB ; 
 scalar_t__ BaseBand_Config_PHY_REG ; 
 int /*<<< orphan*/  COMP_DBG ; 
 int PHY_REGArrayLength ; 
 int PHY_REG_1T2RArrayLength ; 
 scalar_t__ RF_1T2R ; 
 scalar_t__ RF_2T4R ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * Rtl819XAGCTAB_Array ; 
 int /*<<< orphan*/ * Rtl819XPHY_REGArray ; 
 int /*<<< orphan*/ * Rtl819XPHY_REG_1T2RArray ; 
 int /*<<< orphan*/  bMaskDWord ; 
 int /*<<< orphan*/  rtl92e_set_bb_reg (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct r8192_priv* rtllib_priv (struct net_device*) ; 

__attribute__((used)) static void _rtl92e_phy_config_bb(struct net_device *dev, u8 ConfigType)
{
	int i;
	u32 *Rtl819XPHY_REGArray_Table = NULL;
	u32 *Rtl819XAGCTAB_Array_Table = NULL;
	u16 AGCTAB_ArrayLen, PHY_REGArrayLen = 0;
	struct r8192_priv *priv = rtllib_priv(dev);

	AGCTAB_ArrayLen = AGCTAB_ArrayLength;
	Rtl819XAGCTAB_Array_Table = Rtl819XAGCTAB_Array;
	if (priv->rf_type == RF_2T4R) {
		PHY_REGArrayLen = PHY_REGArrayLength;
		Rtl819XPHY_REGArray_Table = Rtl819XPHY_REGArray;
	} else if (priv->rf_type == RF_1T2R) {
		PHY_REGArrayLen = PHY_REG_1T2RArrayLength;
		Rtl819XPHY_REGArray_Table = Rtl819XPHY_REG_1T2RArray;
	}

	if (ConfigType == BaseBand_Config_PHY_REG) {
		for (i = 0; i < PHY_REGArrayLen; i += 2) {
			rtl92e_set_bb_reg(dev, Rtl819XPHY_REGArray_Table[i],
					  bMaskDWord,
					  Rtl819XPHY_REGArray_Table[i+1]);
			RT_TRACE(COMP_DBG,
				 "i: %x, The Rtl819xUsbPHY_REGArray[0] is %x Rtl819xUsbPHY_REGArray[1] is %x\n",
				 i, Rtl819XPHY_REGArray_Table[i],
				 Rtl819XPHY_REGArray_Table[i+1]);
		}
	} else if (ConfigType == BaseBand_Config_AGC_TAB) {
		for (i = 0; i < AGCTAB_ArrayLen; i += 2) {
			rtl92e_set_bb_reg(dev, Rtl819XAGCTAB_Array_Table[i],
					  bMaskDWord,
					  Rtl819XAGCTAB_Array_Table[i+1]);
			RT_TRACE(COMP_DBG,
				 "i:%x, The rtl819XAGCTAB_Array[0] is %x rtl819XAGCTAB_Array[1] is %x\n",
				 i, Rtl819XAGCTAB_Array_Table[i],
				 Rtl819XAGCTAB_Array_Table[i+1]);
		}
	}
}