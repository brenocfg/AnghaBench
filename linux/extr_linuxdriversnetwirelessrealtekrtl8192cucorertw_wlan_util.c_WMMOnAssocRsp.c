#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_9__ {TYPE_1__* ac_param; } ;
struct mlme_ext_info {scalar_t__ WMM_enable; int slotTime; TYPE_2__ WMM_param; } ;
struct mlme_ext_priv {scalar_t__ cur_wireless_mode; struct mlme_ext_info mlmext_info; } ;
struct TYPE_11__ {int acm_mask; } ;
struct TYPE_10__ {int acm_method; } ;
struct TYPE_12__ {TYPE_4__ mlmepriv; TYPE_3__ registrypriv; struct mlme_ext_priv mlmeextpriv; } ;
typedef  TYPE_5__ _adapter ;
struct TYPE_8__ {int ACI_AIFSN; int CW; int /*<<< orphan*/  TXOP_limit; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  DBG_871X (char*,int,int,int) ; 
 int /*<<< orphan*/  HW_VAR_ACM_CTRL ; 
 int /*<<< orphan*/  HW_VAR_AC_PARAM_BE ; 
 int /*<<< orphan*/  HW_VAR_AC_PARAM_BK ; 
 int /*<<< orphan*/  HW_VAR_AC_PARAM_VI ; 
 int /*<<< orphan*/  HW_VAR_AC_PARAM_VO ; 
 scalar_t__ WIRELESS_11B ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_hal_set_hwreg (TYPE_5__*,int /*<<< orphan*/ ,int*) ; 

void WMMOnAssocRsp(_adapter *padapter)
{
	u8	ACI, ACM, AIFS, ECWMin, ECWMax, aSifsTime;
	u8	acm_mask;
	u16	TXOP;
	u32	acParm, i;
	struct mlme_ext_priv	*pmlmeext = &padapter->mlmeextpriv;
	struct mlme_ext_info	*pmlmeinfo = &(pmlmeext->mlmext_info);

	if (pmlmeinfo->WMM_enable == 0)
	{
		padapter->mlmepriv.acm_mask = 0;
		return;
	}

	acm_mask = 0;

	if( pmlmeext->cur_wireless_mode == WIRELESS_11B)
		aSifsTime = 10;
	else
		aSifsTime = 16;

	for (i = 0; i < 4; i++)  
	{
		ACI = (pmlmeinfo->WMM_param.ac_param[i].ACI_AIFSN >> 5) & 0x03;
		ACM = (pmlmeinfo->WMM_param.ac_param[i].ACI_AIFSN >> 4) & 0x01;

		//AIFS = AIFSN * slot time + SIFS - r2t phy delay
		AIFS = (pmlmeinfo->WMM_param.ac_param[i].ACI_AIFSN & 0x0f) * pmlmeinfo->slotTime + aSifsTime;

		ECWMin = (pmlmeinfo->WMM_param.ac_param[i].CW & 0x0f);
		ECWMax = (pmlmeinfo->WMM_param.ac_param[i].CW & 0xf0) >> 4;
		TXOP = le16_to_cpu(pmlmeinfo->WMM_param.ac_param[i].TXOP_limit);

		acParm = AIFS | (ECWMin << 8) | (ECWMax << 12) | (TXOP << 16);

		switch (ACI)
		{
			case 0x0:
				rtw_hal_set_hwreg(padapter, HW_VAR_AC_PARAM_BE, (u8 *)(&acParm));
				acm_mask |= (ACM? BIT(1):0);
				break;

			case 0x1:
				rtw_hal_set_hwreg(padapter, HW_VAR_AC_PARAM_BK, (u8 *)(&acParm));
				//acm_mask |= (ACM? BIT(0):0);
				break;

			case 0x2:
				rtw_hal_set_hwreg(padapter, HW_VAR_AC_PARAM_VI, (u8 *)(&acParm));
				acm_mask |= (ACM? BIT(2):0);
				break;

			case 0x3:
				rtw_hal_set_hwreg(padapter, HW_VAR_AC_PARAM_VO, (u8 *)(&acParm));
				acm_mask |= (ACM? BIT(3):0);
				break;							
		}

		DBG_871X("WMM(%x): %x, %x\n", ACI, ACM, acParm);
	}

	if(padapter->registrypriv.acm_method == 1)
		rtw_hal_set_hwreg(padapter, HW_VAR_ACM_CTRL, (u8 *)(&acm_mask));
	else
		padapter->mlmepriv.acm_mask = acm_mask;

	return;	
}