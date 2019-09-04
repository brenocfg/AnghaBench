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

NDIS_STATUS oid_rt_pro_set_fw_ra_state_hdl(struct oid_par_priv* poid_par_priv)
{

	NDIS_STATUS		status = NDIS_STATUS_SUCCESS;
#if 0
	PADAPTER		Adapter = (PADAPTER)(poid_par_priv->adapter_context);
	_irqL			oldirql;
	
	_func_enter_;	
	if(poid_par_priv->type_of_oid != SET_OID) 
	{
		status = NDIS_STATUS_NOT_ACCEPTED;
		return status;
	}

					
	_irqlevel_changed_(&oldirql,LOWER);
	
	if(poid_par_priv->information_buf_len >= sizeof(struct setra_parm))
	{
		//DEBUG_ERR(("===> oid_rt_pro_set_fw_ra_state_hdl. type:0x%02x.\n",*((unsigned char*)poid_par_priv->information_buf )));	
		if(!rtw_setfwra_cmd(Adapter,*((unsigned char*)poid_par_priv->information_buf )))			
		{
			status = NDIS_STATUS_NOT_ACCEPTED;
		}
		                   
	}
	else{
		status = NDIS_STATUS_NOT_ACCEPTED;
	}  
	_irqlevel_changed_(&oldirql,RAISE);
	_func_exit_;
#endif
	return status;
}