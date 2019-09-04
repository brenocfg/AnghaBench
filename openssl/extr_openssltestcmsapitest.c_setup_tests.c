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
typedef  char BIO ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_TEST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_free (char*) ; 
 char* BIO_new_file (char*,char*) ; 
 int /*<<< orphan*/  PEM_read_bio_PrivateKey (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PEM_read_bio_X509 (char*,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_ptr (char*) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cert ; 
 int /*<<< orphan*/  privkey ; 
 int /*<<< orphan*/  test_encrypt_decrypt ; 
 char* test_get_argument (int) ; 

int setup_tests(void)
{
    char *certin = NULL, *privkeyin = NULL;
    BIO *certbio = NULL, *privkeybio = NULL;

    if (!TEST_ptr(certin = test_get_argument(0))
            || !TEST_ptr(privkeyin = test_get_argument(1)))
        return 0;

    certbio = BIO_new_file(certin, "r");
    if (!TEST_ptr(certbio))
        return 0;
    if (!TEST_true(PEM_read_bio_X509(certbio, &cert, NULL, NULL))) {
        BIO_free(certbio);
        return 0;
    }
    BIO_free(certbio);

    privkeybio = BIO_new_file(privkeyin, "r");
    if (!TEST_ptr(privkeybio)) {
        X509_free(cert);
        cert = NULL;
        return 0;
    }
    if (!TEST_true(PEM_read_bio_PrivateKey(privkeybio, &privkey, NULL, NULL))) {
        BIO_free(privkeybio);
        X509_free(cert);
        cert = NULL;
        return 0;
    }
    BIO_free(privkeybio);

    ADD_TEST(test_encrypt_decrypt);

    return 1;
}