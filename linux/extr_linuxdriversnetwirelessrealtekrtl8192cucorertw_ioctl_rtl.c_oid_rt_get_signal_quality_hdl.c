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
struct oid_par_priv {scalar_t__ type_of_oid; int /*<<< orphan*/  adapter_context; } ;
typedef  int /*<<< orphan*/  PADAPTER ;
typedef  int /*<<< orphan*/  NDIS_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  NDIS_STATUS_NOT_ACCEPTED ; 
 int /*<<< orphan*/  NDIS_STATUS_SUCCESS ; 
 scalar_t__ QUERY_OID ; 

NDIS_STATUS oid_rt_get_signal_quality_hdl(struct oid_par_priv* poid_par_priv)
{
	NDIS_STATUS	 	status = NDIS_STATUS_SUCCESS;
	PADAPTER		padapter = (PADAPTER)(poid_par_priv->adapter_context);

	//DEBUG_ERR(("<**********************oid_rt_get_signal_quality_hdl \n"));
	if(poid_par_priv->type_of_oid != QUERY_OID)
	{
		status = NDIS_STATUS_NOT_ACCEPTED;
		return status;
	}		

#if 0
		if(pMgntInfo->mAssoc || pMgntInfo->mIbss)
		{
			ulInfo = pAdapter->RxStats.SignalQuality;
			*poid_par_priv->bytes_rw = poid_par_priv->information_buf_len;
		}
		else
		{
			ulInfo = 0xffffffff; // It stands for -1 in 4-byte integer.
		}
		break;
#endif

	return status;
}