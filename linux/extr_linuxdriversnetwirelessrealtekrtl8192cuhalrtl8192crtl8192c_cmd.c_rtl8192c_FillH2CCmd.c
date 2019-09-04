#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct TYPE_13__ {scalar_t__ bFWReady; } ;
typedef  TYPE_1__ _adapter ;
struct TYPE_15__ {int /*<<< orphan*/  h2c_fwcmd_mutex; } ;
struct TYPE_14__ {int LastHMEBoxNum; } ;
typedef  TYPE_2__ HAL_DATA_TYPE ;

/* Variables and functions */
 scalar_t__ BIT (int) ; 
 int /*<<< orphan*/  DBG_8192C (char*) ; 
 int EX_MESSAGE_BOX_SIZE ; 
 TYPE_2__* GET_HAL_DATA (TYPE_1__*) ; 
 TYPE_1__* GET_PRIMARY_ADAPTER (TYPE_1__*) ; 
 int MESSAGE_BOX_SIZE ; 
 scalar_t__ REG_HMEBOX_0 ; 
 scalar_t__ REG_HMEBOX_EXT_0 ; 
 scalar_t__ RTL92C_MAX_CMD_LEN ; 
 int RTL92C_MAX_H2C_BOX_NUMS ; 
 int _FAIL ; 
 scalar_t__ _FALSE ; 
 int _SUCCESS ; 
 int _TRUE ; 
 int /*<<< orphan*/  _enter_critical_mutex (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _exit_critical_mutex (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  _is_fw_read_cmd_down (TYPE_1__*,int) ; 
 int /*<<< orphan*/  _rtw_memcpy (int*,int*,scalar_t__) ; 
 TYPE_6__* adapter_to_dvobj (TYPE_1__*) ; 
 scalar_t__ cpu_to_le16 (scalar_t__) ; 
 scalar_t__ cpu_to_le32 (scalar_t__) ; 
 int /*<<< orphan*/  rtw_write16 (TYPE_1__*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  rtw_write32 (TYPE_1__*,scalar_t__,scalar_t__) ; 

int rtl8192c_FillH2CCmd(_adapter* padapter, u8 ElementID, u32 CmdLen, u8* pCmdBuffer)
{
	u8	bcmd_down = _FALSE;
	int 	retry_cnts = 100;
	u8	h2c_box_num;
	u32	msgbox_addr;
	u32  msgbox_ex_addr;
	HAL_DATA_TYPE	*pHalData = GET_HAL_DATA(padapter);
	u32	h2c_cmd = 0;
	u16	h2c_cmd_ex = 0;
	int ret = _FAIL;

_func_enter_;	

	padapter = GET_PRIMARY_ADAPTER(padapter);		
	pHalData = GET_HAL_DATA(padapter);

	if(padapter->bFWReady == _FALSE)
	{
		DBG_8192C("FillH2CCmd(): return H2C cmd because fw is not ready\n");
		return ret;
	}

	_enter_critical_mutex(&(adapter_to_dvobj(padapter)->h2c_fwcmd_mutex), NULL);

	if(!pCmdBuffer){
		goto exit;
	}
	if(CmdLen > RTL92C_MAX_CMD_LEN){
		goto exit;
	}
	//pay attention to if  race condition happened in  H2C cmd setting.
	do{
		h2c_box_num = pHalData->LastHMEBoxNum;

		if(!_is_fw_read_cmd_down(padapter, h2c_box_num)){
			DBG_8192C(" fw read cmd failed...\n");
			goto exit;
		}

		if(CmdLen<=3)
		{
			_rtw_memcpy((u8*)(&h2c_cmd)+1, pCmdBuffer, CmdLen );
		}
		else{
			_rtw_memcpy((u8*)(&h2c_cmd_ex), pCmdBuffer, EX_MESSAGE_BOX_SIZE);
			_rtw_memcpy((u8*)(&h2c_cmd)+1, pCmdBuffer+2,( CmdLen-EX_MESSAGE_BOX_SIZE));
			*(u8*)(&h2c_cmd) |= BIT(7);
		}

		*(u8*)(&h2c_cmd) |= ElementID;

		if(h2c_cmd & BIT(7)){
			msgbox_ex_addr = REG_HMEBOX_EXT_0 + (h2c_box_num *EX_MESSAGE_BOX_SIZE);
			h2c_cmd_ex = cpu_to_le16( h2c_cmd_ex );
			rtw_write16(padapter, msgbox_ex_addr, h2c_cmd_ex);
		}
		msgbox_addr =REG_HMEBOX_0 + (h2c_box_num *MESSAGE_BOX_SIZE);
		h2c_cmd = cpu_to_le32( h2c_cmd );
		rtw_write32(padapter,msgbox_addr, h2c_cmd);

		bcmd_down = _TRUE;

	//	DBG_8192C("MSG_BOX:%d,CmdLen(%d), reg:0x%x =>h2c_cmd:0x%x, reg:0x%x =>h2c_cmd_ex:0x%x ..\n"
	//	 	,pHalData->LastHMEBoxNum ,CmdLen,msgbox_addr,h2c_cmd,msgbox_ex_addr,h2c_cmd_ex);

		 pHalData->LastHMEBoxNum = (h2c_box_num+1) % RTL92C_MAX_H2C_BOX_NUMS ;

	}while((!bcmd_down) && (retry_cnts--));
/*
	if(bcmd_down)
		DBG_8192C("H2C Cmd exe down. \n"	);	
	else
		DBG_8192C("H2C Cmd exe failed. \n"	);
*/
	ret = _SUCCESS;

exit:

	_exit_critical_mutex(&(adapter_to_dvobj(padapter)->h2c_fwcmd_mutex), NULL);	

_func_exit_;

	return ret;

}