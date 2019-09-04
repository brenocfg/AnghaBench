#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct oid_par_priv {scalar_t__ type_of_oid; int /*<<< orphan*/  information_buf_len; int /*<<< orphan*/ * bytes_rw; scalar_t__ information_buf; int /*<<< orphan*/  adapter_context; } ;
struct TYPE_12__ {int /*<<< orphan*/  DSConfig; } ;
struct TYPE_7__ {TYPE_6__ Configuration; } ;
struct TYPE_8__ {TYPE_1__ network; } ;
struct mlme_priv {TYPE_2__ cur_network; } ;
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_9__ {TYPE_6__ Configuration; } ;
struct TYPE_10__ {TYPE_3__ dev_network; } ;
struct TYPE_11__ {TYPE_4__ registrypriv; struct mlme_priv mlmepriv; } ;
typedef  TYPE_5__* PADAPTER ;
typedef  int /*<<< orphan*/  NDIS_STATUS ;
typedef  TYPE_6__ NDIS_802_11_CONFIGURATION ;

/* Variables and functions */
 int /*<<< orphan*/  NDIS_STATUS_NOT_ACCEPTED ; 
 int /*<<< orphan*/  NDIS_STATUS_SUCCESS ; 
 scalar_t__ QUERY_OID ; 
 int /*<<< orphan*/  WIFI_ADHOC_MASTER_STATE ; 
 int /*<<< orphan*/  _FW_LINKED ; 
 scalar_t__ _TRUE ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 scalar_t__ check_fwstate (struct mlme_priv*,int /*<<< orphan*/ ) ; 

NDIS_STATUS oid_rt_get_channel_hdl(struct oid_par_priv* poid_par_priv)
{
	NDIS_STATUS	 	status = NDIS_STATUS_SUCCESS;
	PADAPTER		padapter = (PADAPTER)(poid_par_priv->adapter_context);
	struct	mlme_priv	*pmlmepriv = &padapter->mlmepriv;
	NDIS_802_11_CONFIGURATION		*pnic_Config;

	ULONG   channelnum;

	_func_enter_;
	if(poid_par_priv->type_of_oid != QUERY_OID)
	{
		status = NDIS_STATUS_NOT_ACCEPTED;
		return status;
	}		

	if ( (check_fwstate(pmlmepriv, _FW_LINKED) == _TRUE) ||
		(check_fwstate(pmlmepriv, WIFI_ADHOC_MASTER_STATE) == _TRUE))
		pnic_Config = &pmlmepriv->cur_network.network.Configuration;
	else
		pnic_Config = &padapter->registrypriv.dev_network.Configuration;

	channelnum = pnic_Config->DSConfig;
	*(ULONG *)poid_par_priv->information_buf = channelnum;
	
	*poid_par_priv->bytes_rw = poid_par_priv->information_buf_len;

	_func_exit_;



	return status;
}