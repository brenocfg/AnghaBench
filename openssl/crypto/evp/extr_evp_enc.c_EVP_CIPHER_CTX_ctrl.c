#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int (* ctrl ) (TYPE_1__*,int,int,void*) ;int /*<<< orphan*/ * prov; } ;
struct TYPE_6__ {TYPE_3__* cipher; int /*<<< orphan*/  provctx; } ;
typedef  int /*<<< orphan*/  OSSL_PARAM ;
typedef  TYPE_1__ EVP_CIPHER_CTX ;

/* Variables and functions */
#define  EVP_CTRL_AEAD_GET_TAG 143 
#define  EVP_CTRL_AEAD_SET_IVLEN 142 
#define  EVP_CTRL_AEAD_SET_MAC_KEY 141 
#define  EVP_CTRL_AEAD_SET_TAG 140 
#define  EVP_CTRL_AEAD_TLS1_AAD 139 
#define  EVP_CTRL_GCM_SET_IV_FIXED 138 
#define  EVP_CTRL_GET_IV 137 
#define  EVP_CTRL_GET_RC2_KEY_BITS 136 
#define  EVP_CTRL_GET_RC5_ROUNDS 135 
#define  EVP_CTRL_INIT 134 
#define  EVP_CTRL_RAND_KEY 133 
 int EVP_CTRL_RET_UNSUPPORTED ; 
#define  EVP_CTRL_SET_KEY_LENGTH 132 
#define  EVP_CTRL_SET_PIPELINE_OUTPUT_BUFS 131 
#define  EVP_CTRL_SET_RC2_KEY_BITS 130 
#define  EVP_CTRL_SET_RC5_ROUNDS 129 
#define  EVP_CTRL_SET_SPEED 128 
 int /*<<< orphan*/  EVP_F_EVP_CIPHER_CTX_CTRL ; 
 int /*<<< orphan*/  EVP_R_CTRL_NOT_IMPLEMENTED ; 
 int /*<<< orphan*/  EVP_R_CTRL_OPERATION_NOT_IMPLEMENTED ; 
 int /*<<< orphan*/  EVP_R_NO_CIPHER_SET ; 
 int /*<<< orphan*/  EVPerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSSL_CIPHER_PARAM_AEAD_MAC_KEY ; 
 int /*<<< orphan*/  OSSL_CIPHER_PARAM_AEAD_TAG ; 
 int /*<<< orphan*/  OSSL_CIPHER_PARAM_AEAD_TLS1_AAD ; 
 int /*<<< orphan*/  OSSL_CIPHER_PARAM_AEAD_TLS1_AAD_PAD ; 
 int /*<<< orphan*/  OSSL_CIPHER_PARAM_AEAD_TLS1_IV_FIXED ; 
 int /*<<< orphan*/  OSSL_CIPHER_PARAM_IV ; 
 int /*<<< orphan*/  OSSL_CIPHER_PARAM_IVLEN ; 
 int /*<<< orphan*/  OSSL_CIPHER_PARAM_KEYLEN ; 
 int /*<<< orphan*/  OSSL_CIPHER_PARAM_RANDOM_KEY ; 
 int /*<<< orphan*/  OSSL_CIPHER_PARAM_RC2_KEYBITS ; 
 int /*<<< orphan*/  OSSL_CIPHER_PARAM_ROUNDS ; 
 int /*<<< orphan*/  OSSL_CIPHER_PARAM_SPEED ; 
 int /*<<< orphan*/  OSSL_PARAM_END ; 
 int /*<<< orphan*/  OSSL_PARAM_construct_octet_string (int /*<<< orphan*/ ,void*,size_t) ; 
 int /*<<< orphan*/  OSSL_PARAM_construct_size_t (int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  OSSL_PARAM_construct_uint (int /*<<< orphan*/ ,unsigned int*) ; 
 int evp_do_ciph_ctx_getparams (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int evp_do_ciph_ctx_setparams (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int stub1 (TYPE_1__*,int,int,void*) ; 

int EVP_CIPHER_CTX_ctrl(EVP_CIPHER_CTX *ctx, int type, int arg, void *ptr)
{
    int ret = EVP_CTRL_RET_UNSUPPORTED;
    int set_params = 1;
    size_t sz = arg;
    unsigned int i;
    OSSL_PARAM params[2] = { OSSL_PARAM_END, OSSL_PARAM_END };

    if (ctx == NULL || ctx->cipher == NULL) {
        EVPerr(EVP_F_EVP_CIPHER_CTX_CTRL, EVP_R_NO_CIPHER_SET);
        return 0;
    }

    if (ctx->cipher->prov == NULL)
        goto legacy;

    switch (type) {
    case EVP_CTRL_SET_KEY_LENGTH:
        params[0] = OSSL_PARAM_construct_size_t(OSSL_CIPHER_PARAM_KEYLEN, &sz);
        break;
    case EVP_CTRL_RAND_KEY:      /* Used by DES */
        set_params = 0;
        params[0] =
            OSSL_PARAM_construct_octet_string(OSSL_CIPHER_PARAM_RANDOM_KEY,
                                              ptr, sz);
        break;

    case EVP_CTRL_INIT:
        /*
         * TODO(3.0) EVP_CTRL_INIT is purely legacy, no provider counterpart
         * As a matter of fact, this should be dead code, but some caller
         * might still do a direct control call with this command, so...
         * Legacy methods return 1 except for exceptional circumstances, so
         * we do the same here to not be disruptive.
         */
        return 1;
    case EVP_CTRL_SET_PIPELINE_OUTPUT_BUFS: /* Used by DASYNC */
    default:
        goto end;
    case EVP_CTRL_GET_IV:
        set_params = 0;
        params[0] = OSSL_PARAM_construct_octet_string(OSSL_CIPHER_PARAM_IV,
                                                      ptr, sz);
        break;
    case EVP_CTRL_AEAD_SET_IVLEN:
        if (arg < 0)
            return 0;
        params[0] = OSSL_PARAM_construct_size_t(OSSL_CIPHER_PARAM_IVLEN, &sz);
        break;
    case EVP_CTRL_GCM_SET_IV_FIXED:
        params[0] =
            OSSL_PARAM_construct_octet_string(OSSL_CIPHER_PARAM_AEAD_TLS1_IV_FIXED,
                                              ptr, sz);
        break;
    case EVP_CTRL_GET_RC5_ROUNDS:
        set_params = 0; /* Fall thru */
    case EVP_CTRL_SET_RC5_ROUNDS:
        if (arg < 0)
            return 0;
        i = (unsigned int)arg;
        params[0] = OSSL_PARAM_construct_uint(OSSL_CIPHER_PARAM_ROUNDS, &i);
        break;
    case EVP_CTRL_SET_SPEED:
        if (arg < 0)
            return 0;
        i = (unsigned int)arg;
        params[0] = OSSL_PARAM_construct_uint(OSSL_CIPHER_PARAM_SPEED, &i);
        break;
    case EVP_CTRL_AEAD_GET_TAG:
        set_params = 0; /* Fall thru */
    case EVP_CTRL_AEAD_SET_TAG:
        params[0] = OSSL_PARAM_construct_octet_string(OSSL_CIPHER_PARAM_AEAD_TAG,
                                                      ptr, sz);
        break;
    case EVP_CTRL_AEAD_SET_MAC_KEY:
        params[0] =
            OSSL_PARAM_construct_octet_string(OSSL_CIPHER_PARAM_AEAD_MAC_KEY,
                                              ptr, sz);
        break;
    case EVP_CTRL_AEAD_TLS1_AAD:
        /* This one does a set and a get - since it returns a padding size */
        params[0] =
            OSSL_PARAM_construct_octet_string(OSSL_CIPHER_PARAM_AEAD_TLS1_AAD,
                                              ptr, sz);
        ret = evp_do_ciph_ctx_setparams(ctx->cipher, ctx->provctx, params);
        if (ret <= 0)
            goto end;
        params[0] =
            OSSL_PARAM_construct_size_t(OSSL_CIPHER_PARAM_AEAD_TLS1_AAD_PAD, &sz);
        ret = evp_do_ciph_ctx_getparams(ctx->cipher, ctx->provctx, params);
        if (ret <= 0)
            goto end;
        return sz;
#ifndef OPENSSL_NO_RC2
    case EVP_CTRL_GET_RC2_KEY_BITS:
        set_params = 0; /* Fall thru */
    case EVP_CTRL_SET_RC2_KEY_BITS:
        params[0] = OSSL_PARAM_construct_size_t(OSSL_CIPHER_PARAM_RC2_KEYBITS, &sz);
        break;
#endif /* OPENSSL_NO_RC2 */
    }

    if (set_params)
        ret = evp_do_ciph_ctx_setparams(ctx->cipher, ctx->provctx, params);
    else
        ret = evp_do_ciph_ctx_getparams(ctx->cipher, ctx->provctx, params);
    goto end;

/* TODO(3.0): Remove legacy code below */
legacy:
    if (ctx->cipher->ctrl == NULL) {
        EVPerr(EVP_F_EVP_CIPHER_CTX_CTRL, EVP_R_CTRL_NOT_IMPLEMENTED);
        return 0;
    }

    ret = ctx->cipher->ctrl(ctx, type, arg, ptr);

 end:
    if (ret == EVP_CTRL_RET_UNSUPPORTED) {
        EVPerr(EVP_F_EVP_CIPHER_CTX_CTRL,
               EVP_R_CTRL_OPERATION_NOT_IMPLEMENTED);
        return 0;
    }
    return ret;
}