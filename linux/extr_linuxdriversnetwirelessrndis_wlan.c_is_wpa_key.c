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
typedef  size_t u8 ;
struct rndis_wlan_private {TYPE_1__* encr_keys; } ;
struct TYPE_2__ {int cipher; } ;

/* Variables and functions */
 int WLAN_CIPHER_SUITE_CCMP ; 
 int WLAN_CIPHER_SUITE_TKIP ; 

__attribute__((used)) static bool is_wpa_key(struct rndis_wlan_private *priv, u8 idx)
{
	int cipher = priv->encr_keys[idx].cipher;

	return (cipher == WLAN_CIPHER_SUITE_CCMP ||
		cipher == WLAN_CIPHER_SUITE_TKIP);
}