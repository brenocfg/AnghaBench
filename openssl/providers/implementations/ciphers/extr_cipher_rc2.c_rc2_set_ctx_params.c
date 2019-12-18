#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  iv ;
struct TYPE_13__ {int ivlen; int keylen; } ;
struct TYPE_12__ {unsigned char* data; scalar_t__ data_type; int /*<<< orphan*/  data_size; } ;
struct TYPE_11__ {int key_bits; TYPE_5__ base; } ;
typedef  TYPE_1__ PROV_RC2_CTX ;
typedef  TYPE_2__ OSSL_PARAM ;
typedef  int /*<<< orphan*/  ASN1_TYPE ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_TYPE_free (int /*<<< orphan*/ *) ; 
 scalar_t__ ASN1_TYPE_get_int_octetstring (int /*<<< orphan*/ *,long*,unsigned char*,int) ; 
 int /*<<< orphan*/  ERR_LIB_PROV ; 
 int /*<<< orphan*/  ERR_raise (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSSL_CIPHER_PARAM_ALG_ID ; 
 int /*<<< orphan*/  OSSL_CIPHER_PARAM_RC2_KEYBITS ; 
 scalar_t__ OSSL_PARAM_OCTET_STRING ; 
 int /*<<< orphan*/  OSSL_PARAM_get_size_t (TYPE_2__ const*,int*) ; 
 TYPE_2__* OSSL_PARAM_locate (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* OSSL_PARAM_locate_const (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROV_R_FAILED_TO_GET_PARAMETER ; 
 int /*<<< orphan*/  PROV_R_FAILED_TO_SET_PARAMETER ; 
 int /*<<< orphan*/  cipher_generic_initiv (TYPE_5__*,unsigned char*,size_t) ; 
 int /*<<< orphan*/  cipher_generic_set_ctx_params (void*,TYPE_2__*) ; 
 int /*<<< orphan*/ * d2i_ASN1_TYPE (int /*<<< orphan*/ *,unsigned char const**,int /*<<< orphan*/ ) ; 
 int rc2_magic_to_keybits (long) ; 

__attribute__((used)) static int rc2_set_ctx_params(void *vctx, OSSL_PARAM params[])
{
    PROV_RC2_CTX *ctx = (PROV_RC2_CTX *)vctx;
    const OSSL_PARAM *p;

    if (!cipher_generic_set_ctx_params(vctx, params))
        return 0;
    p = OSSL_PARAM_locate_const(params, OSSL_CIPHER_PARAM_RC2_KEYBITS);
    if (p != NULL) {
         if (!OSSL_PARAM_get_size_t(p, &ctx->key_bits)) {
            ERR_raise(ERR_LIB_PROV, PROV_R_FAILED_TO_GET_PARAMETER);
            return 0;
        }
    }
    p = OSSL_PARAM_locate(params, OSSL_CIPHER_PARAM_ALG_ID);
    if (p != NULL) {
        ASN1_TYPE *type = NULL;
        long num = 0;
        const unsigned char *d = p->data;
        int ret = 1;
        unsigned char iv[16];

        if (p->data_type != OSSL_PARAM_OCTET_STRING
            || ctx->base.ivlen > sizeof(iv)
            || (type = d2i_ASN1_TYPE(NULL, &d, p->data_size)) == NULL
            || ((size_t)ASN1_TYPE_get_int_octetstring(type, &num, iv,
                                                      ctx->base.ivlen)
                != ctx->base.ivlen)
            || !cipher_generic_initiv(&ctx->base, iv, ctx->base.ivlen)
            || (ctx->key_bits = rc2_magic_to_keybits(num)) == 0) {
            ERR_raise(ERR_LIB_PROV, PROV_R_FAILED_TO_SET_PARAMETER);
            ret = 0;
        }
        ASN1_TYPE_free(type);
        if (ret == 0)
            return 0;
        /*
         * This code assumes that the caller will call
         * EVP_CipherInit_ex() with a non NULL key in order to setup a key that
         * uses the keylen and keybits that were set here.
         */
        ctx->base.keylen = ctx->key_bits / 8;
    }
    return 1;
}