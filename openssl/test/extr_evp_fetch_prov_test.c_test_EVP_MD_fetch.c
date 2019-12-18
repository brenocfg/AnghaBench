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
typedef  int /*<<< orphan*/  EVP_MD ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_MD_block_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_MD_fetch (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_MD_meth_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_MD_nid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_MD_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_MD_up_ref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_sha256 () ; 
 int /*<<< orphan*/  NID_sha256 ; 
 int /*<<< orphan*/  OPENSSL_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OPENSSL_thread_stop_ex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSSL_PROVIDER_unload (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHA256_CBLOCK ; 
 int /*<<< orphan*/  SHA256_DIGEST_LENGTH ; 
 int /*<<< orphan*/  TEST_int_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_ptr_null (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  calculate_digest (int /*<<< orphan*/ *,char const*,int,unsigned char const*) ; 
 scalar_t__ expected_fetch_result ; 
 int /*<<< orphan*/  fetch_property ; 
 int /*<<< orphan*/  load_providers (int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 scalar_t__ use_default_ctx ; 

__attribute__((used)) static int test_EVP_MD_fetch(void)
{
    OPENSSL_CTX *ctx = NULL;
    EVP_MD *md = NULL;
    OSSL_PROVIDER *prov[2] = {NULL, NULL};
    int ret = 0;
    const char testmsg[] = "Hello world";
    const unsigned char exptd[] = {
      0x27, 0x51, 0x8b, 0xa9, 0x68, 0x30, 0x11, 0xf6, 0xb3, 0x96, 0x07, 0x2c,
      0x05, 0xf6, 0x65, 0x6d, 0x04, 0xf5, 0xfb, 0xc3, 0x78, 0x7c, 0xf9, 0x24,
      0x90, 0xec, 0x60, 0x6e, 0x50, 0x92, 0xe3, 0x26
    };

    if (use_default_ctx == 0 && !load_providers(&ctx, prov))
        goto err;

    /* Implicit fetching of the MD should produce the expected result */
    if (!TEST_true(calculate_digest(EVP_sha256(), testmsg, sizeof(testmsg),
                                    exptd))
            || !TEST_int_eq(EVP_MD_size(EVP_sha256()), SHA256_DIGEST_LENGTH)
            || !TEST_int_eq(EVP_MD_block_size(EVP_sha256()), SHA256_CBLOCK))
        goto err;

    /* Fetch the digest from a provider using properties. */
    md = EVP_MD_fetch(ctx, "SHA256", fetch_property);
    if (expected_fetch_result != 0) {
        if (!TEST_ptr(md)
            || !TEST_int_eq(EVP_MD_nid(md), NID_sha256)
            || !TEST_true(calculate_digest(md, testmsg, sizeof(testmsg), exptd))
            || !TEST_int_eq(EVP_MD_size(md), SHA256_DIGEST_LENGTH)
            || !TEST_int_eq(EVP_MD_block_size(md), SHA256_CBLOCK))
        goto err;

        /* Also test EVP_MD_up_ref() while we're doing this */
        if (!TEST_true(EVP_MD_up_ref(md)))
            goto err;
        /* Ref count should now be 2. Release first one here */
        EVP_MD_meth_free(md);
    } else {
        if (!TEST_ptr_null(md))
            goto err;
    }
    ret = 1;

err:
    EVP_MD_meth_free(md);
    OSSL_PROVIDER_unload(prov[0]);
    OSSL_PROVIDER_unload(prov[1]);
    /* Not normally needed, but we would like to test that
     * OPENSSL_thread_stop_ex() behaves as expected.
     */
    if (ctx != NULL) {
        OPENSSL_thread_stop_ex(ctx);
        OPENSSL_CTX_free(ctx);
    }
    return ret;
}