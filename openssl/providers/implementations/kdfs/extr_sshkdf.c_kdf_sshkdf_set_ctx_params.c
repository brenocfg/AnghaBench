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
struct TYPE_9__ {char type; int /*<<< orphan*/  session_id_len; int /*<<< orphan*/  session_id; int /*<<< orphan*/  xcghash_len; int /*<<< orphan*/  xcghash; int /*<<< orphan*/  key_len; int /*<<< orphan*/  key; int /*<<< orphan*/  digest; int /*<<< orphan*/  provctx; } ;
struct TYPE_8__ {scalar_t__ data_size; int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ OSSL_PARAM ;
typedef  int /*<<< orphan*/  OPENSSL_CTX ;
typedef  TYPE_2__ KDF_SSHKDF ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_LIB_PROV ; 
 int /*<<< orphan*/  ERR_raise (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSSL_KDF_PARAM_KEY ; 
 int /*<<< orphan*/  OSSL_KDF_PARAM_SSHKDF_SESSION_ID ; 
 int /*<<< orphan*/  OSSL_KDF_PARAM_SSHKDF_TYPE ; 
 int /*<<< orphan*/  OSSL_KDF_PARAM_SSHKDF_XCGHASH ; 
 TYPE_1__* OSSL_PARAM_locate_const (TYPE_1__ const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * PROV_LIBRARY_CONTEXT_OF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROV_R_VALUE_ERROR ; 
 int /*<<< orphan*/  ossl_prov_digest_load_from_params (int /*<<< orphan*/ *,TYPE_1__ const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sshkdf_set_membuf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__ const*) ; 

__attribute__((used)) static int kdf_sshkdf_set_ctx_params(void *vctx, const OSSL_PARAM params[])
{
    const OSSL_PARAM *p;
    KDF_SSHKDF *ctx = vctx;
    OPENSSL_CTX *provctx = PROV_LIBRARY_CONTEXT_OF(ctx->provctx);
    int t;

    if (!ossl_prov_digest_load_from_params(&ctx->digest, params, provctx))
        return 0;

    if ((p = OSSL_PARAM_locate_const(params, OSSL_KDF_PARAM_KEY)) != NULL)
        if (!sshkdf_set_membuf(&ctx->key, &ctx->key_len, p))
            return 0;

    if ((p = OSSL_PARAM_locate_const(params, OSSL_KDF_PARAM_SSHKDF_XCGHASH))
        != NULL)
        if (!sshkdf_set_membuf(&ctx->xcghash, &ctx->xcghash_len, p))
            return 0;

    if ((p = OSSL_PARAM_locate_const(params, OSSL_KDF_PARAM_SSHKDF_SESSION_ID))
        != NULL)
        if (!sshkdf_set_membuf(&ctx->session_id, &ctx->session_id_len, p))
            return 0;

    if ((p = OSSL_PARAM_locate_const(params, OSSL_KDF_PARAM_SSHKDF_TYPE))
        != NULL) {
        if (p->data == NULL || p->data_size == 0)
            return 0;
        t = *(unsigned char *)p->data;
        if (t < 65 || t > 70) {
            ERR_raise(ERR_LIB_PROV, PROV_R_VALUE_ERROR);
            return 0;
        }
        ctx->type = (char)t;
    }
    return 1;
}