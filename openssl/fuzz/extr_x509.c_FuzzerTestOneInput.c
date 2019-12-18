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
typedef  unsigned char uint8_t ;
typedef  int /*<<< orphan*/  X509 ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_s_null () ; 
 int /*<<< orphan*/  ERR_clear_error () ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 int /*<<< orphan*/  X509_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_print (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * d2i_X509 (int /*<<< orphan*/ *,unsigned char const**,size_t) ; 
 int /*<<< orphan*/  i2d_X509 (int /*<<< orphan*/ *,unsigned char**) ; 

int FuzzerTestOneInput(const uint8_t *buf, size_t len)
{
    const unsigned char *p = buf;
    unsigned char *der = NULL;

    X509 *x509 = d2i_X509(NULL, &p, len);
    if (x509 != NULL) {
        BIO *bio = BIO_new(BIO_s_null());
        /* This will load and print the public key as well as extensions */
        X509_print(bio, x509);
        BIO_free(bio);

        i2d_X509(x509, &der);
        OPENSSL_free(der);

        X509_free(x509);
    }
    ERR_clear_error();
    return 0;
}