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
struct mlme_ext_info {int ERP_enable; int /*<<< orphan*/  ERP_IE; } ;
struct mlme_ext_priv {struct mlme_ext_info mlmext_info; } ;
struct TYPE_5__ {struct mlme_ext_priv mlmeextpriv; } ;
typedef  TYPE_1__ _adapter ;
struct TYPE_6__ {int Length; int /*<<< orphan*/  data; } ;
typedef  TYPE_2__* PNDIS_802_11_VARIABLE_IEs ;

/* Variables and functions */
 int /*<<< orphan*/  _rtw_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void ERP_IE_handler(_adapter *padapter, PNDIS_802_11_VARIABLE_IEs pIE)
{
	struct mlme_ext_priv	*pmlmeext = &padapter->mlmeextpriv;
	struct mlme_ext_info	*pmlmeinfo = &(pmlmeext->mlmext_info);

	if(pIE->Length>1)
		return;
	
	pmlmeinfo->ERP_enable = 1;
	_rtw_memcpy(&(pmlmeinfo->ERP_IE), pIE->data, pIE->Length);
}