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
struct TYPE_2__ {int /*<<< orphan*/  constant_len; int /*<<< orphan*/  constant; int /*<<< orphan*/  key_len; int /*<<< orphan*/  key; int /*<<< orphan*/  cipher; int /*<<< orphan*/  provctx; } ;
typedef  int /*<<< orphan*/  OSSL_PARAM ;
typedef  int /*<<< orphan*/  OPENSSL_CTX ;
typedef  TYPE_1__ KRB5KDF_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  OSSL_KDF_PARAM_CONSTANT ; 
 int /*<<< orphan*/  OSSL_KDF_PARAM_KEY ; 
 int /*<<< orphan*/ * OSSL_PARAM_locate_const (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * PROV_LIBRARY_CONTEXT_OF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5kdf_set_membuf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ossl_prov_cipher_load_from_params (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int krb5kdf_set_ctx_params(void *vctx, const OSSL_PARAM params[])
{
    const OSSL_PARAM *p;
    KRB5KDF_CTX *ctx = vctx;
    OPENSSL_CTX *provctx = PROV_LIBRARY_CONTEXT_OF(ctx->provctx);

    if (!ossl_prov_cipher_load_from_params(&ctx->cipher, params, provctx))
        return 0;

    if ((p = OSSL_PARAM_locate_const(params, OSSL_KDF_PARAM_KEY)) != NULL)
        if (!krb5kdf_set_membuf(&ctx->key, &ctx->key_len, p))
            return 0;

    if ((p = OSSL_PARAM_locate_const(params, OSSL_KDF_PARAM_CONSTANT))
        != NULL)
        if (!krb5kdf_set_membuf(&ctx->constant, &ctx->constant_len, p))
            return 0;

    return 1;
}