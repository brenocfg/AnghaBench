#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_3__* cert; } ;
struct TYPE_11__ {TYPE_3__* cert; } ;
struct TYPE_10__ {TYPE_1__* pkeys; } ;
struct TYPE_9__ {int flags; char** cert_filename; int /*<<< orphan*/ * canames; TYPE_6__* ctx; TYPE_5__* ssl; } ;
struct TYPE_8__ {int /*<<< orphan*/  privatekey; } ;
typedef  TYPE_2__ SSL_CONF_CTX ;
typedef  TYPE_3__ CERT ;

/* Variables and functions */
 int SSL_CONF_FLAG_REQUIRE_PRIVATE ; 
 int /*<<< orphan*/  SSL_CTX_set0_CA_list (TYPE_6__*,int /*<<< orphan*/ *) ; 
 size_t SSL_PKEY_NUM ; 
 int /*<<< orphan*/  SSL_set0_CA_list (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_NAME_free ; 
 int /*<<< orphan*/  cmd_PrivateKey (TYPE_2__*,char const*) ; 
 int /*<<< orphan*/  sk_X509_NAME_pop_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int SSL_CONF_CTX_finish(SSL_CONF_CTX *cctx)
{
    /* See if any certificates are missing private keys */
    size_t i;
    CERT *c = NULL;
    if (cctx->ctx)
        c = cctx->ctx->cert;
    else if (cctx->ssl)
        c = cctx->ssl->cert;
    if (c && cctx->flags & SSL_CONF_FLAG_REQUIRE_PRIVATE) {
        for (i = 0; i < SSL_PKEY_NUM; i++) {
            const char *p = cctx->cert_filename[i];
            /*
             * If missing private key try to load one from certificate file
             */
            if (p && !c->pkeys[i].privatekey) {
                if (!cmd_PrivateKey(cctx, p))
                    return 0;
            }
        }
    }
    if (cctx->canames) {
        if (cctx->ssl)
            SSL_set0_CA_list(cctx->ssl, cctx->canames);
        else if (cctx->ctx)
            SSL_CTX_set0_CA_list(cctx->ctx, cctx->canames);
        else
            sk_X509_NAME_pop_free(cctx->canames, X509_NAME_free);
        cctx->canames = NULL;
    }
    return 1;
}