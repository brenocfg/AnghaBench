#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {void* error; TYPE_1__* param; int /*<<< orphan*/  chain; scalar_t__ parent; } ;
typedef  TYPE_2__ X509_STORE_CTX ;
struct TYPE_13__ {int ex_flags; int ex_pathlen; int ex_pcpathlen; } ;
typedef  TYPE_3__ X509 ;
struct TYPE_11__ {int flags; int purpose; } ;

/* Variables and functions */
 int EXFLAG_CRITICAL ; 
 int EXFLAG_PROXY ; 
 int EXFLAG_SI ; 
 int X509_PURPOSE_CRL_SIGN ; 
 void* X509_V_ERR_INVALID_CA ; 
 void* X509_V_ERR_INVALID_NON_CA ; 
 int /*<<< orphan*/  X509_V_ERR_PATH_LENGTH_EXCEEDED ; 
 int /*<<< orphan*/  X509_V_ERR_PROXY_CERTIFICATES_NOT_ALLOWED ; 
 int /*<<< orphan*/  X509_V_ERR_PROXY_PATH_LENGTH_EXCEEDED ; 
 int /*<<< orphan*/  X509_V_ERR_UNHANDLED_CRITICAL_EXTENSION ; 
 int X509_V_FLAG_ALLOW_PROXY_CERTS ; 
 int X509_V_FLAG_IGNORE_CRITICAL ; 
 int X509_V_FLAG_X509_STRICT ; 
 int /*<<< orphan*/  X509_V_OK ; 
 int X509_check_ca (TYPE_3__*) ; 
 int /*<<< orphan*/  check_purpose (TYPE_2__*,TYPE_3__*,int,int,int) ; 
 int sk_X509_num (int /*<<< orphan*/ ) ; 
 TYPE_3__* sk_X509_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  verify_cb_cert (TYPE_2__*,TYPE_3__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int check_chain_extensions(X509_STORE_CTX *ctx)
{
    int i, must_be_ca, plen = 0;
    X509 *x;
    int proxy_path_length = 0;
    int purpose;
    int allow_proxy_certs;
    int num = sk_X509_num(ctx->chain);

    /*-
     *  must_be_ca can have 1 of 3 values:
     * -1: we accept both CA and non-CA certificates, to allow direct
     *     use of self-signed certificates (which are marked as CA).
     * 0:  we only accept non-CA certificates.  This is currently not
     *     used, but the possibility is present for future extensions.
     * 1:  we only accept CA certificates.  This is currently used for
     *     all certificates in the chain except the leaf certificate.
     */
    must_be_ca = -1;

    /* CRL path validation */
    if (ctx->parent) {
        allow_proxy_certs = 0;
        purpose = X509_PURPOSE_CRL_SIGN;
    } else {
        allow_proxy_certs =
            ! !(ctx->param->flags & X509_V_FLAG_ALLOW_PROXY_CERTS);
        purpose = ctx->param->purpose;
    }

    for (i = 0; i < num; i++) {
        int ret;
        x = sk_X509_value(ctx->chain, i);
        if (!(ctx->param->flags & X509_V_FLAG_IGNORE_CRITICAL)
            && (x->ex_flags & EXFLAG_CRITICAL)) {
            if (!verify_cb_cert(ctx, x, i,
                                X509_V_ERR_UNHANDLED_CRITICAL_EXTENSION))
                return 0;
        }
        if (!allow_proxy_certs && (x->ex_flags & EXFLAG_PROXY)) {
            if (!verify_cb_cert(ctx, x, i,
                                X509_V_ERR_PROXY_CERTIFICATES_NOT_ALLOWED))
                return 0;
        }
        ret = X509_check_ca(x);
        switch (must_be_ca) {
        case -1:
            if ((ctx->param->flags & X509_V_FLAG_X509_STRICT)
                && (ret != 1) && (ret != 0)) {
                ret = 0;
                ctx->error = X509_V_ERR_INVALID_CA;
            } else
                ret = 1;
            break;
        case 0:
            if (ret != 0) {
                ret = 0;
                ctx->error = X509_V_ERR_INVALID_NON_CA;
            } else
                ret = 1;
            break;
        default:
            /* X509_V_FLAG_X509_STRICT is implicit for intermediate CAs */
            if ((ret == 0)
                || ((i + 1 < num || ctx->param->flags & X509_V_FLAG_X509_STRICT)
                    && (ret != 1))) {
                ret = 0;
                ctx->error = X509_V_ERR_INVALID_CA;
            } else
                ret = 1;
            break;
        }
        if (ret == 0 && !verify_cb_cert(ctx, x, i, X509_V_OK))
            return 0;
        /* check_purpose() makes the callback as needed */
        if (purpose > 0 && !check_purpose(ctx, x, purpose, i, must_be_ca))
            return 0;
        /* Check pathlen */
        if ((i > 1) && (x->ex_pathlen != -1)
            && (plen > (x->ex_pathlen + proxy_path_length))) {
            if (!verify_cb_cert(ctx, x, i, X509_V_ERR_PATH_LENGTH_EXCEEDED))
                return 0;
        }
        /* Increment path length if not a self issued intermediate CA */
        if (i > 0 && (x->ex_flags & EXFLAG_SI) == 0)
            plen++;
        /*
         * If this certificate is a proxy certificate, the next certificate
         * must be another proxy certificate or a EE certificate.  If not,
         * the next certificate must be a CA certificate.
         */
        if (x->ex_flags & EXFLAG_PROXY) {
            /*
             * RFC3820, 4.1.3 (b)(1) stipulates that if pCPathLengthConstraint
             * is less than max_path_length, the former should be copied to
             * the latter, and 4.1.4 (a) stipulates that max_path_length
             * should be verified to be larger than zero and decrement it.
             *
             * Because we're checking the certs in the reverse order, we start
             * with verifying that proxy_path_length isn't larger than pcPLC,
             * and copy the latter to the former if it is, and finally,
             * increment proxy_path_length.
             */
            if (x->ex_pcpathlen != -1) {
                if (proxy_path_length > x->ex_pcpathlen) {
                    if (!verify_cb_cert(ctx, x, i,
                                        X509_V_ERR_PROXY_PATH_LENGTH_EXCEEDED))
                        return 0;
                }
                proxy_path_length = x->ex_pcpathlen;
            }
            proxy_path_length++;
            must_be_ca = 0;
        } else
            must_be_ca = 1;
    }
    return 1;
}