#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int (* update ) (TYPE_2__*,void const*,size_t) ;int /*<<< orphan*/  provctx; TYPE_1__* digest; } ;
struct TYPE_5__ {int (* dupdate ) (int /*<<< orphan*/ ,void const*,size_t) ;int /*<<< orphan*/ * prov; } ;
typedef  TYPE_2__ EVP_MD_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_F_EVP_DIGESTUPDATE ; 
 int /*<<< orphan*/  EVP_R_UPDATE_ERROR ; 
 int /*<<< orphan*/  EVPerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ ,void const*,size_t) ; 
 int stub2 (TYPE_2__*,void const*,size_t) ; 

int EVP_DigestUpdate(EVP_MD_CTX *ctx, const void *data, size_t count)
{
    if (count == 0)
        return 1;

    if (ctx->digest == NULL || ctx->digest->prov == NULL)
        goto legacy;

    if (ctx->digest->dupdate == NULL) {
        EVPerr(EVP_F_EVP_DIGESTUPDATE, EVP_R_UPDATE_ERROR);
        return 0;
    }
    return ctx->digest->dupdate(ctx->provctx, data, count);

    /* TODO(3.0): Remove legacy code below */
 legacy:
    return ctx->update(ctx, data, count);
}