#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct mlme_ext_info {scalar_t__ assoc_AP_vendor; int /*<<< orphan*/  HT_enable; } ;
struct mlme_ext_priv {int cur_bwmode; struct mlme_ext_info mlmext_info; } ;
struct TYPE_5__ {int HT_caps_info; } ;
struct TYPE_6__ {TYPE_1__ HT_cap_element; } ;
struct HT_caps_element {TYPE_2__ u; } ;
struct TYPE_7__ {struct mlme_ext_priv mlmeextpriv; } ;
typedef  TYPE_3__ _adapter ;

/* Variables and functions */
 int HT_CHANNEL_WIDTH_40 ; 
 int _FAIL ; 
 int _SUCCESS ; 
 scalar_t__ ralinkAP ; 

int support_short_GI(_adapter *padapter, struct HT_caps_element *pHT_caps)
{
	unsigned char					bit_offset;
	struct mlme_ext_priv	*pmlmeext = &padapter->mlmeextpriv;
	struct mlme_ext_info	*pmlmeinfo = &(pmlmeext->mlmext_info);
	
	if (!(pmlmeinfo->HT_enable))
		return _FAIL;
	
	if ((pmlmeinfo->assoc_AP_vendor == ralinkAP))
		return _FAIL;
		
	bit_offset = (pmlmeext->cur_bwmode & HT_CHANNEL_WIDTH_40)? 6: 5;
	
	if (pHT_caps->u.HT_cap_element.HT_caps_info & (0x1 << bit_offset))
	{
		return _SUCCESS;
	}
	else
	{
		return _FAIL;
	}		
}