#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct wlan_network {int /*<<< orphan*/  list; } ;
struct TYPE_11__ {int /*<<< orphan*/  queue; } ;
struct TYPE_8__ {int /*<<< orphan*/  InfrastructureMode; } ;
struct TYPE_9__ {TYPE_1__ network; } ;
struct mlme_priv {TYPE_6__ free_bss_pool; int /*<<< orphan*/ * free_bss_buf; int /*<<< orphan*/  assoc_ssid; TYPE_6__ scanned_queue; int /*<<< orphan*/  lock; int /*<<< orphan*/  scan_mode; TYPE_2__ cur_network; scalar_t__ fw_state; int /*<<< orphan*/ * pscanned; int /*<<< orphan*/ * nic_hdl; } ;
typedef  int sint ;
struct TYPE_10__ {struct mlme_priv mlmepriv; } ;
typedef  TYPE_3__ _adapter ;
typedef  int /*<<< orphan*/  NDIS_802_11_SSID ;

/* Variables and functions */
 int MAX_BSS_CNT ; 
 int /*<<< orphan*/  Ndis802_11AutoUnknown ; 
 int /*<<< orphan*/  SCAN_ACTIVE ; 
 int _FAIL ; 
 int _SUCCESS ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  _rtw_init_listhead (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _rtw_init_queue (TYPE_6__*) ; 
 int /*<<< orphan*/  _rtw_memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  _rtw_spinlock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtw_clear_scan_deny (TYPE_3__*) ; 
 int /*<<< orphan*/  rtw_init_mlme_timer (TYPE_3__*) ; 
 int /*<<< orphan*/  rtw_list_insert_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * rtw_zvmalloc (int) ; 
 int /*<<< orphan*/  set_scanned_network_val (struct mlme_priv*,int /*<<< orphan*/ ) ; 

sint	_rtw_init_mlme_priv (_adapter* padapter)
{
	sint	i;
	u8	*pbuf;
	struct wlan_network	*pnetwork;
	struct mlme_priv		*pmlmepriv = &padapter->mlmepriv;
	sint	res = _SUCCESS;

_func_enter_;

	// We don't need to memset padapter->XXX to zero, because adapter is allocated by rtw_zvmalloc().
	//_rtw_memset((u8 *)pmlmepriv, 0, sizeof(struct mlme_priv));

	pmlmepriv->nic_hdl = (u8 *)padapter;

	pmlmepriv->pscanned = NULL;
	pmlmepriv->fw_state = 0;
	pmlmepriv->cur_network.network.InfrastructureMode = Ndis802_11AutoUnknown;
	pmlmepriv->scan_mode=SCAN_ACTIVE;// 1: active, 0: pasive. Maybe someday we should rename this varable to "active_mode" (Jeff)

	_rtw_spinlock_init(&(pmlmepriv->lock));	
	_rtw_init_queue(&(pmlmepriv->free_bss_pool));
	_rtw_init_queue(&(pmlmepriv->scanned_queue));

	set_scanned_network_val(pmlmepriv, 0);
	
	_rtw_memset(&pmlmepriv->assoc_ssid,0,sizeof(NDIS_802_11_SSID));

	pbuf = rtw_zvmalloc(MAX_BSS_CNT * (sizeof(struct wlan_network)));
	
	if (pbuf == NULL){
		res=_FAIL;
		goto exit;
	}
	pmlmepriv->free_bss_buf = pbuf;
		
	pnetwork = (struct wlan_network *)pbuf;
	
	for(i = 0; i < MAX_BSS_CNT; i++)
	{		
		_rtw_init_listhead(&(pnetwork->list));

		rtw_list_insert_tail(&(pnetwork->list), &(pmlmepriv->free_bss_pool.queue));

		pnetwork++;
	}

	//allocate DMA-able/Non-Page memory for cmd_buf and rsp_buf

	rtw_clear_scan_deny(padapter);

	rtw_init_mlme_timer(padapter);

exit:

_func_exit_;

	return res;
}