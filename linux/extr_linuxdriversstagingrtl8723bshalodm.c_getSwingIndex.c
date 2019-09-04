#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
typedef  size_t u32 ;
struct adapter {int dummy; } ;
struct TYPE_3__ {struct adapter* Adapter; } ;
typedef  TYPE_1__* PDM_ODM_T ;

/* Variables and functions */
 size_t* OFDMSwingTable_New ; 
 size_t OFDM_TABLE_SIZE ; 
 size_t PHY_QueryBBReg (struct adapter*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rOFDM0_XATxIQImbalance ; 

__attribute__((used)) static u8 getSwingIndex(PDM_ODM_T pDM_Odm)
{
	struct adapter *Adapter = pDM_Odm->Adapter;
	u8 i = 0;
	u32 bbSwing;
	u32 swingTableSize;
	u32 *pSwingTable;

	bbSwing = PHY_QueryBBReg(Adapter, rOFDM0_XATxIQImbalance, 0xFFC00000);

	pSwingTable = OFDMSwingTable_New;
	swingTableSize = OFDM_TABLE_SIZE;

	for (i = 0; i < swingTableSize; ++i) {
		u32 tableValue = pSwingTable[i];

		if (tableValue >= 0x100000)
			tableValue >>= 22;
		if (bbSwing == tableValue)
			break;
	}
	return i;
}