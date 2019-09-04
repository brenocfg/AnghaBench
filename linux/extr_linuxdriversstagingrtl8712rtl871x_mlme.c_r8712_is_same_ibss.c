#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ Privacy; } ;
struct wlan_network {TYPE_1__ network; } ;
struct security_priv {scalar_t__ PrivacyAlgrthm; } ;
struct _adapter {struct security_priv securitypriv; } ;

/* Variables and functions */
 scalar_t__ _NO_PRIVACY_ ; 
 scalar_t__ cpu_to_le32 (int) ; 

int r8712_is_same_ibss(struct _adapter *adapter, struct wlan_network *pnetwork)
{
	int ret = true;
	struct security_priv *psecuritypriv = &adapter->securitypriv;

	if ((psecuritypriv->PrivacyAlgrthm != _NO_PRIVACY_) &&
		    (pnetwork->network.Privacy == cpu_to_le32(0)))
		ret = false;
	else if ((psecuritypriv->PrivacyAlgrthm == _NO_PRIVACY_) &&
		 (pnetwork->network.Privacy == cpu_to_le32(1)))
		ret = false;
	else
		ret = true;
	return ret;

}