#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {size_t out_len; int /*<<< orphan*/  salt_len; int /*<<< orphan*/  salt; int /*<<< orphan*/  info_len; int /*<<< orphan*/  info; int /*<<< orphan*/  secret_len; int /*<<< orphan*/  secret; int /*<<< orphan*/  macctx; int /*<<< orphan*/  digest; int /*<<< orphan*/  provctx; } ;
typedef  int /*<<< orphan*/  OSSL_PARAM ;
typedef  int /*<<< orphan*/  OPENSSL_CTX ;
typedef  TYPE_1__ KDF_SSKDF ;

/* Variables and functions */
 int /*<<< orphan*/  OSSL_KDF_PARAM_INFO ; 
 int /*<<< orphan*/  OSSL_KDF_PARAM_KEY ; 
 int /*<<< orphan*/  OSSL_KDF_PARAM_MAC_SIZE ; 
 int /*<<< orphan*/  OSSL_KDF_PARAM_SALT ; 
 int /*<<< orphan*/  OSSL_KDF_PARAM_SECRET ; 
 int /*<<< orphan*/  OSSL_PARAM_get_size_t (int /*<<< orphan*/  const*,size_t*) ; 
 int /*<<< orphan*/ * OSSL_PARAM_locate_const (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * PROV_LIBRARY_CONTEXT_OF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ossl_prov_digest_load_from_params (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ossl_prov_macctx_load_from_params (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sskdf_set_buffer (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int sskdf_set_ctx_params(void *vctx, const OSSL_PARAM params[])
{
    const OSSL_PARAM *p;
    KDF_SSKDF *ctx = vctx;
    OPENSSL_CTX *libctx = PROV_LIBRARY_CONTEXT_OF(ctx->provctx);
    size_t sz;

    if (!ossl_prov_digest_load_from_params(&ctx->digest, params, libctx))
        return 0;

    if (!ossl_prov_macctx_load_from_params(&ctx->macctx, params,
                                           NULL, NULL, NULL, libctx))
        return 0;

    if ((p = OSSL_PARAM_locate_const(params, OSSL_KDF_PARAM_SECRET)) != NULL
        || (p = OSSL_PARAM_locate_const(params, OSSL_KDF_PARAM_KEY)) != NULL)
        if (!sskdf_set_buffer(&ctx->secret, &ctx->secret_len, p))
            return 0;

    if ((p = OSSL_PARAM_locate_const(params, OSSL_KDF_PARAM_INFO)) != NULL)
        if (!sskdf_set_buffer(&ctx->info, &ctx->info_len, p))
            return 0;

    if ((p = OSSL_PARAM_locate_const(params, OSSL_KDF_PARAM_SALT)) != NULL)
        if (!sskdf_set_buffer(&ctx->salt, &ctx->salt_len, p))
            return 0;

    if ((p = OSSL_PARAM_locate_const(params, OSSL_KDF_PARAM_MAC_SIZE))
        != NULL) {
        if (!OSSL_PARAM_get_size_t(p, &sz) || sz == 0)
            return 0;
        ctx->out_len = sz;
    }
    return 1;
}