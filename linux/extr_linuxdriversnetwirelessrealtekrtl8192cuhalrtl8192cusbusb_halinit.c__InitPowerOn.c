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
typedef  int u8 ;
typedef  scalar_t__ u32 ;
typedef  int u16 ;
typedef  int /*<<< orphan*/  _adapter ;
struct TYPE_3__ {scalar_t__ BoardType; scalar_t__ SlimComboDbg; } ;
typedef  TYPE_1__ HAL_DATA_TYPE ;

/* Variables and functions */
 int APFM_ONMAC ; 
 int BIT1 ; 
 int BIT14 ; 
 int BIT4 ; 
 int BIT6 ; 
 int BIT7 ; 
 scalar_t__ BOARD_USB_COMBO ; 
 scalar_t__ BOARD_USB_High_PA ; 
 int /*<<< orphan*/  DBG_8192C (char*) ; 
 int ENSEC ; 
 TYPE_1__* GET_HAL_DATA (int /*<<< orphan*/ *) ; 
 int HCI_RXDMA_EN ; 
 int HCI_TXDMA_EN ; 
 int ISO_DIOR ; 
 int ISO_MD2PP ; 
 scalar_t__ IS_HARDWARE_TYPE_8192C (int /*<<< orphan*/ *) ; 
 int LDV12_EN ; 
 int MACRXEN ; 
 int MACTXEN ; 
 int PFM_ALDN ; 
 scalar_t__ POLLING_READY_TIMEOUT_COUNT ; 
 int PROTOCOL_EN ; 
 int REG_APS_FSMCO ; 
 int REG_CR ; 
 int REG_GPIO_MUXCFG ; 
 int REG_LDOV12D_CTRL ; 
 int REG_RSV_CTRL ; 
 int REG_SPS0_CTRL ; 
 int REG_SYS_ISO_CTRL ; 
 int RXDMA_EN ; 
 int SCHEDULE_EN ; 
 int TXDMA_EN ; 
 int _FAIL ; 
 int _SUCCESS ; 
 scalar_t__ _TRUE ; 
 int /*<<< orphan*/  rFPGA0_XCD_RFParameter ; 
 int rtw_read16 (int /*<<< orphan*/ *,int) ; 
 int rtw_read32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int rtw_read8 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rtw_udelay_os (int) ; 
 int /*<<< orphan*/  rtw_write16 (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  rtw_write32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtw_write8 (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static u8 _InitPowerOn(_adapter *padapter)
{
	HAL_DATA_TYPE	*pHalData = GET_HAL_DATA(padapter);
	u8	ret = _SUCCESS;
	u16	value16=0;
	u8	value8 = 0;
	u32  value32 = 0;

	// polling autoload done.
	u32	pollingCount = 0;

	do
	{
		if(rtw_read8(padapter, REG_APS_FSMCO) & PFM_ALDN){
			//RT_TRACE(COMP_INIT,DBG_LOUD,("Autoload Done!\n"));
			break;
		}

		if(pollingCount++ > POLLING_READY_TIMEOUT_COUNT){
			//RT_TRACE(COMP_INIT,DBG_SERIOUS,("Failed to polling REG_APS_FSMCO[PFM_ALDN] done!\n"));
			return _FAIL;
		}
				
	}while(_TRUE);


//	For hardware power on sequence.

	//0.	RSV_CTRL 0x1C[7:0] = 0x00			// unlock ISO/CLK/Power control register
	rtw_write8(padapter, REG_RSV_CTRL, 0x0);	
	// Power on when re-enter from IPS/Radio off/card disable
	rtw_write8(padapter, REG_SPS0_CTRL, 0x2b);//enable SPS into PWM mode
/*
	value16 = PlatformIORead2Byte(Adapter, REG_AFE_XTAL_CTRL);//enable AFE clock
	value16 &=  (~XTAL_GATE_AFE);
	PlatformIOWrite2Byte(Adapter,REG_AFE_XTAL_CTRL, value16 );		
*/
	
	rtw_udelay_os(100);//PlatformSleepUs(150);//this is not necessary when initially power on

	value8 = rtw_read8(padapter, REG_LDOV12D_CTRL);	
	if(0== (value8 & LDV12_EN) ){
		value8 |= LDV12_EN;
		rtw_write8(padapter, REG_LDOV12D_CTRL, value8);	
		//RT_TRACE(COMP_INIT, DBG_LOUD, (" power-on :REG_LDOV12D_CTRL Reg0x21:0x%02x.\n",value8));
		rtw_udelay_os(100);//PlatformSleepUs(100);//this is not necessary when initially power on
		value8 = rtw_read8(padapter, REG_SYS_ISO_CTRL);
		value8 &= ~ISO_MD2PP;
		rtw_write8(padapter, REG_SYS_ISO_CTRL, value8);			
	}	
	
	// auto enable WLAN
	pollingCount = 0;
	value16 = rtw_read16(padapter, REG_APS_FSMCO);
	value16 |= APFM_ONMAC;
	rtw_write16(padapter, REG_APS_FSMCO, value16);

	do
	{
		if(0 == (rtw_read16(padapter, REG_APS_FSMCO) & APFM_ONMAC)){
			//RT_TRACE(COMP_INIT,DBG_LOUD,("MAC auto ON okay!\n"));
			break;
		}

		if(pollingCount++ > POLLING_READY_TIMEOUT_COUNT){
			//RT_TRACE(COMP_INIT,DBG_SERIOUS,("Failed to polling REG_APS_FSMCO[APFM_ONMAC] done!\n"));
			return _FAIL;
		}
				
	}while(_TRUE);

	//Enable Radio ,GPIO ,and LED function
	rtw_write16(padapter,REG_APS_FSMCO,0x0812);

#ifdef CONFIG_AUTOSUSPEND
	//for usb Combo card ,BT
	if((BOARD_USB_COMBO == pHalData->BoardType)&&(padapter->registrypriv.usbss_enable))
	{
		value32 =  rtw_read32(padapter, REG_APS_FSMCO);
		value32 |= (SOP_ABG|SOP_AMB|XOP_BTCK);
		rtw_write32(padapter, REG_APS_FSMCO, value32);		
	}
#endif	

	// release RF digital isolation
	value16 = rtw_read16(padapter, REG_SYS_ISO_CTRL);
	value16 &= ~ISO_DIOR;
	rtw_write16(padapter, REG_SYS_ISO_CTRL, value16);

	// Enable MAC DMA/WMAC/SCHEDULE/SEC block
	value16 = rtw_read16(padapter, REG_CR);
	value16 |= (HCI_TXDMA_EN | HCI_RXDMA_EN | TXDMA_EN | RXDMA_EN
				| PROTOCOL_EN | SCHEDULE_EN | MACTXEN | MACRXEN | ENSEC);
	rtw_write16(padapter, REG_CR, value16);
	
	//tynli_test for suspend mode.
	{
		rtw_write8(padapter,  0xfe10, 0x19);
	}

	// 2010/11/22 MH For slim combo debug mode check.
	if (pHalData->BoardType == BOARD_USB_COMBO)
	{
		if (pHalData->SlimComboDbg == _TRUE)
		{
			DBG_8192C("SlimComboDbg == TRUE\n");

			// 1. SIC?Test Mode 中, Debug Ports 會自動 Enable, 所以 Driver 上來後, 
			//	要關掉請設定 0x 00[7] -> "1", 將它 Disable.   effect if not: power consumption increase
			rtw_write8(padapter, REG_SYS_ISO_CTRL, rtw_read8(padapter, REG_SYS_ISO_CTRL)|BIT7);

			// 2. SIC?Test Mode 中, GPIO-8?會 report Power State 所以 Driver 上來後, 請設定? 0x04[6] -> "1" 將它 Disable
			// effect if not: GPIO-8 could not be GPIO or LED function
			rtw_write8(padapter, REG_APS_FSMCO, rtw_read8(padapter, REG_APS_FSMCO)|BIT6);

			// 3. SIC Test Mode 中, EESK, EECS 會 report?Host Clock status, 所以 Driver 上來後, 請設定? 0x40[4] -> "1" 將它切成 EEPROM 使用 Pin (autoload still from Efuse)
			//  effect if not:power consumption increase
			value8 = rtw_read8(padapter, REG_GPIO_MUXCFG)|BIT4 ;
		#ifdef CONFIG_BT_COEXIST	
			// 2011/01/26 MH UMB-B cut bug. We need to support the modification.
			if (IS_81xxC_VENDOR_UMC_B_CUT(pHalData->VersionID) &&
				pHalData->bt_coexist.BT_Coexist)
			{
				value8 |= (BIT5);	
			}
		#endif
			rtw_write8(padapter, REG_GPIO_MUXCFG,value8 );
			
			
			// 4. SIC Test Mode 中,?SIC Debug ports 會自動 Enable , 所以 Driver 上來後馬上, 請設定? 0x40[15:11] -> “0x00”, 將它Disable
			//  4.1Two Steps setting for safety: 0x40[15,13,12, 11] -> "0", then ?0x40[14] -> "0"
			// effect if not: Host could not transfer packets, and GPIO-3,2 will occupied by SIC then Co-exist could not work.
			rtw_write16(padapter, REG_GPIO_MUXCFG, (rtw_read16(padapter, REG_GPIO_MUXCFG)&0x07FF)|BIT14);
			rtw_write16(padapter, REG_GPIO_MUXCFG, rtw_read16(padapter, REG_GPIO_MUXCFG)&0x07FF);
		}
	}


	// 2011/02/18 To Fix RU LNA  power leakage problem. We need to execute below below in
	// Adapter init and halt sequence. Accordingto EEchou's opinion, we can enable the ability for all
	// IC. According to Johnny's opinion, only RU will meet the condition.
	if (IS_HARDWARE_TYPE_8192C(padapter) && (pHalData->BoardType == BOARD_USB_High_PA))
		rtw_write32(padapter, rFPGA0_XCD_RFParameter, rtw_read32(padapter, rFPGA0_XCD_RFParameter)&(~BIT1));
	return ret;

}