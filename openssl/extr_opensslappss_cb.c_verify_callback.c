#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  X509_STORE_CTX ;
typedef  int /*<<< orphan*/  X509 ;
struct TYPE_2__ {int depth; int error; int /*<<< orphan*/  quiet; int /*<<< orphan*/  return_error; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_TIME_print (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  BIO_puts (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  X509_NAME_print_ex (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * X509_STORE_CTX_get_current_cert (int /*<<< orphan*/ *) ; 
 int X509_STORE_CTX_get_error (int /*<<< orphan*/ *) ; 
 int X509_STORE_CTX_get_error_depth (int /*<<< orphan*/ *) ; 
 int X509_V_ERR_CERT_CHAIN_TOO_LONG ; 
#define  X509_V_ERR_CERT_HAS_EXPIRED 133 
#define  X509_V_ERR_CERT_NOT_YET_VALID 132 
#define  X509_V_ERR_ERROR_IN_CERT_NOT_AFTER_FIELD 131 
#define  X509_V_ERR_ERROR_IN_CERT_NOT_BEFORE_FIELD 130 
#define  X509_V_ERR_NO_EXPLICIT_POLICY 129 
#define  X509_V_ERR_UNABLE_TO_GET_ISSUER_CERT 128 
 int X509_V_OK ; 
 int /*<<< orphan*/  X509_get0_notAfter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_get0_notBefore (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_get_issuer_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_get_subject_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_verify_cert_error_string (int) ; 
 int /*<<< orphan*/  bio_err ; 
 int /*<<< orphan*/  get_nameopt () ; 
 int /*<<< orphan*/  policies_print (int /*<<< orphan*/ *) ; 
 TYPE_1__ verify_args ; 

int verify_callback(int ok, X509_STORE_CTX *ctx)
{
    X509 *err_cert;
    int err, depth;

    err_cert = X509_STORE_CTX_get_current_cert(ctx);
    err = X509_STORE_CTX_get_error(ctx);
    depth = X509_STORE_CTX_get_error_depth(ctx);

    if (!verify_args.quiet || !ok) {
        BIO_printf(bio_err, "depth=%d ", depth);
        if (err_cert != NULL) {
            X509_NAME_print_ex(bio_err,
                               X509_get_subject_name(err_cert),
                               0, get_nameopt());
            BIO_puts(bio_err, "\n");
        } else {
            BIO_puts(bio_err, "<no cert>\n");
        }
    }
    if (!ok) {
        BIO_printf(bio_err, "verify error:num=%d:%s\n", err,
                   X509_verify_cert_error_string(err));
        if (verify_args.depth < 0 || verify_args.depth >= depth) {
            if (!verify_args.return_error)
                ok = 1;
            verify_args.error = err;
        } else {
            ok = 0;
            verify_args.error = X509_V_ERR_CERT_CHAIN_TOO_LONG;
        }
    }
    switch (err) {
    case X509_V_ERR_UNABLE_TO_GET_ISSUER_CERT:
        BIO_puts(bio_err, "issuer= ");
        X509_NAME_print_ex(bio_err, X509_get_issuer_name(err_cert),
                           0, get_nameopt());
        BIO_puts(bio_err, "\n");
        break;
    case X509_V_ERR_CERT_NOT_YET_VALID:
    case X509_V_ERR_ERROR_IN_CERT_NOT_BEFORE_FIELD:
        BIO_printf(bio_err, "notBefore=");
        ASN1_TIME_print(bio_err, X509_get0_notBefore(err_cert));
        BIO_printf(bio_err, "\n");
        break;
    case X509_V_ERR_CERT_HAS_EXPIRED:
    case X509_V_ERR_ERROR_IN_CERT_NOT_AFTER_FIELD:
        BIO_printf(bio_err, "notAfter=");
        ASN1_TIME_print(bio_err, X509_get0_notAfter(err_cert));
        BIO_printf(bio_err, "\n");
        break;
    case X509_V_ERR_NO_EXPLICIT_POLICY:
        if (!verify_args.quiet)
            policies_print(ctx);
        break;
    }
    if (err == X509_V_OK && ok == 2 && !verify_args.quiet)
        policies_print(ctx);
    if (ok && !verify_args.quiet)
        BIO_printf(bio_err, "verify return:%d\n", ok);
    return ok;
}