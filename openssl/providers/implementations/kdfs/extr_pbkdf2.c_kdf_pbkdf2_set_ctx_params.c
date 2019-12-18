#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_11__ {int lower_bound_checks; int iter; int /*<<< orphan*/  salt_len; int /*<<< orphan*/  salt; int /*<<< orphan*/  pass_len; int /*<<< orphan*/  pass; int /*<<< orphan*/  digest; int /*<<< orphan*/  provctx; } ;
struct TYPE_10__ {scalar_t__ data_size; } ;
typedef  TYPE_1__ OSSL_PARAM ;
typedef  int /*<<< orphan*/  OPENSSL_CTX ;
typedef  TYPE_2__ KDF_PBKDF2 ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_LIB_PROV ; 
 int /*<<< orphan*/  ERR_raise (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int KDF_PBKDF2_MIN_ITERATIONS ; 
 scalar_t__ KDF_PBKDF2_MIN_SALT_LEN ; 
 int /*<<< orphan*/  OSSL_KDF_PARAM_ITER ; 
 int /*<<< orphan*/  OSSL_KDF_PARAM_PASSWORD ; 
 int /*<<< orphan*/  OSSL_KDF_PARAM_PKCS5 ; 
 int /*<<< orphan*/  OSSL_KDF_PARAM_SALT ; 
 int /*<<< orphan*/  OSSL_PARAM_get_int (TYPE_1__ const*,int*) ; 
 int /*<<< orphan*/  OSSL_PARAM_get_uint64 (TYPE_1__ const*,int*) ; 
 TYPE_1__* OSSL_PARAM_locate_const (TYPE_1__ const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * PROV_LIBRARY_CONTEXT_OF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROV_R_INVALID_ITERATION_COUNT ; 
 int /*<<< orphan*/  PROV_R_INVALID_SALT_LENGTH ; 
 int /*<<< orphan*/  ossl_prov_digest_load_from_params (int /*<<< orphan*/ *,TYPE_1__ const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pbkdf2_set_membuf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__ const*) ; 

__attribute__((used)) static int kdf_pbkdf2_set_ctx_params(void *vctx, const OSSL_PARAM params[])
{
    const OSSL_PARAM *p;
    KDF_PBKDF2 *ctx = vctx;
    OPENSSL_CTX *provctx = PROV_LIBRARY_CONTEXT_OF(ctx->provctx);
    int pkcs5;
    uint64_t iter, min_iter;

    if (!ossl_prov_digest_load_from_params(&ctx->digest, params, provctx))
        return 0;

    if ((p = OSSL_PARAM_locate_const(params, OSSL_KDF_PARAM_PKCS5)) != NULL) {
        if (!OSSL_PARAM_get_int(p, &pkcs5))
            return 0;
        ctx->lower_bound_checks = pkcs5 == 0;
    }

    if ((p = OSSL_PARAM_locate_const(params, OSSL_KDF_PARAM_PASSWORD)) != NULL)
        if (!pbkdf2_set_membuf(&ctx->pass, &ctx->pass_len, p))
            return 0;

    if ((p = OSSL_PARAM_locate_const(params, OSSL_KDF_PARAM_SALT)) != NULL) {
        if (ctx->lower_bound_checks != 0
            && p->data_size < KDF_PBKDF2_MIN_SALT_LEN) {
            ERR_raise(ERR_LIB_PROV, PROV_R_INVALID_SALT_LENGTH);
            return 0;
        }
        if (!pbkdf2_set_membuf(&ctx->salt, &ctx->salt_len,p))
            return 0;
    }

    if ((p = OSSL_PARAM_locate_const(params, OSSL_KDF_PARAM_ITER)) != NULL) {
        if (!OSSL_PARAM_get_uint64(p, &iter))
            return 0;
        min_iter = ctx->lower_bound_checks != 0 ? KDF_PBKDF2_MIN_ITERATIONS : 1;
        if (iter < min_iter) {
            ERR_raise(ERR_LIB_PROV, PROV_R_INVALID_ITERATION_COUNT);
            return 0;
        }
        ctx->iter = iter;
    }
    return 1;
}