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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct crypto_cipher {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/ * coeff; } ;
typedef  TYPE_1__ emmh32_context ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 scalar_t__* aes_counter ; 
 int /*<<< orphan*/  crypto_cipher_encrypt_one (struct crypto_cipher*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  crypto_cipher_setkey (struct crypto_cipher*,scalar_t__*,int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__*,int) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void emmh32_setseed(emmh32_context *context, u8 *pkey, int keylen,
			   struct crypto_cipher *tfm)
{
  /* take the keying material, expand if necessary, truncate at 16-bytes */
  /* run through AES counter mode to generate context->coeff[] */
  
	int i,j;
	u32 counter;
	u8 *cipher, plain[16];

	crypto_cipher_setkey(tfm, pkey, 16);
	counter = 0;
	for (i = 0; i < ARRAY_SIZE(context->coeff); ) {
		aes_counter[15] = (u8)(counter >> 0);
		aes_counter[14] = (u8)(counter >> 8);
		aes_counter[13] = (u8)(counter >> 16);
		aes_counter[12] = (u8)(counter >> 24);
		counter++;
		memcpy (plain, aes_counter, 16);
		crypto_cipher_encrypt_one(tfm, plain, plain);
		cipher = plain;
		for (j = 0; (j < 16) && (i < ARRAY_SIZE(context->coeff)); ) {
			context->coeff[i++] = ntohl(*(__be32 *)&cipher[j]);
			j += 4;
		}
	}
}