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
struct crypto_aead {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_GCMP_MIC_LEN ; 
 struct crypto_aead* aead_key_setup_encrypt (char*,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct crypto_aead *
ieee80211_aes_gcm_key_setup_encrypt(const u8 key[], size_t key_len)
{
	return aead_key_setup_encrypt("gcm(aes)", key,
				      key_len, IEEE80211_GCMP_MIC_LEN);
}