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
typedef  int /*<<< orphan*/  OSSL_PARAM ;

/* Variables and functions */
 int /*<<< orphan*/  RC4_HMAC_MD5_BLOCK_BITS ; 
 int /*<<< orphan*/  RC4_HMAC_MD5_FLAGS ; 
 int /*<<< orphan*/  RC4_HMAC_MD5_IV_BITS ; 
 int /*<<< orphan*/  RC4_HMAC_MD5_KEY_BITS ; 
 int /*<<< orphan*/  RC4_HMAC_MD5_MODE ; 
 int cipher_generic_get_params (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rc4_hmac_md5_get_params(OSSL_PARAM params[])
{
    return cipher_generic_get_params(params, RC4_HMAC_MD5_MODE,
                                     RC4_HMAC_MD5_FLAGS,
                                     RC4_HMAC_MD5_KEY_BITS,
                                     RC4_HMAC_MD5_BLOCK_BITS,
                                     RC4_HMAC_MD5_IV_BITS);
}