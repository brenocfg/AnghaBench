#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct hmac_data_st {int /*<<< orphan*/  digest; int /*<<< orphan*/  ctx; int /*<<< orphan*/  provctx; } ;
struct TYPE_7__ {scalar_t__ data_type; int /*<<< orphan*/  data_size; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ OSSL_PARAM ;
typedef  int /*<<< orphan*/  OPENSSL_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  HMAC_CTX_set_flags (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HMAC_Init_ex (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSSL_MAC_PARAM_FLAGS ; 
 int /*<<< orphan*/  OSSL_MAC_PARAM_KEY ; 
 scalar_t__ OSSL_PARAM_OCTET_STRING ; 
 int /*<<< orphan*/  OSSL_PARAM_get_int (TYPE_1__ const*,int*) ; 
 TYPE_1__* OSSL_PARAM_locate_const (TYPE_1__ const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * PROV_LIBRARY_CONTEXT_OF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ossl_prov_digest_load_from_params (int /*<<< orphan*/ *,TYPE_1__ const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ossl_prov_digest_md (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ossl_prov_digest_reset (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hmac_set_ctx_params(void *vmacctx, const OSSL_PARAM params[])
{
    struct hmac_data_st *macctx = vmacctx;
    OPENSSL_CTX *ctx = PROV_LIBRARY_CONTEXT_OF(macctx->provctx);
    const OSSL_PARAM *p;

    if (!ossl_prov_digest_load_from_params(&macctx->digest, params, ctx))
        return 0;

    /* TODO(3.0) formalize the meaning of "flags", perhaps as other params */
    if ((p = OSSL_PARAM_locate_const(params,
                                     OSSL_MAC_PARAM_FLAGS)) != NULL) {
        int flags = 0;

        if (!OSSL_PARAM_get_int(p, &flags))
            return 0;
        HMAC_CTX_set_flags(macctx->ctx, flags);
    }
    if ((p = OSSL_PARAM_locate_const(params, OSSL_MAC_PARAM_KEY)) != NULL) {
        if (p->data_type != OSSL_PARAM_OCTET_STRING)
            return 0;

        if (!HMAC_Init_ex(macctx->ctx, p->data, p->data_size,
                          ossl_prov_digest_md(&macctx->digest),
                          NULL /* ENGINE */))
            return 0;

        ossl_prov_digest_reset(&macctx->digest);
    }
    return 1;
}