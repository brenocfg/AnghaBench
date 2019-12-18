#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int error_depth; int /*<<< orphan*/  chain; int /*<<< orphan*/  (* verify_cb ) (int,TYPE_2__*) ;int /*<<< orphan*/ * current_cert; int /*<<< orphan*/ * current_issuer; TYPE_1__* param; scalar_t__ (* check_issued ) (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;scalar_t__ bare_ta_signed; } ;
typedef  TYPE_2__ X509_STORE_CTX ;
typedef  int /*<<< orphan*/  X509 ;
struct TYPE_8__ {int flags; } ;
typedef  int /*<<< orphan*/  EVP_PKEY ;

/* Variables and functions */
 int /*<<< orphan*/  X509_V_ERR_CERT_SIGNATURE_FAILURE ; 
 int /*<<< orphan*/  X509_V_ERR_UNABLE_TO_DECODE_ISSUER_PUBLIC_KEY ; 
 int /*<<< orphan*/  X509_V_ERR_UNABLE_TO_VERIFY_LEAF_SIGNATURE ; 
 int X509_V_FLAG_CHECK_SS_SIGNATURE ; 
 int X509_V_FLAG_PARTIAL_CHAIN ; 
 int /*<<< orphan*/ * X509_get0_pubkey (int /*<<< orphan*/ *) ; 
 scalar_t__ X509_verify (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int sk_X509_num (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * sk_X509_value (int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub1 (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int,TYPE_2__*) ; 
 int verify_cb_cert (TYPE_2__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  x509_check_cert_time (TYPE_2__*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int internal_verify(X509_STORE_CTX *ctx)
{
    int n = sk_X509_num(ctx->chain) - 1;
    X509 *xi = sk_X509_value(ctx->chain, n);
    X509 *xs;

    /*
     * With DANE-verified bare public key TA signatures, it remains only to
     * check the timestamps of the top certificate.  We report the issuer as
     * NULL, since all we have is a bare key.
     */
    if (ctx->bare_ta_signed) {
        xs = xi;
        xi = NULL;
        goto check_cert;
    }

    if (ctx->check_issued(ctx, xi, xi))
        xs = xi;
    else {
        if (ctx->param->flags & X509_V_FLAG_PARTIAL_CHAIN) {
            xs = xi;
            goto check_cert;
        }
        if (n <= 0)
            return verify_cb_cert(ctx, xi, 0,
                                  X509_V_ERR_UNABLE_TO_VERIFY_LEAF_SIGNATURE);
        n--;
        ctx->error_depth = n;
        xs = sk_X509_value(ctx->chain, n);
    }

    /*
     * Do not clear ctx->error=0, it must be "sticky", only the user's callback
     * is allowed to reset errors (at its own peril).
     */
    while (n >= 0) {
        EVP_PKEY *pkey;

        /*
         * Skip signature check for self signed certificates unless explicitly
         * asked for.  It doesn't add any security and just wastes time.  If
         * the issuer's public key is unusable, report the issuer certificate
         * and its depth (rather than the depth of the subject).
         */
        if (xs != xi || (ctx->param->flags & X509_V_FLAG_CHECK_SS_SIGNATURE)) {
            if ((pkey = X509_get0_pubkey(xi)) == NULL) {
                if (!verify_cb_cert(ctx, xi, xi != xs ? n+1 : n,
                        X509_V_ERR_UNABLE_TO_DECODE_ISSUER_PUBLIC_KEY))
                    return 0;
            } else if (X509_verify(xs, pkey) <= 0) {
                if (!verify_cb_cert(ctx, xs, n,
                                    X509_V_ERR_CERT_SIGNATURE_FAILURE))
                    return 0;
            }
        }

 check_cert:
        /* Calls verify callback as needed */
        if (!x509_check_cert_time(ctx, xs, n))
            return 0;

        /*
         * Signal success at this depth.  However, the previous error (if any)
         * is retained.
         */
        ctx->current_issuer = xi;
        ctx->current_cert = xs;
        ctx->error_depth = n;
        if (!ctx->verify_cb(1, ctx))
            return 0;

        if (--n >= 0) {
            xi = xs;
            xs = sk_X509_value(ctx->chain, n);
        }
    }
    return 1;
}