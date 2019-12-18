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
typedef  int /*<<< orphan*/  ENGINE ;

/* Variables and functions */
 int /*<<< orphan*/  DH_get_default_method () ; 
 int /*<<< orphan*/  DSA_get_default_method () ; 
 int /*<<< orphan*/  EC_KEY_OpenSSL () ; 
 int /*<<< orphan*/  ENGINE_set_DH (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENGINE_set_DSA (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENGINE_set_EC (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENGINE_set_RAND (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENGINE_set_RSA (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENGINE_set_ciphers (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENGINE_set_destroy_function (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENGINE_set_digests (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENGINE_set_id (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENGINE_set_load_privkey_function (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENGINE_set_name (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENGINE_set_pkey_meths (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RAND_OpenSSL () ; 
 int /*<<< orphan*/  RSA_get_default_method () ; 
 int /*<<< orphan*/  engine_openssl_id ; 
 int /*<<< orphan*/  engine_openssl_name ; 
 int /*<<< orphan*/  openssl_ciphers ; 
 int /*<<< orphan*/  openssl_destroy ; 
 int /*<<< orphan*/  openssl_digests ; 
 int /*<<< orphan*/  openssl_load_privkey ; 
 int /*<<< orphan*/  ossl_pkey_meths ; 
 int /*<<< orphan*/  ossl_register_hmac_meth () ; 

__attribute__((used)) static int bind_helper(ENGINE *e)
{
    if (!ENGINE_set_id(e, engine_openssl_id)
        || !ENGINE_set_name(e, engine_openssl_name)
        || !ENGINE_set_destroy_function(e, openssl_destroy)
#ifndef TEST_ENG_OPENSSL_NO_ALGORITHMS
# ifndef OPENSSL_NO_RSA
        || !ENGINE_set_RSA(e, RSA_get_default_method())
# endif
# ifndef OPENSSL_NO_DSA
        || !ENGINE_set_DSA(e, DSA_get_default_method())
# endif
# ifndef OPENSSL_NO_EC
        || !ENGINE_set_EC(e, EC_KEY_OpenSSL())
# endif
# ifndef OPENSSL_NO_DH
        || !ENGINE_set_DH(e, DH_get_default_method())
# endif
        || !ENGINE_set_RAND(e, RAND_OpenSSL())
# ifdef TEST_ENG_OPENSSL_RC4
        || !ENGINE_set_ciphers(e, openssl_ciphers)
# endif
# ifdef TEST_ENG_OPENSSL_SHA
        || !ENGINE_set_digests(e, openssl_digests)
# endif
#endif
#ifdef TEST_ENG_OPENSSL_PKEY
        || !ENGINE_set_load_privkey_function(e, openssl_load_privkey)
#endif
#ifdef TEST_ENG_OPENSSL_HMAC
        || !ossl_register_hmac_meth()
        || !ENGINE_set_pkey_meths(e, ossl_pkey_meths)
#endif
        )
        return 0;
    /*
     * If we add errors to this ENGINE, ensure the error handling is setup
     * here
     */
    /* openssl_load_error_strings(); */
    return 1;
}