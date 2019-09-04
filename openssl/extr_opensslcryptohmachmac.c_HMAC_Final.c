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
struct TYPE_3__ {int /*<<< orphan*/  md_ctx; int /*<<< orphan*/  o_ctx; int /*<<< orphan*/  md; } ;
typedef  TYPE_1__ HMAC_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_DigestFinal_ex (int /*<<< orphan*/ ,unsigned char*,unsigned int*) ; 
 int /*<<< orphan*/  EVP_DigestUpdate (int /*<<< orphan*/ ,unsigned char*,unsigned int) ; 
 int EVP_MAX_MD_SIZE ; 
 int /*<<< orphan*/  EVP_MD_CTX_copy_ex (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int HMAC_Final(HMAC_CTX *ctx, unsigned char *md, unsigned int *len)
{
    unsigned int i;
    unsigned char buf[EVP_MAX_MD_SIZE];

    if (!ctx->md)
        goto err;

    if (!EVP_DigestFinal_ex(ctx->md_ctx, buf, &i))
        goto err;
    if (!EVP_MD_CTX_copy_ex(ctx->md_ctx, ctx->o_ctx))
        goto err;
    if (!EVP_DigestUpdate(ctx->md_ctx, buf, i))
        goto err;
    if (!EVP_DigestFinal_ex(ctx->md_ctx, md, len))
        goto err;
    return 1;
 err:
    return 0;
}