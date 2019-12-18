#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ ki_len; scalar_t__ label_len; scalar_t__ context_len; scalar_t__ iv_len; int /*<<< orphan*/ * ctx_init; int /*<<< orphan*/  ki; int /*<<< orphan*/  iv; int /*<<< orphan*/  context; int /*<<< orphan*/  label; int /*<<< orphan*/  mode; int /*<<< orphan*/  provctx; } ;
struct TYPE_11__ {int /*<<< orphan*/  data_size; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ OSSL_PARAM ;
typedef  int /*<<< orphan*/  OPENSSL_CTX ;
typedef  TYPE_2__ KBKDF ;

/* Variables and functions */
 int /*<<< orphan*/  COUNTER ; 
 int /*<<< orphan*/  ERR_LIB_PROV ; 
 int /*<<< orphan*/  ERR_raise (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_MAC_CTX_mac (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_MAC_CTX_set_params (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  EVP_MAC_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_MAC_is_a (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FEEDBACK ; 
 int /*<<< orphan*/  OSSL_KDF_PARAM_INFO ; 
 int /*<<< orphan*/  OSSL_KDF_PARAM_KEY ; 
 int /*<<< orphan*/  OSSL_KDF_PARAM_MODE ; 
 int /*<<< orphan*/  OSSL_KDF_PARAM_SALT ; 
 int /*<<< orphan*/  OSSL_KDF_PARAM_SEED ; 
 int /*<<< orphan*/  OSSL_MAC_NAME_CMAC ; 
 int /*<<< orphan*/  OSSL_MAC_NAME_HMAC ; 
 int /*<<< orphan*/  OSSL_MAC_PARAM_KEY ; 
 TYPE_1__ OSSL_PARAM_construct_end () ; 
 TYPE_1__ OSSL_PARAM_construct_octet_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_1__* OSSL_PARAM_locate_const (TYPE_1__ const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * PROV_LIBRARY_CONTEXT_OF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROV_R_INVALID_MAC ; 
 int /*<<< orphan*/  PROV_R_INVALID_MODE ; 
 int /*<<< orphan*/  kbkdf_set_buffer (int /*<<< orphan*/ *,scalar_t__*,TYPE_1__ const*) ; 
 int /*<<< orphan*/  ossl_prov_macctx_load_from_params (int /*<<< orphan*/ **,TYPE_1__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ strncasecmp (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kbkdf_set_ctx_params(void *vctx, const OSSL_PARAM params[])
{
    KBKDF *ctx = (KBKDF *)vctx;
    OPENSSL_CTX *libctx = PROV_LIBRARY_CONTEXT_OF(ctx->provctx);
    const OSSL_PARAM *p;
    OSSL_PARAM mparams[2];

    if (!ossl_prov_macctx_load_from_params(&ctx->ctx_init, params, NULL,
                                           NULL, NULL, libctx))
        return 0;
    else if (ctx->ctx_init != NULL
             && !EVP_MAC_is_a(EVP_MAC_CTX_mac(ctx->ctx_init),
                              OSSL_MAC_NAME_HMAC)
             && !EVP_MAC_is_a(EVP_MAC_CTX_mac(ctx->ctx_init),
                              OSSL_MAC_NAME_CMAC)) {
        ERR_raise(ERR_LIB_PROV, PROV_R_INVALID_MAC);
        return 0;
    }

    p = OSSL_PARAM_locate_const(params, OSSL_KDF_PARAM_MODE);
    if (p != NULL && strncasecmp("counter", p->data, p->data_size) == 0) {
        ctx->mode = COUNTER;
    } else if (p != NULL
               && strncasecmp("feedback", p->data, p->data_size) == 0) {
        ctx->mode = FEEDBACK;
    } else if (p != NULL) {
        ERR_raise(ERR_LIB_PROV, PROV_R_INVALID_MODE);
        return 0;
    }

    p = OSSL_PARAM_locate_const(params, OSSL_KDF_PARAM_KEY);
    if (p != NULL && !kbkdf_set_buffer(&ctx->ki, &ctx->ki_len, p))
        return 0;

    p = OSSL_PARAM_locate_const(params, OSSL_KDF_PARAM_SALT);
    if (p != NULL && !kbkdf_set_buffer(&ctx->label, &ctx->label_len, p))
        return 0;

    p = OSSL_PARAM_locate_const(params, OSSL_KDF_PARAM_INFO);
    if (p != NULL && !kbkdf_set_buffer(&ctx->context, &ctx->context_len, p))
        return 0;

    p = OSSL_PARAM_locate_const(params, OSSL_KDF_PARAM_SEED);
    if (p != NULL && !kbkdf_set_buffer(&ctx->iv, &ctx->iv_len, p))
        return 0;

    /* Set up digest context, if we can. */
    if (ctx->ctx_init != NULL && ctx->ki_len != 0) {
        mparams[0] = OSSL_PARAM_construct_octet_string(OSSL_MAC_PARAM_KEY,
                                                       ctx->ki, ctx->ki_len);
        mparams[1] = OSSL_PARAM_construct_end();

        if (!EVP_MAC_CTX_set_params(ctx->ctx_init, mparams)
            || !EVP_MAC_init(ctx->ctx_init))
            return 0;
    }

    return 1;
}