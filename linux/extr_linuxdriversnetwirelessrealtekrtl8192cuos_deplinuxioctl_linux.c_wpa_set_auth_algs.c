#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct net_device {int dummy; } ;
struct TYPE_3__ {scalar_t__ ndisauthtype; int /*<<< orphan*/  dot11AuthAlgrthm; void* ndisencryptstatus; } ;
struct TYPE_4__ {TYPE_1__ securitypriv; } ;
typedef  TYPE_2__ _adapter ;

/* Variables and functions */
 int AUTH_ALG_LEAP ; 
 int AUTH_ALG_OPEN_SYSTEM ; 
 int AUTH_ALG_SHARED_KEY ; 
 int /*<<< orphan*/  DBG_871X (char*,...) ; 
 int EINVAL ; 
 scalar_t__ Ndis802_11AuthModeAutoSwitch ; 
 scalar_t__ Ndis802_11AuthModeOpen ; 
 scalar_t__ Ndis802_11AuthModeShared ; 
 scalar_t__ Ndis802_11AuthModeWPAPSK ; 
 void* Ndis802_11Encryption1Enabled ; 
 int /*<<< orphan*/  dot11AuthAlgrthm_Auto ; 
 int /*<<< orphan*/  dot11AuthAlgrthm_Open ; 
 int /*<<< orphan*/  dot11AuthAlgrthm_Shared ; 
 scalar_t__ rtw_netdev_priv (struct net_device*) ; 

__attribute__((used)) static int wpa_set_auth_algs(struct net_device *dev, u32 value)
{	
	_adapter *padapter = (_adapter *) rtw_netdev_priv(dev);
	int ret = 0;

	if ((value & AUTH_ALG_SHARED_KEY)&&(value & AUTH_ALG_OPEN_SYSTEM))
	{
		DBG_871X("wpa_set_auth_algs, AUTH_ALG_SHARED_KEY and  AUTH_ALG_OPEN_SYSTEM [value:0x%x]\n",value);
		padapter->securitypriv.ndisencryptstatus = Ndis802_11Encryption1Enabled;
		padapter->securitypriv.ndisauthtype = Ndis802_11AuthModeAutoSwitch;
		padapter->securitypriv.dot11AuthAlgrthm = dot11AuthAlgrthm_Auto;
	} 
	else if (value & AUTH_ALG_SHARED_KEY)
	{
		DBG_871X("wpa_set_auth_algs, AUTH_ALG_SHARED_KEY  [value:0x%x]\n",value);
		padapter->securitypriv.ndisencryptstatus = Ndis802_11Encryption1Enabled;

#ifdef CONFIG_PLATFORM_MT53XX
		padapter->securitypriv.ndisauthtype = Ndis802_11AuthModeAutoSwitch;
		padapter->securitypriv.dot11AuthAlgrthm = dot11AuthAlgrthm_Auto;
#else
		padapter->securitypriv.ndisauthtype = Ndis802_11AuthModeShared;
		padapter->securitypriv.dot11AuthAlgrthm = dot11AuthAlgrthm_Shared;
#endif
	} 
	else if(value & AUTH_ALG_OPEN_SYSTEM)
	{
		DBG_871X("wpa_set_auth_algs, AUTH_ALG_OPEN_SYSTEM\n");
		//padapter->securitypriv.ndisencryptstatus = Ndis802_11EncryptionDisabled;
		if(padapter->securitypriv.ndisauthtype < Ndis802_11AuthModeWPAPSK)
		{
#ifdef CONFIG_PLATFORM_MT53XX
			padapter->securitypriv.ndisauthtype = Ndis802_11AuthModeAutoSwitch;
			padapter->securitypriv.dot11AuthAlgrthm = dot11AuthAlgrthm_Auto;
#else
			padapter->securitypriv.ndisauthtype = Ndis802_11AuthModeOpen;
 			padapter->securitypriv.dot11AuthAlgrthm = dot11AuthAlgrthm_Open;
#endif
		}
		
	}
	else if(value & AUTH_ALG_LEAP)
	{
		DBG_871X("wpa_set_auth_algs, AUTH_ALG_LEAP\n");
	}
	else
	{
		DBG_871X("wpa_set_auth_algs, error!\n");
		ret = -EINVAL;
	}

	return ret;
	
}