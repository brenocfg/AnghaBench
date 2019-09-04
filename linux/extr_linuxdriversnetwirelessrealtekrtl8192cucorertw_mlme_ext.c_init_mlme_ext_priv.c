#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct registry_priv {int /*<<< orphan*/  bAcceptAddbaReq; } ;
struct mlme_priv {int /*<<< orphan*/  ChannelPlan; } ;
struct mlme_ext_info {int /*<<< orphan*/  bAcceptAddbaReq; } ;
struct mlme_ext_priv {int /*<<< orphan*/  mlmeext_init; int /*<<< orphan*/  chan_scan_time; int /*<<< orphan*/  channel_list; int /*<<< orphan*/  max_chan_nums; int /*<<< orphan*/  channel_set; TYPE_1__* padapter; struct mlme_ext_info mlmext_info; } ;
struct TYPE_7__ {struct mlme_priv mlmepriv; struct mlme_ext_priv mlmeextpriv; struct registry_priv registrypriv; } ;
typedef  TYPE_1__ _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  SURVEY_TO ; 
 int _SUCCESS ; 
 int /*<<< orphan*/  _TRUE ; 
 int /*<<< orphan*/  init_channel_list (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_channel_set (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_mlme_ext_priv_value (TYPE_1__*) ; 
 int /*<<< orphan*/  init_mlme_ext_timer (TYPE_1__*) ; 

int	init_mlme_ext_priv(_adapter* padapter)
{
	int	res = _SUCCESS;
	struct registry_priv* pregistrypriv = &padapter->registrypriv;
	struct mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	struct mlme_priv *pmlmepriv = &(padapter->mlmepriv);
	struct mlme_ext_info	*pmlmeinfo = &(pmlmeext->mlmext_info);

	// We don't need to memset padapter->XXX to zero, because adapter is allocated by rtw_zvmalloc().
	//_rtw_memset((u8 *)pmlmeext, 0, sizeof(struct mlme_ext_priv));

	pmlmeext->padapter = padapter;

	//fill_fwpriv(padapter, &(pmlmeext->fwpriv));

	init_mlme_ext_priv_value(padapter);
	pmlmeinfo->bAcceptAddbaReq = pregistrypriv->bAcceptAddbaReq;
	
	init_mlme_ext_timer(padapter);

#ifdef CONFIG_AP_MODE
	init_mlme_ap_info(padapter);	
#endif

	pmlmeext->max_chan_nums = init_channel_set(padapter, pmlmepriv->ChannelPlan,pmlmeext->channel_set);
	init_channel_list(padapter, pmlmeext->channel_set, pmlmeext->max_chan_nums, &pmlmeext->channel_list);
	
	pmlmeext->chan_scan_time = SURVEY_TO;
	pmlmeext->mlmeext_init = _TRUE;


#ifdef CONFIG_ACTIVE_KEEP_ALIVE_CHECK	
	pmlmeext->active_keep_alive_check = _TRUE;
#endif

	return res;

}