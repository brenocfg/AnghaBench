#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ data_size; int /*<<< orphan*/ * data; } ;
struct TYPE_8__ {size_t seclen; void* seed; int seedlen; int /*<<< orphan*/ * sec; int /*<<< orphan*/  P_hash; int /*<<< orphan*/  P_sha1; int /*<<< orphan*/  provctx; } ;
typedef  TYPE_1__ TLS1_PRF ;
typedef  TYPE_2__ OSSL_PARAM ;
typedef  int /*<<< orphan*/  OPENSSL_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_MAC_CTX_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_cleanse (void*,int) ; 
 int /*<<< orphan*/  OPENSSL_clear_free (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  OSSL_KDF_PARAM_DIGEST ; 
 int /*<<< orphan*/  OSSL_KDF_PARAM_SECRET ; 
 int /*<<< orphan*/  OSSL_KDF_PARAM_SEED ; 
 int /*<<< orphan*/  OSSL_MAC_NAME_HMAC ; 
 int /*<<< orphan*/  OSSL_PARAM_get_octet_string (TYPE_2__ const*,void**,int,size_t*) ; 
 TYPE_2__* OSSL_PARAM_locate_const (TYPE_2__ const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * PROV_LIBRARY_CONTEXT_OF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SN_md5 ; 
 int /*<<< orphan*/  SN_md5_sha1 ; 
 int /*<<< orphan*/ * SN_sha1 ; 
 int TLS1_PRF_MAXBUF ; 
 int /*<<< orphan*/  ossl_prov_macctx_load_from_params (int /*<<< orphan*/ *,TYPE_2__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ strcasecmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kdf_tls1_prf_set_ctx_params(void *vctx, const OSSL_PARAM params[])
{
    const OSSL_PARAM *p;
    TLS1_PRF *ctx = vctx;
    OPENSSL_CTX *libctx = PROV_LIBRARY_CONTEXT_OF(ctx->provctx);

    if ((p = OSSL_PARAM_locate_const(params, OSSL_KDF_PARAM_DIGEST)) != NULL) {
        if (strcasecmp(p->data, SN_md5_sha1) == 0) {
            if (!ossl_prov_macctx_load_from_params(&ctx->P_hash, params,
                                                   OSSL_MAC_NAME_HMAC,
                                                   NULL, SN_md5, libctx)
                || !ossl_prov_macctx_load_from_params(&ctx->P_sha1, params,
                                                      OSSL_MAC_NAME_HMAC,
                                                      NULL, SN_sha1, libctx))
                return 0;
        } else {
            EVP_MAC_CTX_free(ctx->P_sha1);
            if (!ossl_prov_macctx_load_from_params(&ctx->P_hash, params,
                                                   OSSL_MAC_NAME_HMAC,
                                                   NULL, NULL, libctx))
                return 0;
        }
    }

    if ((p = OSSL_PARAM_locate_const(params, OSSL_KDF_PARAM_SECRET)) != NULL) {
        OPENSSL_clear_free(ctx->sec, ctx->seclen);
        ctx->sec = NULL;
        if (!OSSL_PARAM_get_octet_string(p, (void **)&ctx->sec, 0, &ctx->seclen))
            return 0;
    }
    /* The seed fields concatenate, so process them all */
    if ((p = OSSL_PARAM_locate_const(params, OSSL_KDF_PARAM_SEED)) != NULL) {
        OPENSSL_cleanse(ctx->seed, ctx->seedlen);
        ctx->seedlen = 0;

        for (; p != NULL; p = OSSL_PARAM_locate_const(p + 1,
                                                      OSSL_KDF_PARAM_SEED)) {
            const void *q = ctx->seed + ctx->seedlen;
            size_t sz = 0;

            if (p->data_size != 0
                && p->data != NULL
                && !OSSL_PARAM_get_octet_string(p, (void **)&q,
                                                TLS1_PRF_MAXBUF - ctx->seedlen,
                                                &sz))
                return 0;
            ctx->seedlen += sz;
        }
    }
    return 1;
}