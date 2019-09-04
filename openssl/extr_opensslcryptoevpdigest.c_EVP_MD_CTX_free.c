#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * reqdigest; TYPE_1__* digest; int /*<<< orphan*/ * fetched_digest; } ;
struct TYPE_6__ {int /*<<< orphan*/ * prov; } ;
typedef  TYPE_2__ EVP_MD_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_MD_CTX_reset (TYPE_2__*) ; 
 int /*<<< orphan*/  EVP_MD_meth_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_2__*) ; 

void EVP_MD_CTX_free(EVP_MD_CTX *ctx)
{
    if (ctx == NULL)
        return;

    if (ctx->digest == NULL || ctx->digest->prov == NULL)
        goto legacy;

    EVP_MD_CTX_reset(ctx);

    EVP_MD_meth_free(ctx->fetched_digest);
    ctx->fetched_digest = NULL;
    ctx->digest = NULL;
    ctx->reqdigest = NULL;

    OPENSSL_free(ctx);
    return;

    /* TODO(3.0): Remove legacy code below */
 legacy:
    EVP_MD_CTX_reset(ctx);
    OPENSSL_free(ctx);
}