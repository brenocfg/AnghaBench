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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_9__ {scalar_t__ SsidLength; int /*<<< orphan*/  Ssid; } ;
struct mlme_priv {TYPE_2__ assoc_ssid; } ;
struct cmd_priv {int dummy; } ;
struct cmd_obj {unsigned char* parmbuf; int /*<<< orphan*/  cmdsz; scalar_t__ rspsz; int /*<<< orphan*/ * rsp; int /*<<< orphan*/  cmdcode; int /*<<< orphan*/  list; } ;
struct TYPE_11__ {int /*<<< orphan*/  Length; } ;
struct TYPE_8__ {TYPE_4__ dev_network; } ;
struct TYPE_10__ {TYPE_1__ registrypriv; struct mlme_priv mlmepriv; struct cmd_priv cmdpriv; } ;
typedef  TYPE_3__ _adapter ;
typedef  TYPE_4__ WLAN_BSSID_EX ;

/* Variables and functions */
 int /*<<< orphan*/  LED_CTL_START_TO_LINK ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _CreateBss_CMD_ ; 
 int /*<<< orphan*/  _FAIL ; 
 int /*<<< orphan*/  _SUCCESS ; 
 int /*<<< orphan*/  _drv_info_ ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  _module_rtl871x_cmd_c_ ; 
 int /*<<< orphan*/  _rtw_init_listhead (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_WLAN_BSSID_EX_sz (TYPE_4__*) ; 
 int /*<<< orphan*/  rtw_enqueue_cmd (struct cmd_priv*,struct cmd_obj*) ; 
 int /*<<< orphan*/  rtw_led_control (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ rtw_zmalloc (int) ; 

u8 rtw_createbss_cmd(_adapter  *padapter)
{
	struct cmd_obj*			pcmd;
	struct cmd_priv 			*pcmdpriv=&padapter->cmdpriv;
	struct mlme_priv			*pmlmepriv = &padapter->mlmepriv;
	WLAN_BSSID_EX		*pdev_network = &padapter->registrypriv.dev_network;
	u8	res=_SUCCESS;

_func_enter_;

	rtw_led_control(padapter, LED_CTL_START_TO_LINK);

	if (pmlmepriv->assoc_ssid.SsidLength == 0){
		RT_TRACE(_module_rtl871x_cmd_c_,_drv_info_,(" createbss for Any SSid:%s\n",pmlmepriv->assoc_ssid.Ssid));		
	} else {
		RT_TRACE(_module_rtl871x_cmd_c_,_drv_info_,(" createbss for SSid:%s\n", pmlmepriv->assoc_ssid.Ssid));
	}
		
	pcmd = (struct cmd_obj*)rtw_zmalloc(sizeof(struct cmd_obj));
	if(pcmd==NULL){
		res= _FAIL;
		goto exit;
	}

	_rtw_init_listhead(&pcmd->list);
	pcmd->cmdcode = _CreateBss_CMD_;
	pcmd->parmbuf = (unsigned char *)pdev_network;
	pcmd->cmdsz = get_WLAN_BSSID_EX_sz((WLAN_BSSID_EX*)pdev_network);
	pcmd->rsp = NULL;
	pcmd->rspsz = 0;	
	
	pdev_network->Length = pcmd->cmdsz;	

#ifdef CONFIG_RTL8712
	//notes: translate IELength & Length after assign the Length to cmdsz;
	pdev_network->Length = cpu_to_le32(pcmd->cmdsz);
	pdev_network->IELength = cpu_to_le32(pdev_network->IELength);
	pdev_network->Ssid.SsidLength = cpu_to_le32(pdev_network->Ssid.SsidLength);
#endif

	res = rtw_enqueue_cmd(pcmdpriv, pcmd);	

exit:

_func_exit_;	

	return res;
}