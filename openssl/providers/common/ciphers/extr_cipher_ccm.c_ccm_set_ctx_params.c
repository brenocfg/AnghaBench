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
struct TYPE_10__ {scalar_t__ data_type; int data_size; int /*<<< orphan*/ * data; } ;
struct TYPE_9__ {int tag_set; int m; size_t l; size_t tls_aad_pad_sz; int /*<<< orphan*/  buf; scalar_t__ enc; } ;
typedef  TYPE_1__ PROV_CCM_CTX ;
typedef  TYPE_2__ OSSL_PARAM ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_LIB_PROV ; 
 int /*<<< orphan*/  ERR_raise (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSSL_CIPHER_PARAM_AEAD_IVLEN ; 
 int /*<<< orphan*/  OSSL_CIPHER_PARAM_AEAD_TAG ; 
 int /*<<< orphan*/  OSSL_CIPHER_PARAM_AEAD_TLS1_AAD ; 
 int /*<<< orphan*/  OSSL_CIPHER_PARAM_AEAD_TLS1_IV_FIXED ; 
 scalar_t__ OSSL_PARAM_OCTET_STRING ; 
 int /*<<< orphan*/  OSSL_PARAM_get_size_t (TYPE_2__ const*,size_t*) ; 
 TYPE_2__* OSSL_PARAM_locate_const (TYPE_2__ const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROV_R_FAILED_TO_GET_PARAMETER ; 
 int /*<<< orphan*/  PROV_R_INVALID_DATA ; 
 int /*<<< orphan*/  PROV_R_INVALID_IVLEN ; 
 int /*<<< orphan*/  PROV_R_INVALID_TAGLEN ; 
 int /*<<< orphan*/  PROV_R_TAG_NOT_NEEDED ; 
 size_t ccm_tls_init (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ ccm_tls_iv_set_fixed (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

int ccm_set_ctx_params(void *vctx, const OSSL_PARAM params[])
{
    PROV_CCM_CTX *ctx = (PROV_CCM_CTX *)vctx;
    const OSSL_PARAM *p;
    size_t sz;

    p = OSSL_PARAM_locate_const(params, OSSL_CIPHER_PARAM_AEAD_TAG);
    if (p != NULL) {
        if (p->data_type != OSSL_PARAM_OCTET_STRING) {
            ERR_raise(ERR_LIB_PROV, PROV_R_FAILED_TO_GET_PARAMETER);
            return 0;
        }
        if ((p->data_size & 1) || (p->data_size < 4) || p->data_size > 16) {
            ERR_raise(ERR_LIB_PROV, PROV_R_INVALID_TAGLEN);
            return 0;
        }

        if (p->data != NULL) {
            if (ctx->enc) {
                ERR_raise(ERR_LIB_PROV, PROV_R_TAG_NOT_NEEDED);
                return 0;
            }
            memcpy(ctx->buf, p->data, p->data_size);
            ctx->tag_set = 1;
        }
        ctx->m = p->data_size;
    }

    p = OSSL_PARAM_locate_const(params, OSSL_CIPHER_PARAM_AEAD_IVLEN);
    if (p != NULL) {
        size_t ivlen;

        if (!OSSL_PARAM_get_size_t(p, &sz)) {
            ERR_raise(ERR_LIB_PROV, PROV_R_FAILED_TO_GET_PARAMETER);
            return 0;
        }
        ivlen = 15 - sz;
        if (ivlen < 2 || ivlen > 8) {
            ERR_raise(ERR_LIB_PROV, PROV_R_INVALID_IVLEN);
            return 0;
        }
        ctx->l = ivlen;
    }

    p = OSSL_PARAM_locate_const(params, OSSL_CIPHER_PARAM_AEAD_TLS1_AAD);
    if (p != NULL) {
        if (p->data_type != OSSL_PARAM_OCTET_STRING) {
            ERR_raise(ERR_LIB_PROV, PROV_R_FAILED_TO_GET_PARAMETER);
            return 0;
        }
        sz = ccm_tls_init(ctx, p->data, p->data_size);
        if (sz == 0) {
            ERR_raise(ERR_LIB_PROV, PROV_R_INVALID_DATA);
            return 0;
        }
        ctx->tls_aad_pad_sz = sz;
    }

    p = OSSL_PARAM_locate_const(params, OSSL_CIPHER_PARAM_AEAD_TLS1_IV_FIXED);
    if (p != NULL) {
        if (p->data_type != OSSL_PARAM_OCTET_STRING) {
            ERR_raise(ERR_LIB_PROV, PROV_R_FAILED_TO_GET_PARAMETER);
            return 0;
        }
        if (ccm_tls_iv_set_fixed(ctx, p->data, p->data_size) == 0) {
            ERR_raise(ERR_LIB_PROV, PROV_R_INVALID_IVLEN);
            return 0;
        }
    }

    return 1;
}