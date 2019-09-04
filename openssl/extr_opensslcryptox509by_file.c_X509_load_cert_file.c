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
struct TYPE_3__ {int /*<<< orphan*/  store_ctx; } ;
typedef  TYPE_1__ X509_LOOKUP ;
typedef  int /*<<< orphan*/  X509 ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_new (int /*<<< orphan*/ ) ; 
 scalar_t__ BIO_read_filename (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  BIO_s_file () ; 
 scalar_t__ ERR_GET_REASON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_ASN1_LIB ; 
 int /*<<< orphan*/  ERR_R_PEM_LIB ; 
 int /*<<< orphan*/  ERR_R_SYS_LIB ; 
 int /*<<< orphan*/  ERR_clear_error () ; 
 int /*<<< orphan*/  ERR_peek_last_error () ; 
 scalar_t__ PEM_R_NO_START_LINE ; 
 int /*<<< orphan*/ * PEM_read_bio_X509_AUX (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int X509_FILETYPE_ASN1 ; 
 int X509_FILETYPE_PEM ; 
 int /*<<< orphan*/  X509_F_X509_LOAD_CERT_FILE ; 
 int /*<<< orphan*/  X509_R_BAD_X509_FILETYPE ; 
 int /*<<< orphan*/  X509_R_NO_CERTIFICATE_FOUND ; 
 int X509_STORE_add_cert (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * d2i_X509_bio (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int X509_load_cert_file(X509_LOOKUP *ctx, const char *file, int type)
{
    int ret = 0;
    BIO *in = NULL;
    int i, count = 0;
    X509 *x = NULL;

    in = BIO_new(BIO_s_file());

    if ((in == NULL) || (BIO_read_filename(in, file) <= 0)) {
        X509err(X509_F_X509_LOAD_CERT_FILE, ERR_R_SYS_LIB);
        goto err;
    }

    if (type == X509_FILETYPE_PEM) {
        for (;;) {
            x = PEM_read_bio_X509_AUX(in, NULL, NULL, "");
            if (x == NULL) {
                if ((ERR_GET_REASON(ERR_peek_last_error()) ==
                     PEM_R_NO_START_LINE) && (count > 0)) {
                    ERR_clear_error();
                    break;
                } else {
                    X509err(X509_F_X509_LOAD_CERT_FILE, ERR_R_PEM_LIB);
                    goto err;
                }
            }
            i = X509_STORE_add_cert(ctx->store_ctx, x);
            if (!i)
                goto err;
            count++;
            X509_free(x);
            x = NULL;
        }
        ret = count;
    } else if (type == X509_FILETYPE_ASN1) {
        x = d2i_X509_bio(in, NULL);
        if (x == NULL) {
            X509err(X509_F_X509_LOAD_CERT_FILE, ERR_R_ASN1_LIB);
            goto err;
        }
        i = X509_STORE_add_cert(ctx->store_ctx, x);
        if (!i)
            goto err;
        ret = i;
    } else {
        X509err(X509_F_X509_LOAD_CERT_FILE, X509_R_BAD_X509_FILETYPE);
        goto err;
    }
    if (ret == 0)
        X509err(X509_F_X509_LOAD_CERT_FILE, X509_R_NO_CERTIFICATE_FOUND);
 err:
    X509_free(x);
    BIO_free(in);
    return ret;
}