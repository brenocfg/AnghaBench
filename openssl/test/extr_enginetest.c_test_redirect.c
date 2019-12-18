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
typedef  int /*<<< orphan*/  pt ;
typedef  unsigned char EVP_PKEY_CTX ;
typedef  unsigned char EVP_PKEY ;
typedef  unsigned char ENGINE ;

/* Variables and functions */
 int /*<<< orphan*/  ENGINE_free (unsigned char*) ; 
 unsigned char* ENGINE_new () ; 
 scalar_t__ ENGINE_set_id (unsigned char*,char*) ; 
 scalar_t__ ENGINE_set_name (unsigned char*,char*) ; 
 int /*<<< orphan*/  ENGINE_set_pkey_meths (unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_PKEY_CTX_free (unsigned char*) ; 
 unsigned char* EVP_PKEY_CTX_new (unsigned char*,unsigned char*) ; 
 int /*<<< orphan*/  EVP_PKEY_RSA ; 
 scalar_t__ EVP_PKEY_encrypt (unsigned char*,unsigned char*,size_t*,unsigned char const*,int) ; 
 scalar_t__ EVP_PKEY_encrypt_init (unsigned char*) ; 
 int /*<<< orphan*/  EVP_PKEY_free (unsigned char*) ; 
 unsigned char* EVP_PKEY_meth_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_PKEY_meth_set_encrypt (unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ EVP_PKEY_set1_engine (unsigned char*,unsigned char*) ; 
 size_t EVP_PKEY_size (unsigned char*) ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 unsigned char* OPENSSL_malloc (size_t) ; 
 int /*<<< orphan*/  TEST_false (scalar_t__) ; 
 int /*<<< orphan*/  TEST_info (char*) ; 
 int /*<<< orphan*/  TEST_int_gt (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_int_le (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ptr (unsigned char*) ; 
 int /*<<< orphan*/  TEST_ptr_null (unsigned char*) ; 
 int /*<<< orphan*/  TEST_true (scalar_t__) ; 
 scalar_t__ called_encrypt ; 
 unsigned char* get_test_pkey () ; 
 int /*<<< orphan*/  test_encrypt ; 
 int /*<<< orphan*/  test_pkey_meths ; 
 unsigned char* test_rsa ; 

__attribute__((used)) static int test_redirect(void)
{
    const unsigned char pt[] = "Hello World\n";
    unsigned char *tmp = NULL;
    size_t len;
    EVP_PKEY_CTX *ctx = NULL;
    ENGINE *e = NULL;
    EVP_PKEY *pkey = NULL;

    int to_return = 0;

    if (!TEST_ptr(pkey = get_test_pkey()))
        goto err;

    len = EVP_PKEY_size(pkey);
    if (!TEST_ptr(tmp = OPENSSL_malloc(len)))
        goto err;

    if (!TEST_ptr(ctx = EVP_PKEY_CTX_new(pkey, NULL)))
        goto err;
    TEST_info("EVP_PKEY_encrypt test: no redirection");
    /* Encrypt some data: should succeed but not be redirected */
    if (!TEST_int_gt(EVP_PKEY_encrypt_init(ctx), 0)
            || !TEST_int_gt(EVP_PKEY_encrypt(ctx, tmp, &len, pt, sizeof(pt)), 0)
            || !TEST_false(called_encrypt))
        goto err;
    EVP_PKEY_CTX_free(ctx);
    ctx = NULL;

    /* Create a test ENGINE */
    if (!TEST_ptr(e = ENGINE_new())
            || !TEST_true(ENGINE_set_id(e, "Test redirect engine"))
            || !TEST_true(ENGINE_set_name(e, "Test redirect engine")))
        goto err;

    /*
     * Try to create a context for this engine and test key.
     * Try setting test key engine. Both should fail because the
     * engine has no public key methods.
     */
    if (!TEST_ptr_null(ctx = EVP_PKEY_CTX_new(pkey, e))
            || !TEST_int_le(EVP_PKEY_set1_engine(pkey, e), 0))
        goto err;

    /* Setup an empty test EVP_PKEY_METHOD and set callback to return it */
    if (!TEST_ptr(test_rsa = EVP_PKEY_meth_new(EVP_PKEY_RSA, 0)))
        goto err;
    ENGINE_set_pkey_meths(e, test_pkey_meths);

    /* Getting a context for test ENGINE should now succeed */
    if (!TEST_ptr(ctx = EVP_PKEY_CTX_new(pkey, e)))
        goto err;
    /* Encrypt should fail because operation is not supported */
    if (!TEST_int_le(EVP_PKEY_encrypt_init(ctx), 0))
        goto err;
    EVP_PKEY_CTX_free(ctx);
    ctx = NULL;

    /* Add test encrypt operation to method */
    EVP_PKEY_meth_set_encrypt(test_rsa, 0, test_encrypt);

    TEST_info("EVP_PKEY_encrypt test: redirection via EVP_PKEY_CTX_new()");
    if (!TEST_ptr(ctx = EVP_PKEY_CTX_new(pkey, e)))
        goto err;
    /* Encrypt some data: should succeed and be redirected */
    if (!TEST_int_gt(EVP_PKEY_encrypt_init(ctx), 0)
            || !TEST_int_gt(EVP_PKEY_encrypt(ctx, tmp, &len, pt, sizeof(pt)), 0)
            || !TEST_true(called_encrypt))
        goto err;

    EVP_PKEY_CTX_free(ctx);
    ctx = NULL;
    called_encrypt = 0;

    /* Create context with default engine: should not be redirected */
    if (!TEST_ptr(ctx = EVP_PKEY_CTX_new(pkey, NULL))
            || !TEST_int_gt(EVP_PKEY_encrypt_init(ctx), 0)
            || !TEST_int_gt(EVP_PKEY_encrypt(ctx, tmp, &len, pt, sizeof(pt)), 0)
            || !TEST_false(called_encrypt))
        goto err;

    EVP_PKEY_CTX_free(ctx);
    ctx = NULL;

    /* Set engine explicitly for test key */
    if (!TEST_true(EVP_PKEY_set1_engine(pkey, e)))
        goto err;

    TEST_info("EVP_PKEY_encrypt test: redirection via EVP_PKEY_set1_engine()");

    /* Create context with default engine: should be redirected now */
    if (!TEST_ptr(ctx = EVP_PKEY_CTX_new(pkey, NULL))
            || !TEST_int_gt(EVP_PKEY_encrypt_init(ctx), 0)
            || !TEST_int_gt(EVP_PKEY_encrypt(ctx, tmp, &len, pt, sizeof(pt)), 0)
            || !TEST_true(called_encrypt))
        goto err;

    to_return = 1;

 err:
    EVP_PKEY_CTX_free(ctx);
    EVP_PKEY_free(pkey);
    ENGINE_free(e);
    OPENSSL_free(tmp);
    return to_return;
}