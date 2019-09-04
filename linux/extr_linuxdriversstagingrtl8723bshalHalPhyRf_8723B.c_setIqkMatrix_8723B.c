#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ s32 ;
struct TYPE_4__ {scalar_t__* pBandType; int /*<<< orphan*/  Adapter; } ;
typedef  TYPE_1__* PDM_ODM_T ;

/* Variables and functions */
 int /*<<< orphan*/  BIT24 ; 
 int /*<<< orphan*/  BIT28 ; 
 scalar_t__ ODM_BAND_2_4G ; 
 int /*<<< orphan*/  ODM_COMP_TX_PWR_TRACK ; 
 int /*<<< orphan*/  ODM_DBG_LOUD ; 
#define  ODM_RF_PATH_A 129 
#define  ODM_RF_PATH_B 128 
 int /*<<< orphan*/  ODM_RT_TRACE (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int* OFDMSwingTable_New ; 
 size_t OFDM_TABLE_SIZE ; 
 int /*<<< orphan*/  PHY_SetBBReg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bMaskDWord ; 
 int /*<<< orphan*/  bMaskH4Bits ; 
 int /*<<< orphan*/  rOFDM0_ECCAThreshold ; 
 int /*<<< orphan*/  rOFDM0_XATxIQImbalance ; 
 int /*<<< orphan*/  rOFDM0_XBTxIQImbalance ; 
 int /*<<< orphan*/  rOFDM0_XCTxAFE ; 
 int /*<<< orphan*/  rOFDM0_XDTxAFE ; 

__attribute__((used)) static void setIqkMatrix_8723B(
	PDM_ODM_T pDM_Odm,
	u8 OFDM_index,
	u8 RFPath,
	s32 IqkResult_X,
	s32 IqkResult_Y
)
{
	s32 ele_A = 0, ele_D, ele_C = 0, value32;

	if (OFDM_index >= OFDM_TABLE_SIZE)
		OFDM_index = OFDM_TABLE_SIZE-1;

	ele_D = (OFDMSwingTable_New[OFDM_index] & 0xFFC00000)>>22;

	/* new element A = element D x X */
	if ((IqkResult_X != 0) && (*(pDM_Odm->pBandType) == ODM_BAND_2_4G)) {
		if ((IqkResult_X & 0x00000200) != 0)	/* consider minus */
			IqkResult_X = IqkResult_X | 0xFFFFFC00;
		ele_A = ((IqkResult_X * ele_D)>>8)&0x000003FF;

		/* new element C = element D x Y */
		if ((IqkResult_Y & 0x00000200) != 0)
			IqkResult_Y = IqkResult_Y | 0xFFFFFC00;
		ele_C = ((IqkResult_Y * ele_D)>>8)&0x000003FF;

		/* if (RFPath == ODM_RF_PATH_A) */
		switch (RFPath) {
		case ODM_RF_PATH_A:
			/* wirte new elements A, C, D to regC80 and regC94, element B is always 0 */
			value32 = (ele_D<<22)|((ele_C&0x3F)<<16)|ele_A;
			PHY_SetBBReg(pDM_Odm->Adapter, rOFDM0_XATxIQImbalance, bMaskDWord, value32);

			value32 = (ele_C&0x000003C0)>>6;
			PHY_SetBBReg(pDM_Odm->Adapter, rOFDM0_XCTxAFE, bMaskH4Bits, value32);

			value32 = ((IqkResult_X * ele_D)>>7)&0x01;
			PHY_SetBBReg(pDM_Odm->Adapter, rOFDM0_ECCAThreshold, BIT24, value32);
			break;
		case ODM_RF_PATH_B:
			/* wirte new elements A, C, D to regC88 and regC9C, element B is always 0 */
			value32 = (ele_D<<22)|((ele_C&0x3F)<<16)|ele_A;
			PHY_SetBBReg(pDM_Odm->Adapter, rOFDM0_XBTxIQImbalance, bMaskDWord, value32);

			value32 = (ele_C&0x000003C0)>>6;
			PHY_SetBBReg(pDM_Odm->Adapter, rOFDM0_XDTxAFE, bMaskH4Bits, value32);

			value32 = ((IqkResult_X * ele_D)>>7)&0x01;
			PHY_SetBBReg(pDM_Odm->Adapter, rOFDM0_ECCAThreshold, BIT28, value32);

			break;
		default:
			break;
		}
	} else {
		switch (RFPath) {
		case ODM_RF_PATH_A:
			PHY_SetBBReg(pDM_Odm->Adapter, rOFDM0_XATxIQImbalance, bMaskDWord, OFDMSwingTable_New[OFDM_index]);
			PHY_SetBBReg(pDM_Odm->Adapter, rOFDM0_XCTxAFE, bMaskH4Bits, 0x00);
			PHY_SetBBReg(pDM_Odm->Adapter, rOFDM0_ECCAThreshold, BIT24, 0x00);
			break;

		case ODM_RF_PATH_B:
			PHY_SetBBReg(pDM_Odm->Adapter, rOFDM0_XBTxIQImbalance, bMaskDWord, OFDMSwingTable_New[OFDM_index]);
			PHY_SetBBReg(pDM_Odm->Adapter, rOFDM0_XDTxAFE, bMaskH4Bits, 0x00);
			PHY_SetBBReg(pDM_Odm->Adapter, rOFDM0_ECCAThreshold, BIT28, 0x00);
			break;

		default:
			break;
		}
	}

	ODM_RT_TRACE(pDM_Odm, ODM_COMP_TX_PWR_TRACK, ODM_DBG_LOUD, ("TxPwrTracking path B: X = 0x%x, Y = 0x%x ele_A = 0x%x ele_C = 0x%x ele_D = 0x%x 0xeb4 = 0x%x 0xebc = 0x%x\n",
	(u32)IqkResult_X, (u32)IqkResult_Y, (u32)ele_A, (u32)ele_C, (u32)ele_D, (u32)IqkResult_X, (u32)IqkResult_Y));
}