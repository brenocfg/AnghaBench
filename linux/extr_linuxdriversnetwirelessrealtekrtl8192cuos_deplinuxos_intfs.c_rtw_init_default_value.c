#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct xmit_priv {int /*<<< orphan*/  frag_len; int /*<<< orphan*/  vcs_type; int /*<<< orphan*/  vcs; int /*<<< orphan*/  vcs_setting; } ;
struct security_priv {int dot118021XGrpKeyid; int /*<<< orphan*/  ndisencryptstatus; int /*<<< orphan*/  ndisauthtype; void* dot118021XGrpPrivacy; scalar_t__ dot11PrivacyKeyIndex; void* dot11PrivacyAlgrthm; int /*<<< orphan*/  dot11AuthAlgrthm; int /*<<< orphan*/  sw_decrypt; int /*<<< orphan*/  sw_encrypt; int /*<<< orphan*/  binstallGrpkey; } ;
struct registry_priv {int /*<<< orphan*/  software_decrypt; int /*<<< orphan*/  software_encrypt; int /*<<< orphan*/  frag_thresh; int /*<<< orphan*/  vcs_type; int /*<<< orphan*/  vrtl_carrier_sense; } ;
struct mlme_priv {int /*<<< orphan*/  scan_mode; int /*<<< orphan*/  scan_interval; } ;
struct TYPE_6__ {int bForceWriteInitGain; scalar_t__ bNotifyChannelChange; scalar_t__ bRxRSSIDisplay; void* bWritePortCancel; void* bReadPortCancel; struct security_priv securitypriv; struct mlme_priv mlmepriv; struct xmit_priv xmitpriv; struct registry_priv registrypriv; } ;
typedef  TYPE_1__ _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  Ndis802_11AuthModeOpen ; 
 int /*<<< orphan*/  Ndis802_11WEPDisabled ; 
 int /*<<< orphan*/  SCAN_ACTIVE ; 
 int /*<<< orphan*/  SCAN_INTERVAL ; 
 int /*<<< orphan*/  _FAIL ; 
 void* _FALSE ; 
 void* _NO_PRIVACY_ ; 
 int /*<<< orphan*/  _SUCCESS ; 
 int /*<<< orphan*/  dot11AuthAlgrthm_Open ; 
 int /*<<< orphan*/  rtw_hal_def_value_init (TYPE_1__*) ; 
 int /*<<< orphan*/  rtw_init_registrypriv_dev_network (TYPE_1__*) ; 
 int /*<<< orphan*/  rtw_update_registrypriv_dev_network (TYPE_1__*) ; 

u8 rtw_init_default_value(_adapter *padapter)
{
	u8 ret  = _SUCCESS;
	struct registry_priv* pregistrypriv = &padapter->registrypriv;
	struct xmit_priv	*pxmitpriv = &padapter->xmitpriv;
	struct mlme_priv *pmlmepriv= &padapter->mlmepriv;
	struct security_priv *psecuritypriv = &padapter->securitypriv;

	//xmit_priv
	pxmitpriv->vcs_setting = pregistrypriv->vrtl_carrier_sense;
	pxmitpriv->vcs = pregistrypriv->vcs_type;
	pxmitpriv->vcs_type = pregistrypriv->vcs_type;
	//pxmitpriv->rts_thresh = pregistrypriv->rts_thresh;
	pxmitpriv->frag_len = pregistrypriv->frag_thresh;



	//recv_priv


	//mlme_priv
	pmlmepriv->scan_interval = SCAN_INTERVAL;// 30*2 sec = 60sec
	pmlmepriv->scan_mode = SCAN_ACTIVE;

	//qos_priv
	//pmlmepriv->qospriv.qos_option = pregistrypriv->wmm_enable;

	//ht_priv
#ifdef CONFIG_80211N_HT
	pmlmepriv->htpriv.ampdu_enable = _FALSE;//set to disabled
#endif

	//security_priv
	//rtw_get_encrypt_decrypt_from_registrypriv(padapter);
	psecuritypriv->binstallGrpkey = _FAIL;
	psecuritypriv->sw_encrypt=pregistrypriv->software_encrypt;
	psecuritypriv->sw_decrypt=pregistrypriv->software_decrypt;

	psecuritypriv->dot11AuthAlgrthm = dot11AuthAlgrthm_Open; //open system
	psecuritypriv->dot11PrivacyAlgrthm = _NO_PRIVACY_;

	psecuritypriv->dot11PrivacyKeyIndex = 0;

	psecuritypriv->dot118021XGrpPrivacy = _NO_PRIVACY_;
	psecuritypriv->dot118021XGrpKeyid = 1;

	psecuritypriv->ndisauthtype = Ndis802_11AuthModeOpen;
	psecuritypriv->ndisencryptstatus = Ndis802_11WEPDisabled;


	//pwrctrl_priv


	//registry_priv
	rtw_init_registrypriv_dev_network(padapter);
	rtw_update_registrypriv_dev_network(padapter);


	//hal_priv
	rtw_hal_def_value_init(padapter);

	//misc.
	padapter->bReadPortCancel = _FALSE;
	padapter->bWritePortCancel = _FALSE;
	padapter->bRxRSSIDisplay = 0;
	padapter->bForceWriteInitGain = 1;
	padapter->bNotifyChannelChange = 0;
#ifdef CONFIG_P2P
	padapter->bShowGetP2PState = 1;
#endif
	return ret;
}