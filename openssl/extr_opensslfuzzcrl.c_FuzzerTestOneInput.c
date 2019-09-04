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
typedef  int /*<<< orphan*/  X509_CRL ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_s_null () ; 
 int /*<<< orphan*/  ERR_clear_error () ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 int /*<<< orphan*/  X509_CRL_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_CRL_print (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * d2i_X509_CRL (int /*<<< orphan*/ *,unsigned char const**,size_t) ; 
 int /*<<< orphan*/  i2d_X509_CRL (int /*<<< orphan*/ *,unsigned char**) ; 

int FuzzerTestOneInput(const uint8_t *buf, size_t len)
{
    const unsigned char *p = buf;
    unsigned char *der = NULL;

    X509_CRL *crl = d2i_X509_CRL(NULL, &p, len);
    if (crl != NULL) {
        BIO *bio = BIO_new(BIO_s_null());
        X509_CRL_print(bio, crl);
        BIO_free(bio);

        i2d_X509_CRL(crl, &der);
        OPENSSL_free(der);

        X509_CRL_free(crl);
    }
    ERR_clear_error();

    return 0;
}