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
struct oid_par_priv {scalar_t__ type_of_oid; int information_buf_len; scalar_t__ information_buf; int /*<<< orphan*/  adapter_context; } ;
typedef  int /*<<< orphan*/  _irqL ;
typedef  int /*<<< orphan*/  PADAPTER ;
typedef  int /*<<< orphan*/  NDIS_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  LOWER ; 
 int /*<<< orphan*/  NDIS_STATUS_INVALID_LENGTH ; 
 int /*<<< orphan*/  NDIS_STATUS_NOT_ACCEPTED ; 
 int /*<<< orphan*/  NDIS_STATUS_SUCCESS ; 
 int /*<<< orphan*/  RAISE ; 
 scalar_t__ SET_OID ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  _irqlevel_changed_ (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_setrfreg_cmd (int /*<<< orphan*/ ,unsigned char,unsigned long) ; 

NDIS_STATUS oid_rt_pro_rf_write_registry_hdl(struct oid_par_priv* poid_par_priv)
{
	NDIS_STATUS		status = NDIS_STATUS_SUCCESS;
	PADAPTER		Adapter = (PADAPTER)(poid_par_priv->adapter_context);
	_irqL			oldirql;
	_func_enter_;
	//DEBUG_ERR(("<**********************oid_rt_pro_rf_write_registry_hdl \n"));
	if(poid_par_priv->type_of_oid != SET_OID) //QUERY_OID
	{
		status = NDIS_STATUS_NOT_ACCEPTED;
		return status;
	}
	
	_irqlevel_changed_(&oldirql,LOWER);
	if(poid_par_priv->information_buf_len== (sizeof(unsigned long)*3))
	{      
		//RegOffsetValue	- The offset of RF register to write.
		//RegDataWidth	- The data width of RF register to write.
		//RegDataValue	- The value to write. 
		//RegOffsetValue = *((unsigned long*)InformationBuffer);
		//RegDataWidth = *((unsigned long*)InformationBuffer+1);	   
		//RegDataValue =  *((unsigned long*)InformationBuffer+2);	
		if(!rtw_setrfreg_cmd(Adapter, 
						*(unsigned char*)poid_par_priv->information_buf, 
						(unsigned long)(*((unsigned long*)poid_par_priv->information_buf+2))))
		{
			status = NDIS_STATUS_NOT_ACCEPTED;
		}
	                   
	}
	else{
		status = NDIS_STATUS_INVALID_LENGTH;
	}   
	_irqlevel_changed_(&oldirql,RAISE);
	_func_exit_;

	return status;
}