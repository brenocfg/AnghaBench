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
typedef  int /*<<< orphan*/  X509_REQ ;
typedef  int /*<<< orphan*/  X509 ;
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_new_file (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  EVP_PKEY_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PEM_read_bio_PrivateKey (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PEM_read_bio_X509 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PEM_read_bio_X509_REQ (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_error (char*,...) ; 
 int /*<<< orphan*/  TEST_int_eq (int,int) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ *) ; 
 int X509_REQ_check_private_key (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_REQ_free (int /*<<< orphan*/ *) ; 
 int X509_check_private_key (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c ; 
 int /*<<< orphan*/  e ; 
 int /*<<< orphan*/  k ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  t ; 

__attribute__((used)) static int test_x509_check_cert_pkey(void)
{
    BIO *bio = NULL;
    X509 *x509 = NULL;
    X509_REQ *x509_req = NULL;
    EVP_PKEY *pkey = NULL;
    int ret = 0, type = 0, expected = 0, result = 0;

    /*
     * we check them first thus if fails we don't need to do
     * those PEM parsing operations.
     */
    if (strcmp(t, "cert") == 0) {
        type = 1;
    } else if (strcmp(t, "req") == 0) {
        type = 2;
    } else {
        TEST_error("invalid 'type'");
        goto failed;
    }

    if (strcmp(e, "ok") == 0) {
        expected = 1;
    } else if (strcmp(e, "failed") == 0) {
        expected = 0;
    } else {
        TEST_error("invalid 'expected'");
        goto failed;
    }

    /* process private key */
    if (!TEST_ptr(bio = BIO_new_file(k, "r")))
        goto failed;

    if (!TEST_ptr(pkey = PEM_read_bio_PrivateKey(bio, NULL, NULL, NULL)))
        goto failed;

    BIO_free(bio);

    /* process cert or cert request, use the same local var */
    if (!TEST_ptr(bio = BIO_new_file(c, "r")))
        goto failed;

    switch (type) {
    case 1:
        x509 = PEM_read_bio_X509(bio, NULL, NULL, NULL);
        if (x509 == NULL) {
            TEST_error("read PEM x509 failed");
            goto failed;
        }

        result = X509_check_private_key(x509, pkey);
        break;
    case 2:
        x509_req = PEM_read_bio_X509_REQ(bio, NULL, NULL, NULL);
        if (x509_req == NULL) {
            TEST_error("read PEM x509 req failed");
            goto failed;
        }

        result = X509_REQ_check_private_key(x509_req, pkey);
        break;
    default:
        /* should never be here */
        break;
    }

    if (!TEST_int_eq(result, expected)) {
        TEST_error("check private key: expected: %d, got: %d", expected, result);
        goto failed;
    }

    ret = 1;
failed:
    BIO_free(bio);
    X509_free(x509);
    X509_REQ_free(x509_req);
    EVP_PKEY_free(pkey);
    return ret;
}