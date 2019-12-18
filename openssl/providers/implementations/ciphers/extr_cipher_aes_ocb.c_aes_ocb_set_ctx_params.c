#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ data_type; scalar_t__ data_size; int /*<<< orphan*/ * data; } ;
struct TYPE_8__ {size_t ivlen; size_t keylen; scalar_t__ enc; } ;
struct TYPE_9__ {scalar_t__ taglen; TYPE_1__ base; int /*<<< orphan*/  tag; } ;
typedef  TYPE_2__ PROV_AES_OCB_CTX ;
typedef  TYPE_3__ OSSL_PARAM ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_LIB_PROV ; 
 int /*<<< orphan*/  ERR_raise (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t OCB_MAX_IV_LEN ; 
 scalar_t__ OCB_MAX_TAG_LEN ; 
 size_t OCB_MIN_IV_LEN ; 
 int /*<<< orphan*/  OSSL_CIPHER_PARAM_AEAD_IVLEN ; 
 int /*<<< orphan*/  OSSL_CIPHER_PARAM_AEAD_TAG ; 
 int /*<<< orphan*/  OSSL_CIPHER_PARAM_KEYLEN ; 
 scalar_t__ OSSL_PARAM_OCTET_STRING ; 
 int /*<<< orphan*/  OSSL_PARAM_get_size_t (TYPE_3__ const*,size_t*) ; 
 TYPE_3__* OSSL_PARAM_locate_const (TYPE_3__ const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROV_R_FAILED_TO_GET_PARAMETER ; 
 int /*<<< orphan*/  PROV_R_INVALID_KEY_LENGTH ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static int aes_ocb_set_ctx_params(void *vctx, const OSSL_PARAM params[])
{
    PROV_AES_OCB_CTX *ctx = (PROV_AES_OCB_CTX *)vctx;
    const OSSL_PARAM *p;
    size_t sz;

    p = OSSL_PARAM_locate_const(params, OSSL_CIPHER_PARAM_AEAD_TAG);
    if (p != NULL) {
        if (p->data_type != OSSL_PARAM_OCTET_STRING) {
            ERR_raise(ERR_LIB_PROV, PROV_R_FAILED_TO_GET_PARAMETER);
            return 0;
        }
        if (p->data == NULL) {
            /* Tag len must be 0 to 16 */
            if (p->data_size > OCB_MAX_TAG_LEN)
                return 0;
            ctx->taglen = p->data_size;
        } else {
            if (p->data_size != ctx->taglen || ctx->base.enc)
                return 0;
            memcpy(ctx->tag, p->data, p->data_size);
        }
     }
    p = OSSL_PARAM_locate_const(params, OSSL_CIPHER_PARAM_AEAD_IVLEN);
    if (p != NULL) {
        if (!OSSL_PARAM_get_size_t(p, &sz)) {
            ERR_raise(ERR_LIB_PROV, PROV_R_FAILED_TO_GET_PARAMETER);
            return 0;
        }
        /* IV len must be 1 to 15 */
        if (sz < OCB_MIN_IV_LEN || sz > OCB_MAX_IV_LEN)
            return 0;
        ctx->base.ivlen = sz;
    }
    p = OSSL_PARAM_locate_const(params, OSSL_CIPHER_PARAM_KEYLEN);
    if (p != NULL) {
        size_t keylen;

        if (!OSSL_PARAM_get_size_t(p, &keylen)) {
            ERR_raise(ERR_LIB_PROV, PROV_R_FAILED_TO_GET_PARAMETER);
            return 0;
        }
        if (ctx->base.keylen != keylen) {
            ERR_raise(ERR_LIB_PROV, PROV_R_INVALID_KEY_LENGTH);
            return 0;
        }
    }
    return 1;
}