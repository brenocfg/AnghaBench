#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ht_priv {scalar_t__ ht_option; } ;
struct mlme_priv {struct ht_priv htpriv; } ;
struct mlme_ext_info {int HT_info_enable; int /*<<< orphan*/  HT_info; } ;
struct mlme_ext_priv {struct mlme_ext_info mlmext_info; } ;
struct HT_info_element {int dummy; } ;
struct TYPE_5__ {struct mlme_priv mlmepriv; struct mlme_ext_priv mlmeextpriv; } ;
typedef  TYPE_1__ _adapter ;
struct TYPE_6__ {int Length; int /*<<< orphan*/  data; } ;
typedef  TYPE_2__* PNDIS_802_11_VARIABLE_IEs ;

/* Variables and functions */
 scalar_t__ _FALSE ; 
 int /*<<< orphan*/  _rtw_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void HT_info_handler(_adapter *padapter, PNDIS_802_11_VARIABLE_IEs pIE)
{
	struct mlme_ext_priv	*pmlmeext = &padapter->mlmeextpriv;
	struct mlme_ext_info	*pmlmeinfo = &(pmlmeext->mlmext_info);
	struct mlme_priv 		*pmlmepriv = &padapter->mlmepriv;	
	struct ht_priv			*phtpriv = &pmlmepriv->htpriv;

	if(pIE==NULL) return;

	if(phtpriv->ht_option == _FALSE)	return;


	if(pIE->Length > sizeof(struct HT_info_element))
		return;
	
	pmlmeinfo->HT_info_enable = 1;
	_rtw_memcpy(&(pmlmeinfo->HT_info), pIE->data, pIE->Length);
	
	return;
}