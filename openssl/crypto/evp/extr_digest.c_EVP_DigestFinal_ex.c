#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int (* dfinal ) (int /*<<< orphan*/ ,unsigned char*,size_t*,size_t) ;int (* final ) (TYPE_1__*,unsigned char*) ;int /*<<< orphan*/  ctx_size; int /*<<< orphan*/  (* cleanup ) (TYPE_1__*) ;int /*<<< orphan*/ * prov; } ;
struct TYPE_7__ {TYPE_4__* digest; int /*<<< orphan*/  md_data; int /*<<< orphan*/  provctx; } ;
typedef  TYPE_1__ EVP_MD_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_F_EVP_DIGESTFINAL_EX ; 
 size_t EVP_MAX_MD_SIZE ; 
 int /*<<< orphan*/  EVP_MD_CTX_FLAG_CLEANED ; 
 int /*<<< orphan*/  EVP_MD_CTX_set_flags (TYPE_1__*,int /*<<< orphan*/ ) ; 
 size_t EVP_MD_size (TYPE_4__*) ; 
 int /*<<< orphan*/  EVP_R_FINAL_ERROR ; 
 int /*<<< orphan*/  EVPerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_assert (int) ; 
 int /*<<< orphan*/  OPENSSL_cleanse (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t UINT_MAX ; 
 int stub1 (int /*<<< orphan*/ ,unsigned char*,size_t*,size_t) ; 
 int stub2 (TYPE_1__*,unsigned char*) ; 
 int /*<<< orphan*/  stub3 (TYPE_1__*) ; 

int EVP_DigestFinal_ex(EVP_MD_CTX *ctx, unsigned char *md, unsigned int *isize)
{
    int ret;
    size_t size = 0;
    size_t mdsize = EVP_MD_size(ctx->digest);

    if (ctx->digest == NULL || ctx->digest->prov == NULL)
        goto legacy;

    if (ctx->digest->dfinal == NULL) {
        EVPerr(EVP_F_EVP_DIGESTFINAL_EX, EVP_R_FINAL_ERROR);
        return 0;
    }

    ret = ctx->digest->dfinal(ctx->provctx, md, &size, mdsize);

    if (isize != NULL) {
        if (size <= UINT_MAX) {
            *isize = (int)size;
        } else {
            EVPerr(EVP_F_EVP_DIGESTFINAL_EX, EVP_R_FINAL_ERROR);
            ret = 0;
        }
    }

    return ret;

    /* TODO(3.0): Remove legacy code below */
 legacy:
    OPENSSL_assert(mdsize <= EVP_MAX_MD_SIZE);
    ret = ctx->digest->final(ctx, md);
    if (isize != NULL)
        *isize = mdsize;
    if (ctx->digest->cleanup) {
        ctx->digest->cleanup(ctx);
        EVP_MD_CTX_set_flags(ctx, EVP_MD_CTX_FLAG_CLEANED);
    }
    OPENSSL_cleanse(ctx->md_data, ctx->digest->ctx_size);
    return ret;
}