#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  canames; struct TYPE_4__* prefix; struct TYPE_4__** cert_filename; } ;
typedef  TYPE_1__ SSL_CONF_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 
 size_t SSL_PKEY_NUM ; 
 int /*<<< orphan*/  X509_NAME_free ; 
 int /*<<< orphan*/  sk_X509_NAME_pop_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void SSL_CONF_CTX_free(SSL_CONF_CTX *cctx)
{
    if (cctx) {
        size_t i;
        for (i = 0; i < SSL_PKEY_NUM; i++)
            OPENSSL_free(cctx->cert_filename[i]);
        OPENSSL_free(cctx->prefix);
        sk_X509_NAME_pop_free(cctx->canames, X509_NAME_free);
        OPENSSL_free(cctx);
    }
}