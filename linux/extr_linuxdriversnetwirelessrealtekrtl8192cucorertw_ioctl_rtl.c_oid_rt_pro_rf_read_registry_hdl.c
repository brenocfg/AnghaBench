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
struct oid_par_priv {int dummy; } ;
typedef  int /*<<< orphan*/  NDIS_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  NDIS_STATUS_SUCCESS ; 

NDIS_STATUS oid_rt_pro_rf_read_registry_hdl(struct oid_par_priv* poid_par_priv)
{
	NDIS_STATUS		status = NDIS_STATUS_SUCCESS;
#if 0
	PADAPTER		Adapter = (PADAPTER)(poid_par_priv->adapter_context);
	_irqL	oldirql;
	_func_enter_;

	//DEBUG_ERR(("<**********************oid_rt_pro_rf_read_registry_hdl \n"));
	if(poid_par_priv->type_of_oid != SET_OID) //QUERY_OID
	{
		status = NDIS_STATUS_NOT_ACCEPTED;
		return status;
	}	
	
	_irqlevel_changed_(&oldirql,LOWER);
	if(poid_par_priv->information_buf_len== (sizeof(unsigned long)*3))
	{
		if(Adapter->mppriv.act_in_progress == _TRUE)
		{
			status = NDIS_STATUS_NOT_ACCEPTED;
		}
		else
		{
			//init workparam
			Adapter->mppriv.act_in_progress = _TRUE;
			Adapter->mppriv.workparam.bcompleted= _FALSE;
			Adapter->mppriv.workparam.act_type = MPT_READ_RF;
			Adapter->mppriv.workparam.io_offset = *(unsigned long*)poid_par_priv->information_buf;		
			Adapter->mppriv.workparam.io_value = 0xcccccccc;
				       
			//RegOffsetValue	- The offset of RF register to read.
			//RegDataWidth	- The data width of RF register to read.
			//RegDataValue	- The value to read. 
			//RegOffsetValue = *((unsigned long*)InformationBuffer);
			//RegDataWidth = *((unsigned long*)InformationBuffer+1);	   
			//RegDataValue =  *((unsigned long*)InformationBuffer+2);	   	 	                   
			if(!rtw_getrfreg_cmd(Adapter, 
							*(unsigned char*)poid_par_priv->information_buf, 
							(unsigned char*)&Adapter->mppriv.workparam.io_value))
			{
				status = NDIS_STATUS_NOT_ACCEPTED;
			}
		}
				      		   
		                   
	}
	else	{
		status = NDIS_STATUS_INVALID_LENGTH;
	}
	_irqlevel_changed_(&oldirql,RAISE);
	_func_exit_;
#endif
	return status;
}