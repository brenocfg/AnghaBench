#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int agg_enable_bitmap; int candidate_tid_bitmap; int /*<<< orphan*/  ch_offset; int /*<<< orphan*/  bwmode; void* sgi; void* ampdu_enable; void* ht_option; } ;
struct sta_info {int /*<<< orphan*/  state; void* qos_option; TYPE_2__ htpriv; } ;
struct TYPE_10__ {scalar_t__ qos_option; } ;
struct TYPE_8__ {void* ampdu_enable; scalar_t__ ht_option; } ;
struct mlme_priv {TYPE_3__ qospriv; TYPE_1__ htpriv; } ;
struct mlme_ext_info {int /*<<< orphan*/  HT_caps; } ;
struct mlme_ext_priv {int /*<<< orphan*/  cur_ch_offset; int /*<<< orphan*/  cur_bwmode; struct mlme_ext_info mlmext_info; } ;
struct TYPE_11__ {struct mlme_ext_priv mlmeextpriv; struct mlme_priv mlmepriv; } ;
typedef  TYPE_4__ _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  VCS_update (TYPE_4__*,struct sta_info*) ; 
 void* _FALSE ; 
 int /*<<< orphan*/  _FW_LINKED ; 
 void* _TRUE ; 
 scalar_t__ support_short_GI (TYPE_4__*,int /*<<< orphan*/ *) ; 

void update_sta_info(_adapter *padapter, struct sta_info *psta)
{
	struct mlme_priv *pmlmepriv = &(padapter->mlmepriv);
	struct mlme_ext_priv	*pmlmeext = &padapter->mlmeextpriv;
	struct mlme_ext_info	*pmlmeinfo = &(pmlmeext->mlmext_info);

	//ERP
	VCS_update(padapter, psta);


	//HT
	if(pmlmepriv->htpriv.ht_option)
	{
		psta->htpriv.ht_option = _TRUE;

		psta->htpriv.ampdu_enable = pmlmepriv->htpriv.ampdu_enable;

		if (support_short_GI(padapter, &(pmlmeinfo->HT_caps)))
			psta->htpriv.sgi = _TRUE;

		psta->qos_option = _TRUE;
		
	}
	else
	{
		psta->htpriv.ht_option = _FALSE;

		psta->htpriv.ampdu_enable = _FALSE;
		
		psta->htpriv.sgi = _FALSE;

		psta->qos_option = _FALSE;

	}
	
	psta->htpriv.bwmode = pmlmeext->cur_bwmode;
	psta->htpriv.ch_offset = pmlmeext->cur_ch_offset;
	
	psta->htpriv.agg_enable_bitmap = 0x0;//reset
	psta->htpriv.candidate_tid_bitmap = 0x0;//reset
	

	//QoS
	if(pmlmepriv->qospriv.qos_option)
		psta->qos_option = _TRUE;
	

	psta->state = _FW_LINKED;

}