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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  PADAPTER ;
typedef  int /*<<< orphan*/  HAL_DATA_TYPE ;

/* Variables and functions */
 int /*<<< orphan*/ * GET_HAL_DATA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSG_8192C (char*,...) ; 
 int /*<<< orphan*/  _InitOtherVariable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _ReadPROMContent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _ReadRFType (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _ReadSilmComboMode (int /*<<< orphan*/ ) ; 
 int _SUCCESS ; 
 int /*<<< orphan*/  rtw_get_current_time () ; 
 int /*<<< orphan*/  rtw_get_passing_time_ms (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int _ReadAdapterInfo8192CU(PADAPTER	Adapter)
{
	HAL_DATA_TYPE	*pHalData = GET_HAL_DATA(Adapter);
	u32 start=rtw_get_current_time();
	
	MSG_8192C("====> ReadAdapterInfo8192C\n");

	//Efuse_InitSomeVar(Adapter);

	//if(IS_HARDWARE_TYPE_8723A(Adapter))
	//	_EfuseCellSel(Adapter);

	_ReadRFType(Adapter);//rf_chip -> _InitRFType()
	_ReadPROMContent(Adapter);

	// 2010/10/25 MH THe function must be called after borad_type & IC-Version recognize.
	_ReadSilmComboMode(Adapter);

	_InitOtherVariable(Adapter);

	//MSG_8192C("%s()(done), rf_chip=0x%x, rf_type=0x%x\n",  __FUNCTION__, pHalData->rf_chip, pHalData->rf_type);

	MSG_8192C("<==== ReadAdapterInfo8192C in %d ms\n", rtw_get_passing_time_ms(start));

	return _SUCCESS;
}