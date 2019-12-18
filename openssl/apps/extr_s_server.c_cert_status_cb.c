#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ verbose; int /*<<< orphan*/ * respin; } ;
typedef  TYPE_1__ tlsextstatusctx ;
typedef  int /*<<< orphan*/  SSL ;
typedef  int /*<<< orphan*/  OCSP_RESPONSE ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_puts (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ERR_print_errors (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FORMAT_ASN1 ; 
 int /*<<< orphan*/  OCSP_RESPONSE_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OCSP_RESPONSE_print (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int SSL_TLSEXT_ERR_ALERT_FATAL ; 
 int SSL_TLSEXT_ERR_OK ; 
 int /*<<< orphan*/  SSL_set_tlsext_status_ocsp_resp (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  bio_err ; 
 int /*<<< orphan*/ * bio_open_default (int /*<<< orphan*/ *,char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * d2i_OCSP_RESPONSE_bio (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int get_ocsp_resp_from_responder (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ **) ; 
 int i2d_OCSP_RESPONSE (int /*<<< orphan*/ *,unsigned char**) ; 

__attribute__((used)) static int cert_status_cb(SSL *s, void *arg)
{
    tlsextstatusctx *srctx = arg;
    OCSP_RESPONSE *resp = NULL;
    unsigned char *rspder = NULL;
    int rspderlen;
    int ret = SSL_TLSEXT_ERR_ALERT_FATAL;

    if (srctx->verbose)
        BIO_puts(bio_err, "cert_status: callback called\n");

    if (srctx->respin != NULL) {
        BIO *derbio = bio_open_default(srctx->respin, 'r', FORMAT_ASN1);
        if (derbio == NULL) {
            BIO_puts(bio_err, "cert_status: Cannot open OCSP response file\n");
            goto err;
        }
        resp = d2i_OCSP_RESPONSE_bio(derbio, NULL);
        BIO_free(derbio);
        if (resp == NULL) {
            BIO_puts(bio_err, "cert_status: Error reading OCSP response\n");
            goto err;
        }
    } else {
        ret = get_ocsp_resp_from_responder(s, srctx, &resp);
        if (ret != SSL_TLSEXT_ERR_OK)
            goto err;
    }

    rspderlen = i2d_OCSP_RESPONSE(resp, &rspder);
    if (rspderlen <= 0)
        goto err;

    SSL_set_tlsext_status_ocsp_resp(s, rspder, rspderlen);
    if (srctx->verbose) {
        BIO_puts(bio_err, "cert_status: ocsp response sent:\n");
        OCSP_RESPONSE_print(bio_err, resp, 2);
    }

    ret = SSL_TLSEXT_ERR_OK;

 err:
    if (ret != SSL_TLSEXT_ERR_OK)
        ERR_print_errors(bio_err);

    OCSP_RESPONSE_free(resp);

    return ret;
}