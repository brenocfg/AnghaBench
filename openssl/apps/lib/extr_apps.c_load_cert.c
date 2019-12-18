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
typedef  int /*<<< orphan*/  pem_password_cb ;
typedef  int /*<<< orphan*/  X509 ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ERR_print_errors (int /*<<< orphan*/ ) ; 
 int FORMAT_ASN1 ; 
 int FORMAT_HTTP ; 
 int FORMAT_PEM ; 
 int FORMAT_PKCS12 ; 
 int /*<<< orphan*/ * PEM_read_bio_X509_AUX (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bio_err ; 
 int /*<<< orphan*/ * bio_open_default (char const*,char,int) ; 
 int /*<<< orphan*/ * d2i_X509_bio (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dup_bio_in (int) ; 
 int /*<<< orphan*/  load_cert_crl_http (char const*,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  load_pkcs12 (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 scalar_t__ password_callback ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  unbuffer (int /*<<< orphan*/ ) ; 

X509 *load_cert(const char *file, int format, const char *cert_descrip)
{
    X509 *x = NULL;
    BIO *cert;

    if (format == FORMAT_HTTP) {
#if !defined(OPENSSL_NO_OCSP) && !defined(OPENSSL_NO_SOCK)
        load_cert_crl_http(file, &x, NULL);
#endif
        return x;
    }

    if (file == NULL) {
        unbuffer(stdin);
        cert = dup_bio_in(format);
    } else {
        cert = bio_open_default(file, 'r', format);
    }
    if (cert == NULL)
        goto end;

    if (format == FORMAT_ASN1) {
        x = d2i_X509_bio(cert, NULL);
    } else if (format == FORMAT_PEM) {
        x = PEM_read_bio_X509_AUX(cert, NULL,
                                  (pem_password_cb *)password_callback, NULL);
    } else if (format == FORMAT_PKCS12) {
        if (!load_pkcs12(cert, cert_descrip, NULL, NULL, NULL, &x, NULL))
            goto end;
    } else {
        BIO_printf(bio_err, "bad input format specified for %s\n", cert_descrip);
        goto end;
    }
 end:
    if (x == NULL) {
        BIO_printf(bio_err, "unable to load certificate\n");
        ERR_print_errors(bio_err);
    }
    BIO_free(cert);
    return x;
}