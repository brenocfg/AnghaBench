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
typedef  int /*<<< orphan*/  X509 ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_read_filename (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  BIO_s_file () ; 
 int /*<<< orphan*/ * PEM_read_bio_X509 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ TEST_int_gt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ *) ; 

X509 *load_pem_cert(const char *file)
{
    X509 *cert = NULL;
    BIO *bio = NULL;

    if (!TEST_ptr(bio = BIO_new(BIO_s_file())))
        return NULL;
    if (TEST_int_gt(BIO_read_filename(bio, file), 0))
        (void)TEST_ptr(cert = PEM_read_bio_X509(bio, NULL, NULL, NULL));

    BIO_free(bio);
    return cert;
}