#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct oid_par_priv {scalar_t__ type_of_oid; int /*<<< orphan*/  information_buf_len; int /*<<< orphan*/ * bytes_rw; scalar_t__ information_buf; int /*<<< orphan*/  adapter_context; } ;
struct mlme_priv {int dummy; } ;
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_2__ {struct mlme_priv mlmepriv; } ;
typedef  TYPE_1__* PADAPTER ;
typedef  int /*<<< orphan*/  NDIS_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ADHOCMODE ; 
 int /*<<< orphan*/  ASSOCIATED ; 
 int /*<<< orphan*/  CHECKINGSTATUS ; 
 int /*<<< orphan*/  NDIS_STATUS_NOT_ACCEPTED ; 
 int /*<<< orphan*/  NDIS_STATUS_SUCCESS ; 
 int /*<<< orphan*/  NOTASSOCIATED ; 
 scalar_t__ QUERY_OID ; 
 int /*<<< orphan*/  WIFI_ADHOC_STATE ; 
 int /*<<< orphan*/  _FW_LINKED ; 
 int /*<<< orphan*/  _FW_UNDER_LINKING ; 
 scalar_t__ _TRUE ; 
 scalar_t__ check_fwstate (struct mlme_priv*,int /*<<< orphan*/ ) ; 

NDIS_STATUS oid_rt_get_connect_state_hdl(struct oid_par_priv* poid_par_priv)
{
	NDIS_STATUS		status = NDIS_STATUS_SUCCESS;
	PADAPTER		padapter = (PADAPTER)(poid_par_priv->adapter_context);

	struct mlme_priv	*pmlmepriv = &(padapter->mlmepriv);

	ULONG ulInfo;
		
	if(poid_par_priv->type_of_oid != QUERY_OID)
	{
		status = NDIS_STATUS_NOT_ACCEPTED;
		return status;
	}		

	// nStatus==0	CheckingStatus
	// nStatus==1	Associated
	// nStatus==2	AdHocMode
	// nStatus==3	NotAssociated
	
	if(check_fwstate(pmlmepriv, _FW_UNDER_LINKING) == _TRUE)
		ulInfo = CHECKINGSTATUS;
	else if(check_fwstate(pmlmepriv, _FW_LINKED) == _TRUE)	
		ulInfo = ASSOCIATED;
	else if(check_fwstate(pmlmepriv, WIFI_ADHOC_STATE)== _TRUE)
		ulInfo = ADHOCMODE;
	else
		ulInfo = NOTASSOCIATED ;

	*(ULONG *)poid_par_priv->information_buf = ulInfo;
	*poid_par_priv->bytes_rw =  poid_par_priv->information_buf_len;

#if 0
	// Rearrange the order to let the UI still shows connection when scan is in progress
	RT_TRACE(COMP_OID_QUERY, DBG_LOUD, ("===> Query OID_RT_GET_CONNECT_STATE.\n"));
	if(pMgntInfo->mAssoc)
		ulInfo = 1;
	else if(pMgntInfo->mIbss)
		ulInfo = 2;
	else if(pMgntInfo->bScanInProgress)
		ulInfo = 0;
	else
		ulInfo = 3;
	ulInfoLen = sizeof(ULONG);
	RT_TRACE(COMP_OID_QUERY, DBG_LOUD, ("<=== Query OID_RT_GET_CONNECT_STATE: %d\n", ulInfo));
#endif

	return status;
}