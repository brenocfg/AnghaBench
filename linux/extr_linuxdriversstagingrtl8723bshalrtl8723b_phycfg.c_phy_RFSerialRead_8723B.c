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
struct hal_com_data {struct bb_register_def* PHYRegDef; } ;
struct bb_register_def {int rfLSSIReadBackPi; int rfLSSIReadBack; } ;
struct adapter {int dummy; } ;
typedef  enum RF_PATH { ____Placeholder_RF_PATH } RF_PATH ;

/* Variables and functions */
 int /*<<< orphan*/  BIT8 ; 
 struct hal_com_data* GET_HAL_DATA (struct adapter*) ; 
 int MAX_STALL_TIME ; 
 int PHY_QueryBBReg (struct adapter*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PHY_SetBBReg (struct adapter*,int,int /*<<< orphan*/ ,int) ; 
 int RF_PATH_A ; 
 int RF_PATH_B ; 
 int bLSSIReadAddress ; 
 int /*<<< orphan*/  bLSSIReadBackData ; 
 int bLSSIReadEdge ; 
 int /*<<< orphan*/  bMaskDWord ; 
 int rFPGA0_XA_HSSIParameter1 ; 
 int rFPGA0_XA_HSSIParameter2 ; 
 int rFPGA0_XB_HSSIParameter1 ; 
 int rFPGA0_XB_HSSIParameter2 ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static u32 phy_RFSerialRead_8723B(
	struct adapter *Adapter, enum RF_PATH eRFPath, u32 Offset
)
{
	u32 retValue = 0;
	struct hal_com_data *pHalData = GET_HAL_DATA(Adapter);
	struct bb_register_def *pPhyReg = &pHalData->PHYRegDef[eRFPath];
	u32 NewOffset;
	u32 tmplong2;
	u8 RfPiEnable = 0;
	u32 MaskforPhySet = 0;
	int i = 0;

	/*  */
	/*  Make sure RF register offset is correct */
	/*  */
	Offset &= 0xff;

	NewOffset = Offset;

	if (eRFPath == RF_PATH_A) {
		tmplong2 = PHY_QueryBBReg(Adapter, rFPGA0_XA_HSSIParameter2|MaskforPhySet, bMaskDWord);
		tmplong2 = (tmplong2 & (~bLSSIReadAddress)) | (NewOffset<<23) | bLSSIReadEdge;	/* T65 RF */
		PHY_SetBBReg(Adapter, rFPGA0_XA_HSSIParameter2|MaskforPhySet, bMaskDWord, tmplong2&(~bLSSIReadEdge));
	} else {
		tmplong2 = PHY_QueryBBReg(Adapter, rFPGA0_XB_HSSIParameter2|MaskforPhySet, bMaskDWord);
		tmplong2 = (tmplong2 & (~bLSSIReadAddress)) | (NewOffset<<23) | bLSSIReadEdge;	/* T65 RF */
		PHY_SetBBReg(Adapter, rFPGA0_XB_HSSIParameter2|MaskforPhySet, bMaskDWord, tmplong2&(~bLSSIReadEdge));
	}

	tmplong2 = PHY_QueryBBReg(Adapter, rFPGA0_XA_HSSIParameter2|MaskforPhySet, bMaskDWord);
	PHY_SetBBReg(Adapter, rFPGA0_XA_HSSIParameter2|MaskforPhySet, bMaskDWord, tmplong2 & (~bLSSIReadEdge));
	PHY_SetBBReg(Adapter, rFPGA0_XA_HSSIParameter2|MaskforPhySet, bMaskDWord, tmplong2 | bLSSIReadEdge);

	udelay(10);

	for (i = 0; i < 2; i++)
		udelay(MAX_STALL_TIME);
	udelay(10);

	if (eRFPath == RF_PATH_A)
		RfPiEnable = (u8)PHY_QueryBBReg(Adapter, rFPGA0_XA_HSSIParameter1|MaskforPhySet, BIT8);
	else if (eRFPath == RF_PATH_B)
		RfPiEnable = (u8)PHY_QueryBBReg(Adapter, rFPGA0_XB_HSSIParameter1|MaskforPhySet, BIT8);

	if (RfPiEnable) {
		/*  Read from BBreg8b8, 12 bits for 8190, 20bits for T65 RF */
		retValue = PHY_QueryBBReg(Adapter, pPhyReg->rfLSSIReadBackPi|MaskforPhySet, bLSSIReadBackData);

		/* RT_DISP(FINIT, INIT_RF, ("Readback from RF-PI : 0x%x\n", retValue)); */
	} else {
		/* Read from BBreg8a0, 12 bits for 8190, 20 bits for T65 RF */
		retValue = PHY_QueryBBReg(Adapter, pPhyReg->rfLSSIReadBack|MaskforPhySet, bLSSIReadBackData);

		/* RT_DISP(FINIT, INIT_RF, ("Readback from RF-SI : 0x%x\n", retValue)); */
	}
	return retValue;

}