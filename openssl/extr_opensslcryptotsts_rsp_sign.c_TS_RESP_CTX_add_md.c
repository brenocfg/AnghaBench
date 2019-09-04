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
struct TYPE_3__ {int /*<<< orphan*/ * mds; } ;
typedef  TYPE_1__ TS_RESP_CTX ;
typedef  int /*<<< orphan*/  EVP_MD ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  TS_F_TS_RESP_CTX_ADD_MD ; 
 int /*<<< orphan*/  TSerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * sk_EVP_MD_new_null () ; 
 int /*<<< orphan*/  sk_EVP_MD_push (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

int TS_RESP_CTX_add_md(TS_RESP_CTX *ctx, const EVP_MD *md)
{
    if (ctx->mds == NULL
        && (ctx->mds = sk_EVP_MD_new_null()) == NULL)
        goto err;
    if (!sk_EVP_MD_push(ctx->mds, md))
        goto err;

    return 1;
 err:
    TSerr(TS_F_TS_RESP_CTX_ADD_MD, ERR_R_MALLOC_FAILURE);
    return 0;
}