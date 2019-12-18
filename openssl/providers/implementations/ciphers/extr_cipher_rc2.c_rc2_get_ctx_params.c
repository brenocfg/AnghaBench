#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {unsigned char* data; scalar_t__ data_type; size_t return_size; } ;
struct TYPE_9__ {int /*<<< orphan*/  ivlen; int /*<<< orphan*/  iv; } ;
struct TYPE_10__ {TYPE_1__ base; int /*<<< orphan*/  key_bits; } ;
typedef  TYPE_2__ PROV_RC2_CTX ;
typedef  TYPE_3__ OSSL_PARAM ;
typedef  int /*<<< orphan*/  ASN1_TYPE ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_TYPE_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ASN1_TYPE_new () ; 
 int /*<<< orphan*/  ASN1_TYPE_set_int_octetstring (int /*<<< orphan*/ *,long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_LIB_PROV ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  ERR_raise (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSSL_CIPHER_PARAM_ALG_ID ; 
 int /*<<< orphan*/  OSSL_CIPHER_PARAM_RC2_KEYBITS ; 
 scalar_t__ OSSL_PARAM_OCTET_STRING ; 
 TYPE_3__* OSSL_PARAM_locate (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSSL_PARAM_set_size_t (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROV_R_FAILED_TO_SET_PARAMETER ; 
 int /*<<< orphan*/  cipher_generic_get_ctx_params (void*,TYPE_3__*) ; 
 int i2d_ASN1_TYPE (int /*<<< orphan*/ *,unsigned char**) ; 
 long rc2_keybits_to_magic (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rc2_get_ctx_params(void *vctx, OSSL_PARAM params[])
{
    PROV_RC2_CTX *ctx = (PROV_RC2_CTX *)vctx;
    OSSL_PARAM *p;

    if (!cipher_generic_get_ctx_params(vctx, params))
        return 0;
    p = OSSL_PARAM_locate(params, OSSL_CIPHER_PARAM_RC2_KEYBITS);
    if (p != NULL && !OSSL_PARAM_set_size_t(p, ctx->key_bits)) {
        ERR_raise(ERR_LIB_PROV, PROV_R_FAILED_TO_SET_PARAMETER);
        return 0;
    }
    p = OSSL_PARAM_locate(params, OSSL_CIPHER_PARAM_ALG_ID);
    if (p != NULL) {
        long num;
        int i;
        ASN1_TYPE *type;
        unsigned char *d = p->data;
        unsigned char **dd = d == NULL ? NULL : &d;

        if (p->data_type != OSSL_PARAM_OCTET_STRING) {
            ERR_raise(ERR_LIB_PROV, PROV_R_FAILED_TO_SET_PARAMETER);
            return 0;
        }
        if ((type = ASN1_TYPE_new()) == NULL) {
            ERR_raise(ERR_LIB_PROV, ERR_R_MALLOC_FAILURE);
            return 0;
        }

        /* Is this the original IV or the running IV? */
        num = rc2_keybits_to_magic(ctx->key_bits);
        if (!ASN1_TYPE_set_int_octetstring(type, num,
                                           ctx->base.iv, ctx->base.ivlen)) {
            ASN1_TYPE_free(type);
            ERR_raise(ERR_LIB_PROV, ERR_R_MALLOC_FAILURE);
            return 0;
        }
        /*
         * IF the caller has a buffer, we pray to the gods they got the
         * size right.  There's no way to tell the i2d functions...
         */
        i = i2d_ASN1_TYPE(type, dd);
        if (i >= 0)
            p->return_size = (size_t)i;

        ASN1_TYPE_free(type);
        if (i < 0) {
            ERR_raise(ERR_LIB_PROV, PROV_R_FAILED_TO_SET_PARAMETER);
            return 0;
        }
    }
    return 1;
}