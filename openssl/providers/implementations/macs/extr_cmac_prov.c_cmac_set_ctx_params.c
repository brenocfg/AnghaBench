#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct cmac_data_st {int /*<<< orphan*/  cipher; int /*<<< orphan*/  ctx; int /*<<< orphan*/  provctx; } ;
struct TYPE_6__ {scalar_t__ data_type; int /*<<< orphan*/  data_size; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ OSSL_PARAM ;
typedef  int /*<<< orphan*/  OPENSSL_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  CMAC_Init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSSL_MAC_PARAM_KEY ; 
 scalar_t__ OSSL_PARAM_OCTET_STRING ; 
 TYPE_1__* OSSL_PARAM_locate_const (TYPE_1__ const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * PROV_LIBRARY_CONTEXT_OF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ossl_prov_cipher_cipher (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ossl_prov_cipher_engine (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ossl_prov_cipher_load_from_params (int /*<<< orphan*/ *,TYPE_1__ const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ossl_prov_cipher_reset (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cmac_set_ctx_params(void *vmacctx, const OSSL_PARAM params[])
{
    struct cmac_data_st *macctx = vmacctx;
    OPENSSL_CTX *ctx = PROV_LIBRARY_CONTEXT_OF(macctx->provctx);
    const OSSL_PARAM *p;

    if (!ossl_prov_cipher_load_from_params(&macctx->cipher, params, ctx))
        return 0;

    if ((p = OSSL_PARAM_locate_const(params, OSSL_MAC_PARAM_KEY)) != NULL) {
        if (p->data_type != OSSL_PARAM_OCTET_STRING)
            return 0;

        if (!CMAC_Init(macctx->ctx, p->data, p->data_size,
                       ossl_prov_cipher_cipher(&macctx->cipher),
                       ossl_prov_cipher_engine(&macctx->cipher)))
            return 0;

        ossl_prov_cipher_reset(&macctx->cipher);
    }
    return 1;
}