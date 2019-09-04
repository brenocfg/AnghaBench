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
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_2__ {scalar_t__ PhyRegPgVersion; } ;
struct hal_com_data {TYPE_1__ odmpriv; } ;
struct adapter {int dummy; } ;
typedef  TYPE_1__* PDM_ODM_T ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_871X (char*,int) ; 
 struct hal_com_data* GET_HAL_DATA (struct adapter*) ; 
 int bMaskH3Bytes ; 
#define  rTxAGC_A_CCK1_Mcs32 142 
#define  rTxAGC_A_Mcs03_Mcs00 141 
#define  rTxAGC_A_Mcs07_Mcs04 140 
#define  rTxAGC_A_Mcs11_Mcs08 139 
#define  rTxAGC_A_Mcs15_Mcs12 138 
#define  rTxAGC_A_Rate18_06 137 
#define  rTxAGC_A_Rate54_24 136 
#define  rTxAGC_B_CCK11_A_CCK2_11 135 
#define  rTxAGC_B_CCK1_55_Mcs32 134 
#define  rTxAGC_B_Mcs03_Mcs00 133 
#define  rTxAGC_B_Mcs07_Mcs04 132 
#define  rTxAGC_B_Mcs11_Mcs08 131 
#define  rTxAGC_B_Mcs15_Mcs12 130 
#define  rTxAGC_B_Rate18_06 129 
#define  rTxAGC_B_Rate54_24 128 

u8 PHY_GetRateSectionIndexOfTxPowerByRate(
	struct adapter *padapter, u32 RegAddr, u32 BitMask
)
{
	struct hal_com_data	*pHalData = GET_HAL_DATA(padapter);
	PDM_ODM_T pDM_Odm = &pHalData->odmpriv;
	u8	index = 0;

	if (pDM_Odm->PhyRegPgVersion == 0) {
		switch (RegAddr) {
		case rTxAGC_A_Rate18_06:
			index = 0;
			break;
		case rTxAGC_A_Rate54_24:
			index = 1;
			break;
		case rTxAGC_A_CCK1_Mcs32:
			index = 6;
			break;
		case rTxAGC_B_CCK11_A_CCK2_11:
			if (BitMask == bMaskH3Bytes)
				index = 7;
			else if (BitMask == 0x000000ff)
				index = 15;
			break;

		case rTxAGC_A_Mcs03_Mcs00:
			index = 2;
			break;
		case rTxAGC_A_Mcs07_Mcs04:
			index = 3;
			break;
		case rTxAGC_A_Mcs11_Mcs08:
			index = 4;
			break;
		case rTxAGC_A_Mcs15_Mcs12:
			index = 5;
			break;
		case rTxAGC_B_Rate18_06:
			index = 8;
			break;
		case rTxAGC_B_Rate54_24:
			index = 9;
			break;
		case rTxAGC_B_CCK1_55_Mcs32:
			index = 14;
			break;
		case rTxAGC_B_Mcs03_Mcs00:
			index = 10;
			break;
		case rTxAGC_B_Mcs07_Mcs04:
			index = 11;
			break;
		case rTxAGC_B_Mcs11_Mcs08:
			index = 12;
			break;
		case rTxAGC_B_Mcs15_Mcs12:
			index = 13;
			break;
		default:
			DBG_871X("Invalid RegAddr 0x3%x in PHY_GetRateSectionIndexOfTxPowerByRate()", RegAddr);
			break;
		}
	}

	return index;
}