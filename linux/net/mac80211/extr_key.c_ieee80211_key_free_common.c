#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  tfm; } ;
struct TYPE_10__ {int /*<<< orphan*/  tfm; } ;
struct TYPE_9__ {int /*<<< orphan*/  tfm; } ;
struct TYPE_8__ {int /*<<< orphan*/  tfm; } ;
struct TYPE_12__ {TYPE_5__ gcmp; TYPE_4__ aes_gmac; TYPE_3__ aes_cmac; TYPE_2__ ccmp; } ;
struct TYPE_7__ {int cipher; } ;
struct ieee80211_key {TYPE_6__ u; TYPE_1__ conf; } ;

/* Variables and functions */
#define  WLAN_CIPHER_SUITE_AES_CMAC 135 
#define  WLAN_CIPHER_SUITE_BIP_CMAC_256 134 
#define  WLAN_CIPHER_SUITE_BIP_GMAC_128 133 
#define  WLAN_CIPHER_SUITE_BIP_GMAC_256 132 
#define  WLAN_CIPHER_SUITE_CCMP 131 
#define  WLAN_CIPHER_SUITE_CCMP_256 130 
#define  WLAN_CIPHER_SUITE_GCMP 129 
#define  WLAN_CIPHER_SUITE_GCMP_256 128 
 int /*<<< orphan*/  ieee80211_aes_cmac_key_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_aes_gcm_key_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_aes_gmac_key_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_aes_key_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kzfree (struct ieee80211_key*) ; 

__attribute__((used)) static void ieee80211_key_free_common(struct ieee80211_key *key)
{
	switch (key->conf.cipher) {
	case WLAN_CIPHER_SUITE_CCMP:
	case WLAN_CIPHER_SUITE_CCMP_256:
		ieee80211_aes_key_free(key->u.ccmp.tfm);
		break;
	case WLAN_CIPHER_SUITE_AES_CMAC:
	case WLAN_CIPHER_SUITE_BIP_CMAC_256:
		ieee80211_aes_cmac_key_free(key->u.aes_cmac.tfm);
		break;
	case WLAN_CIPHER_SUITE_BIP_GMAC_128:
	case WLAN_CIPHER_SUITE_BIP_GMAC_256:
		ieee80211_aes_gmac_key_free(key->u.aes_gmac.tfm);
		break;
	case WLAN_CIPHER_SUITE_GCMP:
	case WLAN_CIPHER_SUITE_GCMP_256:
		ieee80211_aes_gcm_key_free(key->u.gcmp.tfm);
		break;
	}
	kzfree(key);
}