#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  void* u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct security_priv {scalar_t__ dot11AuthAlgrthm; int dot118021XGrpKeyid; void* ndisencryptstatus; void* ndisauthtype; void* dot118021XGrpPrivacy; scalar_t__ dot11PrivacyKeyIndex; void* dot11PrivacyAlgrthm; int /*<<< orphan*/  btkip_countermeasure_time; void* btkip_countermeasure; void* PMKIDIndex; int /*<<< orphan*/ * PMKIDList; } ;
struct rt_pmkid_list {int dummy; } ;
struct adapter {struct security_priv securitypriv; } ;

/* Variables and functions */
 int NUM_PMKID_CACHE ; 
 void* Ndis802_11AuthModeOpen ; 
 void* Ndis802_11WEPDisabled ; 
 void* _NO_PRIVACY_ ; 
 int /*<<< orphan*/ * backup_pmkid ; 
 scalar_t__ dot11AuthAlgrthm_8021X ; 
 scalar_t__ dot11AuthAlgrthm_Open ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 

void rtw_reset_securitypriv(struct adapter *adapter)
{
	u8	backup_index = 0;
	u8	backup_counter = 0x00;
	u32	backup_time = 0;

	if (adapter->securitypriv.dot11AuthAlgrthm == dot11AuthAlgrthm_8021X) {
		/* 802.1x */
		/*  We have to backup the PMK information for WiFi PMK Caching test item. */
		/*  Backup the btkip_countermeasure information. */
		/*  When the countermeasure is trigger, the driver have to disconnect with AP for 60 seconds. */
		memcpy(&backup_pmkid[0], &adapter->securitypriv.PMKIDList[0], sizeof(struct rt_pmkid_list) * NUM_PMKID_CACHE);
		backup_index = adapter->securitypriv.PMKIDIndex;
		backup_counter = adapter->securitypriv.btkip_countermeasure;
		backup_time = adapter->securitypriv.btkip_countermeasure_time;
		memset((unsigned char *)&adapter->securitypriv, 0, sizeof(struct security_priv));

		/*  Restore the PMK information to securitypriv structure for the following connection. */
		memcpy(&adapter->securitypriv.PMKIDList[0],
			    &backup_pmkid[0],
			    sizeof(struct rt_pmkid_list) * NUM_PMKID_CACHE);
		adapter->securitypriv.PMKIDIndex = backup_index;
		adapter->securitypriv.btkip_countermeasure = backup_counter;
		adapter->securitypriv.btkip_countermeasure_time = backup_time;
		adapter->securitypriv.ndisauthtype = Ndis802_11AuthModeOpen;
		adapter->securitypriv.ndisencryptstatus = Ndis802_11WEPDisabled;
	} else {
		/* reset values in securitypriv */
		struct security_priv *psec_priv = &adapter->securitypriv;

		psec_priv->dot11AuthAlgrthm = dot11AuthAlgrthm_Open;
		psec_priv->dot11PrivacyAlgrthm = _NO_PRIVACY_;
		psec_priv->dot11PrivacyKeyIndex = 0;
		psec_priv->dot118021XGrpPrivacy = _NO_PRIVACY_;
		psec_priv->dot118021XGrpKeyid = 1;
		psec_priv->ndisauthtype = Ndis802_11AuthModeOpen;
		psec_priv->ndisencryptstatus = Ndis802_11WEPDisabled;
	}
}