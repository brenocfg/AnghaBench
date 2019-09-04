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
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int aead_decrypt (struct crypto_aead*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  be16_to_cpup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int ieee80211_aes_gcm_decrypt(struct crypto_aead *tfm,
					    u8 *j_0, u8 *aad, u8 *data,
					    size_t data_len, u8 *mic)
{
	return aead_decrypt(tfm, j_0, aad + 2,
			    be16_to_cpup((__be16 *)aad),
			    data, data_len, mic);
}