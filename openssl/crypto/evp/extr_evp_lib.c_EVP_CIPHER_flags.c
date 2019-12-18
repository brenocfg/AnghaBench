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
typedef  int /*<<< orphan*/  EVP_CIPHER ;

/* Variables and functions */
 unsigned int EVP_CIPHER_flags (int /*<<< orphan*/  const*) ; 
 unsigned int EVP_CIPH_MODE ; 
 int /*<<< orphan*/  OSSL_CIPHER_PARAM_MODE ; 
 int /*<<< orphan*/  OSSL_PARAM_END ; 
 int /*<<< orphan*/  OSSL_PARAM_construct_uint (int /*<<< orphan*/ ,unsigned int*) ; 
 int evp_do_ciph_getparams (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

int EVP_CIPHER_mode(const EVP_CIPHER *cipher)
{
    int ok;
    unsigned int v = EVP_CIPHER_flags(cipher) & EVP_CIPH_MODE;
    OSSL_PARAM params[2] = { OSSL_PARAM_END, OSSL_PARAM_END };

    params[0] = OSSL_PARAM_construct_uint(OSSL_CIPHER_PARAM_MODE, &v);
    ok = evp_do_ciph_getparams(cipher, params);

    return ok != 0 ? (int)v : 0;
}