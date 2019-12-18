#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_2__* digest; TYPE_1__* pctx; } ;
struct TYPE_9__ {int (* md_ctrl ) (TYPE_3__*,int,int,void*) ;int /*<<< orphan*/ * prov; } ;
struct TYPE_8__ {scalar_t__ operation; } ;
typedef  int /*<<< orphan*/  OSSL_PARAM ;
typedef  TYPE_3__ EVP_MD_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_LIB_EVP ; 
 int /*<<< orphan*/  ERR_raise (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EVP_CTRL_RET_UNSUPPORTED ; 
#define  EVP_CTRL_SSL3_MASTER_SECRET 130 
#define  EVP_MD_CTRL_MICALG 129 
#define  EVP_MD_CTRL_XOF_LEN 128 
 int EVP_MD_CTX_get_params (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int EVP_MD_CTX_set_params (TYPE_3__*,int /*<<< orphan*/ *) ; 
 scalar_t__ EVP_PKEY_OP_SIGNCTX ; 
 scalar_t__ EVP_PKEY_OP_VERIFYCTX ; 
 int /*<<< orphan*/  EVP_R_CTRL_NOT_IMPLEMENTED ; 
 int /*<<< orphan*/  EVP_R_MESSAGE_DIGEST_IS_NULL ; 
 int /*<<< orphan*/  OSSL_DIGEST_PARAM_MICALG ; 
 int /*<<< orphan*/  OSSL_DIGEST_PARAM_SSL3_MS ; 
 int /*<<< orphan*/  OSSL_DIGEST_PARAM_XOFLEN ; 
 int /*<<< orphan*/  OSSL_PARAM_END ; 
 int /*<<< orphan*/  OSSL_PARAM_construct_octet_string (int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  OSSL_PARAM_construct_size_t (int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  OSSL_PARAM_construct_utf8_string (int /*<<< orphan*/ ,void*,int) ; 
 int stub1 (TYPE_3__*,int,int,void*) ; 

int EVP_MD_CTX_ctrl(EVP_MD_CTX *ctx, int cmd, int p1, void *p2)
{
    int ret = EVP_CTRL_RET_UNSUPPORTED;
    int set_params = 1;
    size_t sz;
    OSSL_PARAM params[2] = { OSSL_PARAM_END, OSSL_PARAM_END };

    if (ctx == NULL || ctx->digest == NULL) {
        ERR_raise(ERR_LIB_EVP, EVP_R_MESSAGE_DIGEST_IS_NULL);
        return 0;
    }

    if (ctx->digest->prov == NULL
        && (ctx->pctx == NULL
            || (ctx->pctx->operation != EVP_PKEY_OP_VERIFYCTX
                && ctx->pctx->operation != EVP_PKEY_OP_SIGNCTX)))
        goto legacy;

    switch (cmd) {
    case EVP_MD_CTRL_XOF_LEN:
        sz = (size_t)p1;
        params[0] = OSSL_PARAM_construct_size_t(OSSL_DIGEST_PARAM_XOFLEN, &sz);
        break;
    case EVP_MD_CTRL_MICALG:
        set_params = 0;
        params[0] = OSSL_PARAM_construct_utf8_string(OSSL_DIGEST_PARAM_MICALG,
                                                     p2, p1 ? p1 : 9999);
        break;
    case EVP_CTRL_SSL3_MASTER_SECRET:
        params[0] = OSSL_PARAM_construct_octet_string(OSSL_DIGEST_PARAM_SSL3_MS,
                                                      p2, p1);
        break;
    default:
        goto conclude;
    }

    if (set_params)
        ret = EVP_MD_CTX_set_params(ctx, params);
    else
        ret = EVP_MD_CTX_get_params(ctx, params);
    goto conclude;


/* TODO(3.0): Remove legacy code below */
 legacy:
    if (ctx->digest->md_ctrl == NULL) {
        ERR_raise(ERR_LIB_EVP, EVP_R_CTRL_NOT_IMPLEMENTED);
        return 0;
    }

    ret = ctx->digest->md_ctrl(ctx, cmd, p1, p2);
 conclude:
    if (ret <= 0)
        return 0;
    return ret;
}