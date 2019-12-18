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
typedef  int /*<<< orphan*/  EVP_PKEY_CTX ;
typedef  int /*<<< orphan*/  EVP_PKEY ;

/* Variables and functions */
 size_t D ; 
 size_t DP ; 
 size_t DQ ; 
 size_t E ; 
 int /*<<< orphan*/  EVP_PKEY_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_PKEY_CTX_new_provided (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_PKEY_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_PKEY_fromdata (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_PKEY_key_fromdata_init (int /*<<< orphan*/ *) ; 
 size_t N ; 
 int /*<<< orphan*/  OSSL_PARAM_END ; 
 int /*<<< orphan*/  OSSL_PARAM_ulong (int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  OSSL_PKEY_PARAM_RSA_COEFFICIENT ; 
 int /*<<< orphan*/  OSSL_PKEY_PARAM_RSA_D ; 
 int /*<<< orphan*/  OSSL_PKEY_PARAM_RSA_E ; 
 int /*<<< orphan*/  OSSL_PKEY_PARAM_RSA_EXPONENT ; 
 int /*<<< orphan*/  OSSL_PKEY_PARAM_RSA_FACTOR ; 
 int /*<<< orphan*/  OSSL_PKEY_PARAM_RSA_N ; 
 size_t P ; 
 size_t Q ; 
 size_t QINV ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int test_fromdata_rsa(void)
{
    int ret = 0;
    EVP_PKEY_CTX *ctx = NULL;
    EVP_PKEY *pk = NULL;
    /*
     * 32-bit RSA key, extracted from this command,
     * executed with OpenSSL 1.0.2:
     *
     * openssl genrsa 32 | openssl rsa -text
     */
    static unsigned long key_numbers[] = {
        0xbc747fc5,              /* N */
        0x10001,                 /* E */
        0x7b133399,              /* D */
        0xe963,                  /* P */
        0xceb7,                  /* Q */
        0x8599,                  /* DP */
        0xbd87,                  /* DQ */
        0xcc3b,                  /* QINV */
    };
    OSSL_PARAM fromdata_params[] = {
        OSSL_PARAM_ulong(OSSL_PKEY_PARAM_RSA_N, &key_numbers[N]),
        OSSL_PARAM_ulong(OSSL_PKEY_PARAM_RSA_E, &key_numbers[E]),
        OSSL_PARAM_ulong(OSSL_PKEY_PARAM_RSA_D, &key_numbers[D]),
        OSSL_PARAM_ulong(OSSL_PKEY_PARAM_RSA_FACTOR, &key_numbers[P]),
        OSSL_PARAM_ulong(OSSL_PKEY_PARAM_RSA_FACTOR, &key_numbers[Q]),
        OSSL_PARAM_ulong(OSSL_PKEY_PARAM_RSA_EXPONENT, &key_numbers[DP]),
        OSSL_PARAM_ulong(OSSL_PKEY_PARAM_RSA_EXPONENT, &key_numbers[DQ]),
        OSSL_PARAM_ulong(OSSL_PKEY_PARAM_RSA_COEFFICIENT, &key_numbers[QINV]),
        OSSL_PARAM_END
    };

    if (!TEST_ptr(ctx = EVP_PKEY_CTX_new_provided(NULL, "RSA", NULL)))
        goto err;

    if (!TEST_true(EVP_PKEY_key_fromdata_init(ctx))
        || !TEST_true(EVP_PKEY_fromdata(ctx, &pk, fromdata_params)))
        goto err;

    /*
     * TODO(3.0) We can't do much more at this point without using internals,
     * because RSA functionality is still missing.  When the time comes, it
     * would be nice to try and do something "useful" with this key, such
     * as signing a small piece of data.
     */
    ret = 1;

 err:
    EVP_PKEY_free(pk);
    EVP_PKEY_CTX_free(ctx);

    return ret;
}