#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int mode; size_t key_len; size_t salt_len; int info_len; void* info; int /*<<< orphan*/ * salt; int /*<<< orphan*/ * key; int /*<<< orphan*/  digest; int /*<<< orphan*/  provctx; } ;
struct TYPE_9__ {scalar_t__ data_type; scalar_t__ data_size; int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ OSSL_PARAM ;
typedef  int /*<<< orphan*/  OPENSSL_CTX ;
typedef  TYPE_2__ KDF_HKDF ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_LIB_PROV ; 
 int /*<<< orphan*/  ERR_raise (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EVP_KDF_HKDF_MODE_EXPAND_ONLY ; 
 int EVP_KDF_HKDF_MODE_EXTRACT_AND_EXPAND ; 
 int EVP_KDF_HKDF_MODE_EXTRACT_ONLY ; 
 int HKDF_MAXBUF ; 
 int /*<<< orphan*/  OPENSSL_clear_free (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  OPENSSL_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSSL_KDF_PARAM_INFO ; 
 int /*<<< orphan*/  OSSL_KDF_PARAM_KEY ; 
 int /*<<< orphan*/  OSSL_KDF_PARAM_MODE ; 
 int /*<<< orphan*/  OSSL_KDF_PARAM_SALT ; 
 scalar_t__ OSSL_PARAM_UTF8_STRING ; 
 scalar_t__ OSSL_PARAM_get_int (TYPE_1__ const*,int*) ; 
 int /*<<< orphan*/  OSSL_PARAM_get_octet_string (TYPE_1__ const*,void**,int,size_t*) ; 
 TYPE_1__* OSSL_PARAM_locate_const (TYPE_1__ const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * PROV_LIBRARY_CONTEXT_OF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROV_R_INVALID_MODE ; 
 int /*<<< orphan*/  ossl_prov_digest_load_from_params (int /*<<< orphan*/ *,TYPE_1__ const*,int /*<<< orphan*/ *) ; 
 scalar_t__ strcasecmp (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int kdf_hkdf_set_ctx_params(void *vctx, const OSSL_PARAM params[])
{
    const OSSL_PARAM *p;
    KDF_HKDF *ctx = vctx;
    OPENSSL_CTX *provctx = PROV_LIBRARY_CONTEXT_OF(ctx->provctx);
    int n;

    if (!ossl_prov_digest_load_from_params(&ctx->digest, params, provctx))
        return 0;

    if ((p = OSSL_PARAM_locate_const(params, OSSL_KDF_PARAM_MODE)) != NULL) {
        if (p->data_type == OSSL_PARAM_UTF8_STRING) {
            if (strcasecmp(p->data, "EXTRACT_AND_EXPAND") == 0) {
                ctx->mode = EVP_KDF_HKDF_MODE_EXTRACT_AND_EXPAND;
            } else if (strcasecmp(p->data, "EXTRACT_ONLY") == 0) {
                ctx->mode = EVP_KDF_HKDF_MODE_EXTRACT_ONLY;
            } else if (strcasecmp(p->data, "EXPAND_ONLY") == 0) {
                ctx->mode = EVP_KDF_HKDF_MODE_EXPAND_ONLY;
            } else {
                ERR_raise(ERR_LIB_PROV, PROV_R_INVALID_MODE);
                return 0;
            }
        } else if (OSSL_PARAM_get_int(p, &n)) {
            if (n != EVP_KDF_HKDF_MODE_EXTRACT_AND_EXPAND
                && n != EVP_KDF_HKDF_MODE_EXTRACT_ONLY
                && n != EVP_KDF_HKDF_MODE_EXPAND_ONLY) {
                ERR_raise(ERR_LIB_PROV, PROV_R_INVALID_MODE);
                return 0;
            }
            ctx->mode = n;
        } else {
            ERR_raise(ERR_LIB_PROV, PROV_R_INVALID_MODE);
            return 0;
        }
    }

    if ((p = OSSL_PARAM_locate_const(params, OSSL_KDF_PARAM_KEY)) != NULL) {
        OPENSSL_clear_free(ctx->key, ctx->key_len);
        ctx->key = NULL;
        if (!OSSL_PARAM_get_octet_string(p, (void **)&ctx->key, 0,
                                         &ctx->key_len))
            return 0;
    }

    if ((p = OSSL_PARAM_locate_const(params, OSSL_KDF_PARAM_SALT)) != NULL) {
        if (p->data_size != 0 && p->data != NULL) {
            OPENSSL_free(ctx->salt);
            ctx->salt = NULL;
            if (!OSSL_PARAM_get_octet_string(p, (void **)&ctx->salt, 0,
                                             &ctx->salt_len))
                return 0;
        }
    }
    /* The info fields concatenate, so process them all */
    if ((p = OSSL_PARAM_locate_const(params, OSSL_KDF_PARAM_INFO)) != NULL) {
        ctx->info_len = 0;
        for (; p != NULL; p = OSSL_PARAM_locate_const(p + 1,
                                                      OSSL_KDF_PARAM_INFO)) {
            const void *q = ctx->info + ctx->info_len;
            size_t sz = 0;

            if (p->data_size != 0
                && p->data != NULL
                && !OSSL_PARAM_get_octet_string(p, (void **)&q,
                                                HKDF_MAXBUF - ctx->info_len,
                                                &sz))
                return 0;
            ctx->info_len += sz;
        }
    }
    return 1;
}