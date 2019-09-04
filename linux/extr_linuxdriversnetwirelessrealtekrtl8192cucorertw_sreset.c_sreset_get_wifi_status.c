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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  WIFI_STATUS_SUCCESS ; 

u8 sreset_get_wifi_status(_adapter *padapter)
{
#if defined(DBG_CONFIG_ERROR_DETECT)
	HAL_DATA_TYPE	*pHalData = GET_HAL_DATA(padapter);
	struct sreset_priv *psrtpriv = &pHalData->srestpriv;

	u8 status = WIFI_STATUS_SUCCESS;
	u32 val32 = 0;
	_irqL irqL;
	if(psrtpriv->silent_reset_inprogress == _TRUE)
        {
		return status;
	}
	val32 =rtw_read32(padapter,REG_TXDMA_STATUS);
	if(val32==0xeaeaeaea){
		psrtpriv->Wifi_Error_Status = WIFI_IF_NOT_EXIST;
	}
	else if(val32!=0){
		DBG_8192C("txdmastatu(%x)\n",val32);
		psrtpriv->Wifi_Error_Status = WIFI_MAC_TXDMA_ERROR;
	}

	if(WIFI_STATUS_SUCCESS !=psrtpriv->Wifi_Error_Status)
	{
		DBG_8192C("==>%s error_status(0x%x) \n",__FUNCTION__,psrtpriv->Wifi_Error_Status);
		status = (psrtpriv->Wifi_Error_Status &( ~(USB_READ_PORT_FAIL|USB_WRITE_PORT_FAIL)));
	}
	DBG_8192C("==> %s wifi_status(0x%x)\n",__FUNCTION__,status);

	//status restore
	psrtpriv->Wifi_Error_Status = WIFI_STATUS_SUCCESS;

	return status;
#else
	return WIFI_STATUS_SUCCESS;
#endif
}