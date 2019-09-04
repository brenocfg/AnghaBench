#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mlme_ext_info {int assoc_AP_vendor; int turboMode_cts2self; int turboMode_rtsen; } ;
struct mlme_ext_priv {struct mlme_ext_info mlmext_info; } ;
struct TYPE_4__ {struct mlme_ext_priv mlmeextpriv; } ;
typedef  TYPE_1__ _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  DYNAMIC_FUNC_HP ; 
 int /*<<< orphan*/  Switch_DM_Func (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _FALSE ; 
#define  marvellAP 130 
#define  ralinkAP 129 
#define  realtekAP 128 

void update_IOT_info(_adapter *padapter)
{
	struct mlme_ext_priv	*pmlmeext = &padapter->mlmeextpriv;
	struct mlme_ext_info	*pmlmeinfo = &(pmlmeext->mlmext_info);
	
	switch (pmlmeinfo->assoc_AP_vendor)
	{
		case marvellAP:
			pmlmeinfo->turboMode_cts2self = 1;
			pmlmeinfo->turboMode_rtsen = 0;
			break;
		
		case ralinkAP:
			pmlmeinfo->turboMode_cts2self = 0;
			pmlmeinfo->turboMode_rtsen = 1;
			//disable high power			
			Switch_DM_Func(padapter, (~DYNAMIC_FUNC_HP), _FALSE);
			break;
		case realtekAP:
			//rtw_write16(padapter, 0x4cc, 0xffff);
			//rtw_write16(padapter, 0x546, 0x01c0);
			//disable high power			
			Switch_DM_Func(padapter, (~DYNAMIC_FUNC_HP), _FALSE);
			break;
		default:
			pmlmeinfo->turboMode_cts2self = 0;
			pmlmeinfo->turboMode_rtsen = 1;
			break;	
	}
	
}