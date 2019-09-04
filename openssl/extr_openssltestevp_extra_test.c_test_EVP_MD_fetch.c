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
 int /*<<< orphan*/ * EVP_MD_fetch (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  EVP_MD_meth_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_MD_nid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_MD_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_MD_upref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_sha256 () ; 
 int /*<<< orphan*/  NID_sha256 ; 
 int /*<<< orphan*/  OPENSSL_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * OPENSSL_CTX_new () ; 
 int /*<<< orphan*/ * OSSL_PROVIDER_load (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  OSSL_PROVIDER_unload (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHA256_CBLOCK ; 
 int /*<<< orphan*/  SHA256_DIGEST_LENGTH ; 
 int /*<<< orphan*/  TEST_int_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_ptr_null (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  calculate_digest (int /*<<< orphan*/ *,char const*,int,unsigned char const*) ; 

__attribute__((used)) static int test_EVP_MD_fetch(int tst)
{
    OPENSSL_CTX *ctx = NULL;
    EVP_MD *md = NULL;
    OSSL_PROVIDER *defltprov = NULL, *fipsprov = NULL;
    int ret = 0;
    const char testmsg[] = "Hello world";
    const unsigned char exptd[] = {
      0x27, 0x51, 0x8b, 0xa9, 0x68, 0x30, 0x11, 0xf6, 0xb3, 0x96, 0x07, 0x2c,
      0x05, 0xf6, 0x65, 0x6d, 0x04, 0xf5, 0xfb, 0xc3, 0x78, 0x7c, 0xf9, 0x24,
      0x90, 0xec, 0x60, 0x6e, 0x50, 0x92, 0xe3, 0x26
    };

    if (tst > 0) {
        ctx = OPENSSL_CTX_new();
        if (!TEST_ptr(ctx))
            goto err;

        if (tst == 2 || tst == 3) {
            defltprov = OSSL_PROVIDER_load(ctx, "default");
            if (!TEST_ptr(defltprov))
                goto err;
        }
        if (tst == 3 || tst == 4) {
            fipsprov = OSSL_PROVIDER_load(ctx, "fips");
            if (!TEST_ptr(fipsprov))
                goto err;
        }
    }

    /* Implicit fetching of the MD should produce the expected result */
    if (!TEST_true(calculate_digest(EVP_sha256(), testmsg, sizeof(testmsg),
                                    exptd))
            || !TEST_int_eq(EVP_MD_size(EVP_sha256()), SHA256_DIGEST_LENGTH)
            || !TEST_int_eq(EVP_MD_block_size(EVP_sha256()), SHA256_CBLOCK))
        goto err;

    /*
     * Test that without specifying any properties we can get a sha256 md from a
     * provider.
     */
    if (!TEST_ptr(md = EVP_MD_fetch(ctx, "SHA256", NULL))
            || !TEST_ptr(md)
            || !TEST_int_eq(EVP_MD_nid(md), NID_sha256)
            || !TEST_true(calculate_digest(md, testmsg, sizeof(testmsg), exptd))
            || !TEST_int_eq(EVP_MD_size(md), SHA256_DIGEST_LENGTH)
            || !TEST_int_eq(EVP_MD_block_size(md), SHA256_CBLOCK))
        goto err;

    /* Also test EVP_MD_upref() while we're doing this */
    if (!TEST_true(EVP_MD_upref(md)))
        goto err;
    /* Ref count should now be 2. Release both */
    EVP_MD_meth_free(md);
    EVP_MD_meth_free(md);
    md = NULL;

    /*
     * In tests 0 - 2 we've only loaded the default provider so explicitly
     * asking for a non-default implementation should fail. In tests 3 and 4 we
     * have the FIPS provider loaded so we should succeed in that case.
     */
    md = EVP_MD_fetch(ctx, "SHA256", "default=no");
    if (tst == 3 || tst == 4) {
        if (!TEST_ptr(md)
                || !TEST_true(calculate_digest(md, testmsg, sizeof(testmsg),
                                               exptd)))
            goto err;
    } else  {
        if (!TEST_ptr_null(md))
            goto err;
    }

    EVP_MD_meth_free(md);
    md = NULL;

    /*
     * Explicitly asking for the default implementation should succeeed except
     * in test 4 where the default provider is not loaded.
     */
    md = EVP_MD_fetch(ctx, "SHA256", "default=yes");
    if (tst != 4) {
        if (!TEST_ptr(md)
                || !TEST_int_eq(EVP_MD_nid(md), NID_sha256)
                || !TEST_true(calculate_digest(md, testmsg, sizeof(testmsg),
                                               exptd))
                || !TEST_int_eq(EVP_MD_size(md), SHA256_DIGEST_LENGTH)
                || !TEST_int_eq(EVP_MD_block_size(md), SHA256_CBLOCK))
            goto err;
    } else {
        if (!TEST_ptr_null(md))
            goto err;
    }

    EVP_MD_meth_free(md);
    md = NULL;

    /*
     * Explicitly asking for a fips implementation should succeed if we have
     * the FIPS provider loaded and fail otherwise
     */
    md = EVP_MD_fetch(ctx, "SHA256", "fips=yes");
    if (tst == 3 || tst == 4) {
        if (!TEST_ptr(md)
                || !TEST_true(calculate_digest(md, testmsg, sizeof(testmsg),
                                               exptd)))
            goto err;
    } else  {
        if (!TEST_ptr_null(md))
            goto err;
    }


    ret = 1;

 err:
    EVP_MD_meth_free(md);
    OSSL_PROVIDER_unload(defltprov);
    OSSL_PROVIDER_unload(fipsprov);
    OPENSSL_CTX_free(ctx);
    return ret;
}