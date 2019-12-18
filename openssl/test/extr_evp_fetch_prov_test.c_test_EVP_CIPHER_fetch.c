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
typedef  int /*<<< orphan*/  testmsg ;
typedef  int /*<<< orphan*/  OSSL_PROVIDER ;
typedef  int /*<<< orphan*/  OPENSSL_CTX ;
typedef  int /*<<< orphan*/  EVP_CIPHER ;

/* Variables and functions */
 int /*<<< orphan*/ * EVP_CIPHER_fetch (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_CIPHER_meth_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_CIPHER_up_ref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_aes_128_cbc () ; 
 int /*<<< orphan*/  OPENSSL_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSSL_PROVIDER_unload (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_ptr_null (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  encrypt_decrypt (int /*<<< orphan*/ *,unsigned char const*,int) ; 
 scalar_t__ expected_fetch_result ; 
 int /*<<< orphan*/  fetch_property ; 
 int /*<<< orphan*/  load_providers (int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 scalar_t__ use_default_ctx ; 

__attribute__((used)) static int test_EVP_CIPHER_fetch(void)
{
    OPENSSL_CTX *ctx = NULL;
    EVP_CIPHER *cipher = NULL;
    OSSL_PROVIDER *prov[2] = {NULL, NULL};
    int ret = 0;
    const unsigned char testmsg[] = "Hello world";

    if (use_default_ctx == 0 && !load_providers(&ctx, prov))
        goto err;

    /* Implicit fetching of the cipher should produce the expected result */
    if (!TEST_true(encrypt_decrypt(EVP_aes_128_cbc(), testmsg, sizeof(testmsg))))
        goto err;

    /* Fetch the cipher from a provider using properties. */
    cipher = EVP_CIPHER_fetch(ctx, "AES-128-CBC", fetch_property);
    if (expected_fetch_result != 0) {
        if (!TEST_ptr(cipher)
            || !TEST_true(encrypt_decrypt(cipher, testmsg, sizeof(testmsg)))) {
            if (!TEST_true(EVP_CIPHER_up_ref(cipher)))
                goto err;
            /* Ref count should now be 2. Release first one here */
            EVP_CIPHER_meth_free(cipher);
        }
    } else {
        if (!TEST_ptr_null(cipher))
            goto err;
    }
    ret = 1;
err:
    EVP_CIPHER_meth_free(cipher);
    OSSL_PROVIDER_unload(prov[0]);
    OSSL_PROVIDER_unload(prov[1]);
    OPENSSL_CTX_free(ctx);
    return ret;
}