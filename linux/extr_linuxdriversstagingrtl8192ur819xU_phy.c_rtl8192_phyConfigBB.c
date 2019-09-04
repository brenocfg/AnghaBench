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
typedef  int u32 ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int AGCTAB_ArrayLength ; 
 scalar_t__ BaseBand_Config_AGC_TAB ; 
 scalar_t__ BaseBand_Config_PHY_REG ; 
 int /*<<< orphan*/  COMP_DBG ; 
 int PHY_REG_1T2RArrayLength ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * Rtl8192UsbAGCTAB_Array ; 
 int /*<<< orphan*/ * Rtl8192UsbPHY_REG_1T2RArray ; 
 int /*<<< orphan*/  bMaskDWord ; 
 int /*<<< orphan*/  rtl8192_setBBreg (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void rtl8192_phyConfigBB(struct net_device *dev, u8 ConfigType)
{
	u32 i;

#ifdef TO_DO_LIST
	u32 *rtl8192PhyRegArrayTable = NULL, *rtl8192AgcTabArrayTable = NULL;

	if (Adapter->bInHctTest) {
		PHY_REGArrayLen = PHY_REGArrayLengthDTM;
		AGCTAB_ArrayLen = AGCTAB_ArrayLengthDTM;
		Rtl8190PHY_REGArray_Table = Rtl819XPHY_REGArrayDTM;
		Rtl8190AGCTAB_Array_Table = Rtl819XAGCTAB_ArrayDTM;
	}
#endif
	if (ConfigType == BaseBand_Config_PHY_REG) {
		for (i = 0; i < PHY_REG_1T2RArrayLength; i += 2) {
			rtl8192_setBBreg(dev, Rtl8192UsbPHY_REG_1T2RArray[i],
					 bMaskDWord,
					 Rtl8192UsbPHY_REG_1T2RArray[i+1]);
			RT_TRACE(COMP_DBG,
				 "i: %x, Rtl819xUsbPHY_REGArray[0]=%x Rtl819xUsbPHY_REGArray[1]=%x\n",
				 i, Rtl8192UsbPHY_REG_1T2RArray[i],
				 Rtl8192UsbPHY_REG_1T2RArray[i+1]);
		}
	} else if (ConfigType == BaseBand_Config_AGC_TAB) {
		for (i = 0; i < AGCTAB_ArrayLength; i += 2) {
			rtl8192_setBBreg(dev, Rtl8192UsbAGCTAB_Array[i],
					 bMaskDWord, Rtl8192UsbAGCTAB_Array[i+1]);
			RT_TRACE(COMP_DBG,
				 "i: %x, Rtl8192UsbAGCTAB_Array[0]=%x Rtl8192UsbAGCTAB_Array[1]=%x\n",
				 i, Rtl8192UsbAGCTAB_Array[i],
				 Rtl8192UsbAGCTAB_Array[i+1]);
		}
	}
}