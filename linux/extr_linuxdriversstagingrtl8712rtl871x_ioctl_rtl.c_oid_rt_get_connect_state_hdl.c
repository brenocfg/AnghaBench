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
typedef  int /*<<< orphan*/  uint ;
typedef  int /*<<< orphan*/  u32 ;
struct oid_par_priv {scalar_t__ type_of_oid; int /*<<< orphan*/  information_buf_len; int /*<<< orphan*/ * bytes_rw; scalar_t__ information_buf; struct _adapter* adapter_context; } ;
struct mlme_priv {int dummy; } ;
struct _adapter {struct mlme_priv mlmepriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADHOCMODE ; 
 int /*<<< orphan*/  ASSOCIATED ; 
 int /*<<< orphan*/  CHECKINGSTATUS ; 
 int /*<<< orphan*/  NOTASSOCIATED ; 
 scalar_t__ QUERY_OID ; 
 int /*<<< orphan*/  RNDIS_STATUS_NOT_ACCEPTED ; 
 int /*<<< orphan*/  RNDIS_STATUS_SUCCESS ; 
 int /*<<< orphan*/  WIFI_ADHOC_STATE ; 
 int /*<<< orphan*/  _FW_LINKED ; 
 int /*<<< orphan*/  _FW_UNDER_LINKING ; 
 scalar_t__ check_fwstate (struct mlme_priv*,int /*<<< orphan*/ ) ; 

uint oid_rt_get_connect_state_hdl(struct oid_par_priv *poid_par_priv)
{
	struct _adapter *padapter = poid_par_priv->adapter_context;
	struct mlme_priv *pmlmepriv = &(padapter->mlmepriv);
	u32 ulInfo;

	if (poid_par_priv->type_of_oid != QUERY_OID)
		return RNDIS_STATUS_NOT_ACCEPTED;
	/* nStatus==0	CheckingStatus
	 * nStatus==1	Associated
	 * nStatus==2	AdHocMode
	 * nStatus==3	NotAssociated
	 */
	if (check_fwstate(pmlmepriv, _FW_UNDER_LINKING))
		ulInfo = CHECKINGSTATUS;
	else if (check_fwstate(pmlmepriv, _FW_LINKED))
		ulInfo = ASSOCIATED;
	else if (check_fwstate(pmlmepriv, WIFI_ADHOC_STATE))
		ulInfo = ADHOCMODE;
	else
		ulInfo = NOTASSOCIATED;
	*(u32 *)poid_par_priv->information_buf = ulInfo;
	*poid_par_priv->bytes_rw =  poid_par_priv->information_buf_len;
	return RNDIS_STATUS_SUCCESS;
}