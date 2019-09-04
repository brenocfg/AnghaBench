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
typedef  int /*<<< orphan*/  X509 ;
typedef  int /*<<< orphan*/  OCSP_REQ_CTX ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_free_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_new_connect (char*) ; 
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*,char*,char const*) ; 
 int /*<<< orphan*/  BIO_puts (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  BIO_set_conn_port (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ERR_print_errors (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OCSP_REQ_CTX_add1_header (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  OCSP_REQ_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OCSP_REQ_CTX_http (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/ * OCSP_REQ_CTX_new (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  OCSP_parse_url (char const*,char**,char**,char**,int*) ; 
 int /*<<< orphan*/  OPENSSL_free (char*) ; 
 int X509_CRL_http_nbio (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int X509_http_nbio (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  bio_err ; 

__attribute__((used)) static int load_cert_crl_http(const char *url, X509 **pcert, X509_CRL **pcrl)
{
    char *host = NULL, *port = NULL, *path = NULL;
    BIO *bio = NULL;
    OCSP_REQ_CTX *rctx = NULL;
    int use_ssl, rv = 0;
    if (!OCSP_parse_url(url, &host, &port, &path, &use_ssl))
        goto err;
    if (use_ssl) {
        BIO_puts(bio_err, "https not supported\n");
        goto err;
    }
    bio = BIO_new_connect(host);
    if (!bio || !BIO_set_conn_port(bio, port))
        goto err;
    rctx = OCSP_REQ_CTX_new(bio, 1024);
    if (rctx == NULL)
        goto err;
    if (!OCSP_REQ_CTX_http(rctx, "GET", path))
        goto err;
    if (!OCSP_REQ_CTX_add1_header(rctx, "Host", host))
        goto err;
    if (pcert) {
        do {
            rv = X509_http_nbio(rctx, pcert);
        } while (rv == -1);
    } else {
        do {
            rv = X509_CRL_http_nbio(rctx, pcrl);
        } while (rv == -1);
    }

 err:
    OPENSSL_free(host);
    OPENSSL_free(path);
    OPENSSL_free(port);
    BIO_free_all(bio);
    OCSP_REQ_CTX_free(rctx);
    if (rv != 1) {
        BIO_printf(bio_err, "Error loading %s from %s\n",
                   pcert ? "certificate" : "CRL", url);
        ERR_print_errors(bio_err);
    }
    return rv;
}