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
struct gmac_data_st {int /*<<< orphan*/  cipher; int /*<<< orphan*/  provctx; int /*<<< orphan*/ * ctx; } ;
struct TYPE_6__ {scalar_t__ data_type; size_t data_size; int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ OSSL_PARAM ;
typedef  int /*<<< orphan*/  OPENSSL_CTX ;
typedef  int /*<<< orphan*/  EVP_CIPHER_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_LIB_PROV ; 
 int /*<<< orphan*/  ERR_raise (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_CIPHER_CTX_ctrl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *) ; 
 scalar_t__ EVP_CIPHER_CTX_key_length (int /*<<< orphan*/ *) ; 
 scalar_t__ EVP_CIPHER_mode (int /*<<< orphan*/ *) ; 
 scalar_t__ EVP_CIPH_GCM_MODE ; 
 int /*<<< orphan*/  EVP_CTRL_AEAD_SET_IVLEN ; 
 int /*<<< orphan*/  EVP_EncryptInit_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_R_CIPHER_NOT_GCM_MODE ; 
 int /*<<< orphan*/  EVP_R_INVALID_KEY_LENGTH ; 
 int /*<<< orphan*/  OSSL_MAC_PARAM_IV ; 
 int /*<<< orphan*/  OSSL_MAC_PARAM_KEY ; 
 scalar_t__ OSSL_PARAM_OCTET_STRING ; 
 TYPE_1__* OSSL_PARAM_locate_const (TYPE_1__ const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * PROV_LIBRARY_CONTEXT_OF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ossl_prov_cipher_cipher (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ossl_prov_cipher_engine (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ossl_prov_cipher_load_from_params (int /*<<< orphan*/ *,TYPE_1__ const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gmac_set_ctx_params(void *vmacctx, const OSSL_PARAM params[])
{
    struct gmac_data_st *macctx = vmacctx;
    EVP_CIPHER_CTX *ctx = macctx->ctx;
    OPENSSL_CTX *provctx = PROV_LIBRARY_CONTEXT_OF(macctx->provctx);
    const OSSL_PARAM *p;

   if (ctx == NULL
        || !ossl_prov_cipher_load_from_params(&macctx->cipher, params, provctx))
        return 0;

    if (EVP_CIPHER_mode(ossl_prov_cipher_cipher(&macctx->cipher))
        != EVP_CIPH_GCM_MODE) {
        ERR_raise(ERR_LIB_PROV, EVP_R_CIPHER_NOT_GCM_MODE);
        return 0;
    }
    if (!EVP_EncryptInit_ex(ctx, ossl_prov_cipher_cipher(&macctx->cipher),
                            ossl_prov_cipher_engine(&macctx->cipher), NULL,
                            NULL))
        return 0;

    if ((p = OSSL_PARAM_locate_const(params, OSSL_MAC_PARAM_KEY)) != NULL) {
        if (p->data_type != OSSL_PARAM_OCTET_STRING)
            return 0;

        if (p->data_size != (size_t)EVP_CIPHER_CTX_key_length(ctx)) {
            ERR_raise(ERR_LIB_PROV, EVP_R_INVALID_KEY_LENGTH);
            return 0;
        }
        if (!EVP_EncryptInit_ex(ctx, NULL, NULL, p->data, NULL))
            return 0;
    }
    if ((p = OSSL_PARAM_locate_const(params, OSSL_MAC_PARAM_IV)) != NULL) {
        if (p->data_type != OSSL_PARAM_OCTET_STRING)
            return 0;

        if (!EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_AEAD_SET_IVLEN,
                                 p->data_size, NULL)
            || !EVP_EncryptInit_ex(ctx, NULL, NULL, NULL, p->data))
            return 0;
    }
    return 1;
}