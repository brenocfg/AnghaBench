#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ nid; int /*<<< orphan*/  keklen; } ;
struct TYPE_11__ {scalar_t__ cek_nid; int /*<<< orphan*/  dkm_len; int /*<<< orphan*/  ukm_len; int /*<<< orphan*/  ukm; int /*<<< orphan*/  secret_len; int /*<<< orphan*/  secret; int /*<<< orphan*/  digest; int /*<<< orphan*/  provctx; } ;
struct TYPE_10__ {scalar_t__ data_type; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ OSSL_PARAM ;
typedef  int /*<<< orphan*/  OPENSSL_CTX ;
typedef  TYPE_2__ KDF_X942 ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_LIB_PROV ; 
 int /*<<< orphan*/  ERR_raise (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ OBJ_sn2nid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSSL_KDF_PARAM_CEK_ALG ; 
 int /*<<< orphan*/  OSSL_KDF_PARAM_KEY ; 
 int /*<<< orphan*/  OSSL_KDF_PARAM_SECRET ; 
 int /*<<< orphan*/  OSSL_KDF_PARAM_UKM ; 
 size_t OSSL_NELEM (TYPE_6__*) ; 
 scalar_t__ OSSL_PARAM_UTF8_STRING ; 
 TYPE_1__* OSSL_PARAM_locate_const (TYPE_1__ const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * PROV_LIBRARY_CONTEXT_OF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROV_R_UNSUPPORTED_CEK_ALG ; 
 TYPE_6__* kek_algs ; 
 int /*<<< orphan*/  ossl_prov_digest_load_from_params (int /*<<< orphan*/ *,TYPE_1__ const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  x942kdf_set_buffer (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__ const*) ; 

__attribute__((used)) static int x942kdf_set_ctx_params(void *vctx, const OSSL_PARAM params[])
{
    const OSSL_PARAM *p;
    KDF_X942 *ctx = vctx;
    OPENSSL_CTX *provctx = PROV_LIBRARY_CONTEXT_OF(ctx->provctx);
    size_t i;

    if (!ossl_prov_digest_load_from_params(&ctx->digest, params, provctx))
        return 0;

    if ((p = OSSL_PARAM_locate_const(params, OSSL_KDF_PARAM_SECRET)) != NULL
        || (p = OSSL_PARAM_locate_const(params, OSSL_KDF_PARAM_KEY)) != NULL)
        if (!x942kdf_set_buffer(&ctx->secret, &ctx->secret_len, p))
            return 0;

    if ((p = OSSL_PARAM_locate_const(params, OSSL_KDF_PARAM_UKM)) != NULL)
        if (!x942kdf_set_buffer(&ctx->ukm, &ctx->ukm_len, p))
            return 0;

    if ((p = OSSL_PARAM_locate_const(params, OSSL_KDF_PARAM_CEK_ALG)) != NULL) {
        if (p->data_type != OSSL_PARAM_UTF8_STRING)
            return 0;
        ctx->cek_nid = OBJ_sn2nid(p->data);
        for (i = 0; i < OSSL_NELEM(kek_algs); i++)
            if (kek_algs[i].nid == ctx->cek_nid)
                goto cek_found;
        ERR_raise(ERR_LIB_PROV, PROV_R_UNSUPPORTED_CEK_ALG);
        return 0;
cek_found:
        ctx->dkm_len = kek_algs[i].keklen;
    }
    return 1;
}