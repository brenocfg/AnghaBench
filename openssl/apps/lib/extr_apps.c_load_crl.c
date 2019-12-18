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
typedef  int /*<<< orphan*/  X509_CRL ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ERR_print_errors (int /*<<< orphan*/ ) ; 
 int FORMAT_ASN1 ; 
 int FORMAT_HTTP ; 
 int FORMAT_PEM ; 
 int /*<<< orphan*/ * PEM_read_bio_X509_CRL (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bio_err ; 
 int /*<<< orphan*/ * bio_open_default (char const*,char,int) ; 
 int /*<<< orphan*/ * d2i_X509_CRL_bio (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  load_cert_crl_http (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 

X509_CRL *load_crl(const char *infile, int format)
{
    X509_CRL *x = NULL;
    BIO *in = NULL;

    if (format == FORMAT_HTTP) {
#if !defined(OPENSSL_NO_OCSP) && !defined(OPENSSL_NO_SOCK)
        load_cert_crl_http(infile, NULL, &x);
#endif
        return x;
    }

    in = bio_open_default(infile, 'r', format);
    if (in == NULL)
        goto end;
    if (format == FORMAT_ASN1) {
        x = d2i_X509_CRL_bio(in, NULL);
    } else if (format == FORMAT_PEM) {
        x = PEM_read_bio_X509_CRL(in, NULL, NULL, NULL);
    } else {
        BIO_printf(bio_err, "bad input format specified for input crl\n");
        goto end;
    }
    if (x == NULL) {
        BIO_printf(bio_err, "unable to load CRL\n");
        ERR_print_errors(bio_err);
        goto end;
    }

 end:
    BIO_free(in);
    return x;
}