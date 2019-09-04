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
struct security_priv {scalar_t__ dot11PrivacyAlgrthm; int key_mask; int dot11PrivacyKeyIndex; } ;
struct adapter {struct security_priv securitypriv; } ;
typedef  int sint ;

/* Variables and functions */
 int BIT (int) ; 
 scalar_t__ _WEP104_ ; 
 scalar_t__ _WEP40_ ; 
 int /*<<< orphan*/  rtw_set_key (struct adapter*,struct security_priv*,int,int,int) ; 

void rtw_sec_restore_wep_key(struct adapter *adapter)
{
	struct security_priv *securitypriv = &(adapter->securitypriv);
	sint keyid;

	if ((_WEP40_ == securitypriv->dot11PrivacyAlgrthm) || (_WEP104_ == securitypriv->dot11PrivacyAlgrthm)) {
		for (keyid = 0; keyid < 4; keyid++) {
			if (securitypriv->key_mask & BIT(keyid)) {
				if (keyid == securitypriv->dot11PrivacyKeyIndex)
					rtw_set_key(adapter, securitypriv, keyid, 1, false);
				else
					rtw_set_key(adapter, securitypriv, keyid, 0, false);
			}
		}
	}
}