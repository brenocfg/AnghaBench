#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  void* u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct security_priv {scalar_t__ dot11AuthAlgrthm; unsigned char* PMKIDList; int dot118021XGrpKeyid; void* ndisencryptstatus; void* ndisauthtype; void* dot118021XGrpPrivacy; scalar_t__ dot11PrivacyKeyIndex; void* dot11PrivacyAlgrthm; int /*<<< orphan*/  btkip_countermeasure_time; void* btkip_countermeasure; void* PMKIDIndex; } ;
struct mlme_ext_priv {int dummy; } ;
typedef  int /*<<< orphan*/  _irqL ;
struct TYPE_3__ {int /*<<< orphan*/  security_key_mutex; struct security_priv securitypriv; struct mlme_ext_priv mlmeextpriv; } ;
typedef  TYPE_1__ _adapter ;
typedef  int /*<<< orphan*/  RT_PMKID_LIST ;

/* Variables and functions */
 int NUM_PMKID_CACHE ; 
 void* Ndis802_11AuthModeOpen ; 
 void* Ndis802_11WEPDisabled ; 
 void* _NO_PRIVACY_ ; 
 int /*<<< orphan*/  _enter_critical_bh (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _exit_critical_bh (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _rtw_memcpy (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  _rtw_memset (unsigned char*,int,int) ; 
 unsigned char* backupPMKIDList ; 
 scalar_t__ dot11AuthAlgrthm_8021X ; 
 scalar_t__ dot11AuthAlgrthm_Open ; 

void rtw_reset_securitypriv( _adapter *adapter )
{
	u8	backupPMKIDIndex = 0;
	u8	backupTKIPCountermeasure = 0x00;
	u32	backupTKIPcountermeasure_time = 0;
	// add for CONFIG_IEEE80211W, none 11w also can use
	_irqL irqL;
	struct mlme_ext_priv	*pmlmeext = &adapter->mlmeextpriv;
	
	_enter_critical_bh(&adapter->security_key_mutex, &irqL);
	
	if(adapter->securitypriv.dot11AuthAlgrthm == dot11AuthAlgrthm_8021X)//802.1x
	{		 
		// Added by Albert 2009/02/18
		// We have to backup the PMK information for WiFi PMK Caching test item.
		//
		// Backup the btkip_countermeasure information.
		// When the countermeasure is trigger, the driver have to disconnect with AP for 60 seconds.

		_rtw_memset( &backupPMKIDList[ 0 ], 0x00, sizeof( RT_PMKID_LIST ) * NUM_PMKID_CACHE );

		_rtw_memcpy( &backupPMKIDList[ 0 ], &adapter->securitypriv.PMKIDList[ 0 ], sizeof( RT_PMKID_LIST ) * NUM_PMKID_CACHE );
		backupPMKIDIndex = adapter->securitypriv.PMKIDIndex;
		backupTKIPCountermeasure = adapter->securitypriv.btkip_countermeasure;
		backupTKIPcountermeasure_time = adapter->securitypriv.btkip_countermeasure_time;		
#ifdef CONFIG_IEEE80211W
		//reset RX BIP packet number
		pmlmeext->mgnt_80211w_IPN_rx = 0;
#endif //CONFIG_IEEE80211W
		_rtw_memset((unsigned char *)&adapter->securitypriv, 0, sizeof (struct security_priv));
		//_init_timer(&(adapter->securitypriv.tkip_timer),adapter->pnetdev, rtw_use_tkipkey_handler, adapter);

		// Added by Albert 2009/02/18
		// Restore the PMK information to securitypriv structure for the following connection.
		_rtw_memcpy( &adapter->securitypriv.PMKIDList[ 0 ], &backupPMKIDList[ 0 ], sizeof( RT_PMKID_LIST ) * NUM_PMKID_CACHE );
		adapter->securitypriv.PMKIDIndex = backupPMKIDIndex;
		adapter->securitypriv.btkip_countermeasure = backupTKIPCountermeasure;
		adapter->securitypriv.btkip_countermeasure_time = backupTKIPcountermeasure_time;		

		adapter->securitypriv.ndisauthtype = Ndis802_11AuthModeOpen;
		adapter->securitypriv.ndisencryptstatus = Ndis802_11WEPDisabled;

	}
	else //reset values in securitypriv 
	{
		//if(adapter->mlmepriv.fw_state & WIFI_STATION_STATE)
		//{
		struct security_priv *psec_priv=&adapter->securitypriv;

		psec_priv->dot11AuthAlgrthm =dot11AuthAlgrthm_Open;  //open system
		psec_priv->dot11PrivacyAlgrthm = _NO_PRIVACY_;
		psec_priv->dot11PrivacyKeyIndex = 0;

		psec_priv->dot118021XGrpPrivacy = _NO_PRIVACY_;
		psec_priv->dot118021XGrpKeyid = 1;

		psec_priv->ndisauthtype = Ndis802_11AuthModeOpen;
		psec_priv->ndisencryptstatus = Ndis802_11WEPDisabled;
		//}
	}
	// add for CONFIG_IEEE80211W, none 11w also can use
	_exit_critical_bh(&adapter->security_key_mutex, &irqL);
}