#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ enc; scalar_t__ hw; } ;
struct TYPE_12__ {scalar_t__ data_type; scalar_t__ data_size; int /*<<< orphan*/ * data; } ;
struct TYPE_11__ {size_t nonce_len; scalar_t__ tag_len; size_t tls_aad_pad_sz; TYPE_4__ base; int /*<<< orphan*/  tag; } ;
struct TYPE_10__ {size_t (* tls_init ) (TYPE_4__*,int /*<<< orphan*/ *,scalar_t__) ;scalar_t__ (* tls_iv_set_fixed ) (TYPE_4__*,int /*<<< orphan*/ *,scalar_t__) ;} ;
typedef  TYPE_1__ PROV_CIPHER_HW_CHACHA20_POLY1305 ;
typedef  TYPE_2__ PROV_CHACHA20_POLY1305_CTX ;
typedef  TYPE_3__ OSSL_PARAM ;

/* Variables and functions */
 size_t CHACHA20_POLY1305_KEYLEN ; 
 size_t CHACHA20_POLY1305_MAX_IVLEN ; 
 int /*<<< orphan*/  ERR_LIB_PROV ; 
 int /*<<< orphan*/  ERR_raise (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSSL_CIPHER_PARAM_AEAD_TAG ; 
 int /*<<< orphan*/  OSSL_CIPHER_PARAM_AEAD_TLS1_AAD ; 
 int /*<<< orphan*/  OSSL_CIPHER_PARAM_AEAD_TLS1_IV_FIXED ; 
 int /*<<< orphan*/  OSSL_CIPHER_PARAM_IVLEN ; 
 int /*<<< orphan*/  OSSL_CIPHER_PARAM_KEYLEN ; 
 scalar_t__ OSSL_PARAM_OCTET_STRING ; 
 int /*<<< orphan*/  OSSL_PARAM_get_size_t (TYPE_3__ const*,size_t*) ; 
 TYPE_3__* OSSL_PARAM_locate_const (TYPE_3__ const*,int /*<<< orphan*/ ) ; 
 scalar_t__ POLY1305_BLOCK_SIZE ; 
 int /*<<< orphan*/  PROV_R_FAILED_TO_GET_PARAMETER ; 
 int /*<<< orphan*/  PROV_R_INVALID_DATA ; 
 int /*<<< orphan*/  PROV_R_INVALID_IVLEN ; 
 int /*<<< orphan*/  PROV_R_INVALID_IV_LENGTH ; 
 int /*<<< orphan*/  PROV_R_INVALID_KEY_LENGTH ; 
 int /*<<< orphan*/  PROV_R_INVALID_TAGLEN ; 
 int /*<<< orphan*/  PROV_R_TAG_NOT_NEEDED ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 size_t stub1 (TYPE_4__*,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ stub2 (TYPE_4__*,int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static int chacha20_poly1305_set_ctx_params(void *vctx,
                                            const OSSL_PARAM params[])
{
    const OSSL_PARAM *p;
    size_t len;
    PROV_CHACHA20_POLY1305_CTX *ctx = (PROV_CHACHA20_POLY1305_CTX *)vctx;
    PROV_CIPHER_HW_CHACHA20_POLY1305 *hw =
        (PROV_CIPHER_HW_CHACHA20_POLY1305 *)ctx->base.hw;

    p = OSSL_PARAM_locate_const(params, OSSL_CIPHER_PARAM_KEYLEN);
    if (p != NULL) {
        if (!OSSL_PARAM_get_size_t(p, &len)) {
            ERR_raise(ERR_LIB_PROV, PROV_R_FAILED_TO_GET_PARAMETER);
            return 0;
        }
        if (len != CHACHA20_POLY1305_KEYLEN) {
            ERR_raise(ERR_LIB_PROV, PROV_R_INVALID_KEY_LENGTH);
            return 0;
        }
    }
    p = OSSL_PARAM_locate_const(params, OSSL_CIPHER_PARAM_IVLEN);
    if (p != NULL) {
        if (!OSSL_PARAM_get_size_t(p, &len)) {
            ERR_raise(ERR_LIB_PROV, PROV_R_FAILED_TO_GET_PARAMETER);
            return 0;
        }
        if (len == 0 || len > CHACHA20_POLY1305_MAX_IVLEN) {
            ERR_raise(ERR_LIB_PROV, PROV_R_INVALID_IV_LENGTH);
            return 0;
        }
        ctx->nonce_len = len;
    }

    p = OSSL_PARAM_locate_const(params, OSSL_CIPHER_PARAM_AEAD_TAG);
    if (p != NULL) {
        if (p->data_type != OSSL_PARAM_OCTET_STRING) {
            ERR_raise(ERR_LIB_PROV, PROV_R_FAILED_TO_GET_PARAMETER);
            return 0;
        }
        if (p->data_size == 0 || p->data_size > POLY1305_BLOCK_SIZE) {
            ERR_raise(ERR_LIB_PROV, PROV_R_INVALID_TAGLEN);
            return 0;
        }
        if (p->data != NULL) {
            if (ctx->base.enc) {
                ERR_raise(ERR_LIB_PROV, PROV_R_TAG_NOT_NEEDED);
                return 0;
            }
            memcpy(ctx->tag, p->data, p->data_size);
        }
        ctx->tag_len = p->data_size;
    }

    p = OSSL_PARAM_locate_const(params, OSSL_CIPHER_PARAM_AEAD_TLS1_AAD);
    if (p != NULL) {
        if (p->data_type != OSSL_PARAM_OCTET_STRING) {
            ERR_raise(ERR_LIB_PROV, PROV_R_FAILED_TO_GET_PARAMETER);
            return 0;
        }
        len = hw->tls_init(&ctx->base, p->data, p->data_size);
        if (len == 0) {
            ERR_raise(ERR_LIB_PROV, PROV_R_INVALID_DATA);
            return 0;
        }
        ctx->tls_aad_pad_sz = len;
    }

    p = OSSL_PARAM_locate_const(params, OSSL_CIPHER_PARAM_AEAD_TLS1_IV_FIXED);
    if (p != NULL) {
        if (p->data_type != OSSL_PARAM_OCTET_STRING) {
            ERR_raise(ERR_LIB_PROV, PROV_R_FAILED_TO_GET_PARAMETER);
            return 0;
        }
        if (hw->tls_iv_set_fixed(&ctx->base, p->data, p->data_size) == 0) {
            ERR_raise(ERR_LIB_PROV, PROV_R_INVALID_IVLEN);
            return 0;
        }
    }
    /* ignore OSSL_CIPHER_PARAM_AEAD_MAC_KEY */
    return 1;
}