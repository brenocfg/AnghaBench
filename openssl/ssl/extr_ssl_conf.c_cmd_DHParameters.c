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
struct TYPE_3__ {scalar_t__ ssl; scalar_t__ ctx; } ;
typedef  TYPE_1__ SSL_CONF_CTX ;
typedef  int /*<<< orphan*/  DH ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_new (int /*<<< orphan*/ ) ; 
 scalar_t__ BIO_read_filename (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  BIO_s_file () ; 
 int /*<<< orphan*/  DH_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PEM_read_bio_DHparams (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int SSL_CTX_set_tmp_dh (scalar_t__,int /*<<< orphan*/ *) ; 
 int SSL_set_tmp_dh (scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cmd_DHParameters(SSL_CONF_CTX *cctx, const char *value)
{
    int rv = 0;
    DH *dh = NULL;
    BIO *in = NULL;
    if (cctx->ctx || cctx->ssl) {
        in = BIO_new(BIO_s_file());
        if (in == NULL)
            goto end;
        if (BIO_read_filename(in, value) <= 0)
            goto end;
        dh = PEM_read_bio_DHparams(in, NULL, NULL, NULL);
        if (dh == NULL)
            goto end;
    } else
        return 1;
    if (cctx->ctx)
        rv = SSL_CTX_set_tmp_dh(cctx->ctx, dh);
    if (cctx->ssl)
        rv = SSL_set_tmp_dh(cctx->ssl, dh);
 end:
    DH_free(dh);
    BIO_free(in);
    return rv > 0;
}