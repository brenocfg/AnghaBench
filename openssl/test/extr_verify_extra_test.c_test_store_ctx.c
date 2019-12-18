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
typedef  int /*<<< orphan*/  X509_STORE_CTX ;
typedef  int /*<<< orphan*/  X509 ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_new_file (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * PEM_read_bio_X509 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_STORE_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_STORE_CTX_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * X509_STORE_CTX_new () ; 
 int /*<<< orphan*/  X509_free (int /*<<< orphan*/ *) ; 
 int X509_verify_cert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bad_f ; 

__attribute__((used)) static int test_store_ctx(void)
{
    X509_STORE_CTX *sctx = NULL;
    X509 *x = NULL;
    BIO *bio = NULL;
    int testresult = 0, ret;

    bio = BIO_new_file(bad_f, "r");
    if (bio == NULL)
        goto err;

    x = PEM_read_bio_X509(bio, NULL, 0, NULL);
    if (x == NULL)
        goto err;

    sctx = X509_STORE_CTX_new();
    if (sctx == NULL)
        goto err;

    if (!X509_STORE_CTX_init(sctx, NULL, x, NULL))
        goto err;

    /* Verifying a cert where we have no trusted certs should fail */
    ret = X509_verify_cert(sctx);

    if (ret == 0) {
        /* This is the result we were expecting: Test passed */
        testresult = 1;
    }

 err:
    X509_STORE_CTX_free(sctx);
    X509_free(x);
    BIO_free(bio);
    return testresult;
}