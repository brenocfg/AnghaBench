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
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int dummy; } ;
struct ieee80211_key {int /*<<< orphan*/  conf; } ;
struct crypto_cipher {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ieee80211_get_tkip_p2k (int /*<<< orphan*/ *,struct sk_buff*,int /*<<< orphan*/ *) ; 
 int ieee80211_wep_encrypt_data (struct crypto_cipher*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,size_t) ; 

int ieee80211_tkip_encrypt_data(struct crypto_cipher *tfm,
				struct ieee80211_key *key,
				struct sk_buff *skb,
				u8 *payload, size_t payload_len)
{
	u8 rc4key[16];

	ieee80211_get_tkip_p2k(&key->conf, skb, rc4key);

	return ieee80211_wep_encrypt_data(tfm, rc4key, 16,
					  payload, payload_len);
}