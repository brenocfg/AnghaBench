#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct mlme_ext_info {int /*<<< orphan*/  bcn_interval; } ;
struct mlme_ext_priv {struct mlme_ext_info mlmext_info; } ;
struct TYPE_12__ {struct mlme_ext_priv mlmeextpriv; } ;
typedef  TYPE_1__* PADAPTER ;
typedef  int /*<<< orphan*/  HAL_DATA_TYPE ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/ * GET_HAL_DATA (TYPE_1__*) ; 
 int /*<<< orphan*/  REG_ATIMWND ; 
 int /*<<< orphan*/  REG_BCN_CTRL ; 
 int /*<<< orphan*/  REG_BCN_INTERVAL ; 
 int /*<<< orphan*/  REG_RXTSF_OFFSET_CCK ; 
 int /*<<< orphan*/  REG_RXTSF_OFFSET_OFDM ; 
 int /*<<< orphan*/  REG_SLOT ; 
 int /*<<< orphan*/  REG_TCR ; 
 int /*<<< orphan*/  ResumeTxBeacon (TYPE_1__*) ; 
 int /*<<< orphan*/  TSFRST ; 
 int /*<<< orphan*/  _BeaconFunctionEnable (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _InitBeaconParameters (TYPE_1__*) ; 
 int /*<<< orphan*/  _TRUE ; 
 int /*<<< orphan*/  rtw_read32 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int rtw_read8 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_write16 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_write32 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_write8 (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void SetBeaconRelatedRegisters8192CUsb(PADAPTER padapter)
{
	u32	value32;
	HAL_DATA_TYPE	*pHalData = GET_HAL_DATA(padapter);
	struct mlme_ext_priv	*pmlmeext = &(padapter->mlmeextpriv);
	struct mlme_ext_info	*pmlmeinfo = &(pmlmeext->mlmext_info);

	//reset TSF, enable update TSF, correcting TSF On Beacon 
	
	//REG_BCN_INTERVAL
	//REG_BCNDMATIM
	//REG_ATIMWND
	//REG_TBTT_PROHIBIT
	//REG_DRVERLYINT
	//REG_BCN_MAX_ERR	
	//REG_BCNTCFG //(0x510)
	//REG_DUAL_TSF_RST
	//REG_BCN_CTRL //(0x550) 

	//BCN interval
	rtw_write16(padapter, REG_BCN_INTERVAL, pmlmeinfo->bcn_interval);
	rtw_write8(padapter, REG_ATIMWND, 0x02);// 2ms

	_InitBeaconParameters(padapter);

	rtw_write8(padapter, REG_SLOT, 0x09);

	value32 =rtw_read32(padapter, REG_TCR); 
	value32 &= ~TSFRST;
	rtw_write32(padapter,  REG_TCR, value32); 

	value32 |= TSFRST;
	rtw_write32(padapter, REG_TCR, value32); 

	// NOTE: Fix test chip's bug (about contention windows's randomness)
	rtw_write8(padapter,  REG_RXTSF_OFFSET_CCK, 0x50);
	rtw_write8(padapter, REG_RXTSF_OFFSET_OFDM, 0x50);

	_BeaconFunctionEnable(padapter, _TRUE, _TRUE);

	ResumeTxBeacon(padapter);

	//rtw_write8(padapter, 0x422, rtw_read8(padapter, 0x422)|BIT(6));
	
	//rtw_write8(padapter, 0x541, 0xff);

	//rtw_write8(padapter, 0x542, rtw_read8(padapter, 0x541)|BIT(0));

	rtw_write8(padapter, REG_BCN_CTRL, rtw_read8(padapter, REG_BCN_CTRL)|BIT(1));

}