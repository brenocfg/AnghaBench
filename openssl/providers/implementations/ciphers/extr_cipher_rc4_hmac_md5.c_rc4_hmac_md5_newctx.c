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
typedef  void PROV_RC4_HMAC_MD5_CTX ;

/* Variables and functions */
 void* OPENSSL_zalloc (int) ; 
 int /*<<< orphan*/  PROV_CIPHER_HW_rc4_hmac_md5 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RC4_HMAC_MD5_BLOCK_BITS ; 
 int /*<<< orphan*/  RC4_HMAC_MD5_FLAGS ; 
 int /*<<< orphan*/  RC4_HMAC_MD5_IV_BITS ; 
 int /*<<< orphan*/  RC4_HMAC_MD5_KEY_BITS ; 
 int /*<<< orphan*/  RC4_HMAC_MD5_MODE ; 
 int /*<<< orphan*/  cipher_generic_initkey (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void *rc4_hmac_md5_newctx(void *provctx)
{
    PROV_RC4_HMAC_MD5_CTX *ctx = OPENSSL_zalloc(sizeof(*ctx));

    if (ctx != NULL)
        cipher_generic_initkey(ctx, RC4_HMAC_MD5_KEY_BITS,
                               RC4_HMAC_MD5_BLOCK_BITS,
                               RC4_HMAC_MD5_IV_BITS,
                               RC4_HMAC_MD5_MODE, RC4_HMAC_MD5_FLAGS,
                               PROV_CIPHER_HW_rc4_hmac_md5(RC4_HMAC_MD5_KEY_BITS),
                               NULL);
     return ctx;
}