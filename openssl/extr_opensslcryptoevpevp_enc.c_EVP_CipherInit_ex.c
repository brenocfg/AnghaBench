#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {scalar_t__ nid; int (* einit ) (int /*<<< orphan*/ *,unsigned char const*,int /*<<< orphan*/ ,unsigned char const*,int) ;int (* dinit ) (int /*<<< orphan*/ *,unsigned char const*,int /*<<< orphan*/ ,unsigned char const*,int) ;int flags; int block_size; int /*<<< orphan*/  (* init ) (TYPE_1__*,unsigned char const*,unsigned char const*,int) ;int /*<<< orphan*/  key_len; scalar_t__ ctx_size; int /*<<< orphan*/ * prov; int /*<<< orphan*/ * (* newctx ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_17__ {int encrypt; unsigned long flags; unsigned char const* oiv; unsigned char const* iv; int block_mask; TYPE_2__ const* cipher; scalar_t__ final_used; scalar_t__ buf_len; int /*<<< orphan*/  num; int /*<<< orphan*/  key_len; int /*<<< orphan*/ * cipher_data; int /*<<< orphan*/ * engine; int /*<<< orphan*/ * provctx; TYPE_2__ const* fetched_cipher; } ;
typedef  TYPE_1__ EVP_CIPHER_CTX ;
typedef  TYPE_2__ const EVP_CIPHER ;
typedef  int /*<<< orphan*/  ENGINE ;

/* Variables and functions */
 TYPE_2__ const* ENGINE_get_cipher (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * ENGINE_get_cipher_engine (scalar_t__) ; 
 int /*<<< orphan*/  ENGINE_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int EVP_CIPHER_CTX_FLAG_WRAP_ALLOW ; 
 int /*<<< orphan*/  EVP_CIPHER_CTX_cipher (TYPE_1__*) ; 
 int /*<<< orphan*/  EVP_CIPHER_CTX_ctrl (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int EVP_CIPHER_CTX_iv_length (TYPE_1__*) ; 
 int /*<<< orphan*/  EVP_CIPHER_CTX_key_length (TYPE_1__*) ; 
 int EVP_CIPHER_CTX_mode (TYPE_1__*) ; 
 int /*<<< orphan*/  EVP_CIPHER_CTX_reset (TYPE_1__*) ; 
 int /*<<< orphan*/  EVP_CIPHER_CTX_set_padding (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_2__ const* EVP_CIPHER_fetch (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int EVP_CIPHER_flags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_CIPHER_meth_free (TYPE_2__ const*) ; 
 int EVP_CIPHER_mode (TYPE_2__ const*) ; 
 int EVP_CIPH_ALWAYS_CALL_INIT ; 
#define  EVP_CIPH_CBC_MODE 154 
#define  EVP_CIPH_CFB_MODE 153 
 int EVP_CIPH_CTRL_INIT ; 
#define  EVP_CIPH_CTR_MODE 152 
 int EVP_CIPH_CUSTOM_IV ; 
#define  EVP_CIPH_ECB_MODE 151 
 int EVP_CIPH_NO_PADDING ; 
#define  EVP_CIPH_OFB_MODE 150 
#define  EVP_CIPH_STREAM_CIPHER 149 
 int EVP_CIPH_WRAP_MODE ; 
 int /*<<< orphan*/  EVP_CTRL_INIT ; 
 int /*<<< orphan*/  EVP_F_EVP_CIPHERINIT_EX ; 
 int /*<<< orphan*/  EVP_R_INITIALIZATION_ERROR ; 
 int /*<<< orphan*/  EVP_R_NO_CIPHER_SET ; 
 int /*<<< orphan*/  EVP_R_WRAP_MODE_NOT_ALLOWED ; 
 int /*<<< orphan*/  EVPerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  NID_aes_128_cbc 148 
#define  NID_aes_128_cfb1 147 
#define  NID_aes_128_cfb128 146 
#define  NID_aes_128_cfb8 145 
#define  NID_aes_128_ctr 144 
#define  NID_aes_128_ecb 143 
#define  NID_aes_128_ofb128 142 
#define  NID_aes_192_cbc 141 
#define  NID_aes_192_cfb1 140 
#define  NID_aes_192_cfb128 139 
#define  NID_aes_192_cfb8 138 
#define  NID_aes_192_ctr 137 
#define  NID_aes_192_ecb 136 
#define  NID_aes_192_ofb128 135 
#define  NID_aes_256_cbc 134 
#define  NID_aes_256_cfb1 133 
#define  NID_aes_256_cfb128 132 
#define  NID_aes_256_cfb8 131 
#define  NID_aes_256_ctr 130 
#define  NID_aes_256_ecb 129 
#define  NID_aes_256_ofb128 128 
 int /*<<< orphan*/  OBJ_nid2sn (int) ; 
 int /*<<< orphan*/  OPENSSL_assert (int) ; 
 int /*<<< orphan*/  OPENSSL_clear_free (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/ * OPENSSL_zalloc (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (unsigned char const*,unsigned char const*,int) ; 
 int /*<<< orphan*/  ossl_assert (int) ; 
 int /*<<< orphan*/  ossl_provider_ctx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ ) ; 
 int stub2 (int /*<<< orphan*/ *,unsigned char const*,int /*<<< orphan*/ ,unsigned char const*,int) ; 
 int stub3 (int /*<<< orphan*/ *,unsigned char const*,int /*<<< orphan*/ ,unsigned char const*,int) ; 
 int /*<<< orphan*/  stub4 (TYPE_1__*,unsigned char const*,unsigned char const*,int) ; 

int EVP_CipherInit_ex(EVP_CIPHER_CTX *ctx, const EVP_CIPHER *cipher,
                      ENGINE *impl, const unsigned char *key,
                      const unsigned char *iv, int enc)
{
    EVP_CIPHER *provciph = NULL;
    ENGINE *tmpimpl = NULL;
    const EVP_CIPHER *tmpcipher;

    /*
     * enc == 1 means we are encrypting.
     * enc == 0 means we are decrypting.
     * enc == -1 means, use the previously initialised value for encrypt/decrypt
     */
    if (enc == -1) {
        enc = ctx->encrypt;
    } else {
        if (enc)
            enc = 1;
        ctx->encrypt = enc;
    }

    if (cipher == NULL && ctx->cipher == NULL) {
        EVPerr(EVP_F_EVP_CIPHERINIT_EX, EVP_R_NO_CIPHER_SET);
        return 0;
    }

    /* TODO(3.0): Legacy work around code below. Remove this */

#ifndef OPENSSL_NO_ENGINE
    /*
     * Whether it's nice or not, "Inits" can be used on "Final"'d contexts so
     * this context may already have an ENGINE! Try to avoid releasing the
     * previous handle, re-querying for an ENGINE, and having a
     * reinitialisation, when it may all be unnecessary.
     */
    if (ctx->engine && ctx->cipher
        && (cipher == NULL || cipher->nid == ctx->cipher->nid))
        goto skip_to_init;

    if (cipher != NULL && impl == NULL) {
         /* Ask if an ENGINE is reserved for this job */
        tmpimpl = ENGINE_get_cipher_engine(cipher->nid);
    }
#endif

    /*
     * If there are engines involved then we should use legacy handling for now.
     */
    if (ctx->engine != NULL
            || impl != NULL
            || tmpimpl != NULL) {
        if (ctx->cipher == ctx->fetched_cipher)
            ctx->cipher = NULL;
        EVP_CIPHER_meth_free(ctx->fetched_cipher);
        ctx->fetched_cipher = NULL;
        goto legacy;
    }

    tmpcipher = (cipher == NULL) ? ctx->cipher : cipher;

    if (tmpcipher->prov == NULL) {
        switch(tmpcipher->nid) {
        case NID_aes_256_ecb:
        case NID_aes_192_ecb:
        case NID_aes_128_ecb:
        case NID_aes_256_cbc:
        case NID_aes_192_cbc:
        case NID_aes_128_cbc:
        case NID_aes_256_ofb128:
        case NID_aes_192_ofb128:
        case NID_aes_128_ofb128:
        case NID_aes_256_cfb128:
        case NID_aes_192_cfb128:
        case NID_aes_128_cfb128:
        case NID_aes_256_cfb1:
        case NID_aes_192_cfb1:
        case NID_aes_128_cfb1:
        case NID_aes_256_cfb8:
        case NID_aes_192_cfb8:
        case NID_aes_128_cfb8:
        case NID_aes_256_ctr:
        case NID_aes_192_ctr:
        case NID_aes_128_ctr:
            break;
        default:
            goto legacy;
        }
    }

    /*
     * Ensure a context left lying around from last time is cleared
     * (legacy code)
     */
    if (cipher != NULL && ctx->cipher != NULL) {
        OPENSSL_clear_free(ctx->cipher_data, ctx->cipher->ctx_size);
        ctx->cipher_data = NULL;
    }


    /* TODO(3.0): Start of non-legacy code below */

    /* Ensure a context left lying around from last time is cleared */
    if (cipher != NULL && ctx->cipher != NULL) {
        unsigned long flags = ctx->flags;

        EVP_CIPHER_CTX_reset(ctx);
        /* Restore encrypt and flags */
        ctx->encrypt = enc;
        ctx->flags = flags;
    }

    if (cipher != NULL)
        ctx->cipher = cipher;
    else
        cipher = ctx->cipher;

    if (cipher->prov == NULL) {
        provciph = EVP_CIPHER_fetch(NULL, OBJ_nid2sn(cipher->nid), "");
        if (provciph == NULL) {
            EVPerr(EVP_F_EVP_CIPHERINIT_EX, EVP_R_INITIALIZATION_ERROR);
            return 0;
        }
        cipher = provciph;
        EVP_CIPHER_meth_free(ctx->fetched_cipher);
        ctx->fetched_cipher = provciph;
    }

    ctx->cipher = cipher;
    if (ctx->provctx == NULL) {
        ctx->provctx = ctx->cipher->newctx(ossl_provider_ctx(cipher->prov));
        if (ctx->provctx == NULL) {
            EVPerr(EVP_F_EVP_CIPHERINIT_EX, EVP_R_INITIALIZATION_ERROR);
            return 0;
        }
    }

    if ((ctx->flags & EVP_CIPH_NO_PADDING) != 0) {
        /*
         * If this ctx was already set up for no padding then we need to tell
         * the new cipher about it.
         */
        if (!EVP_CIPHER_CTX_set_padding(ctx, 0))
            return 0;
    }

    switch (EVP_CIPHER_mode(ctx->cipher)) {
    case EVP_CIPH_CFB_MODE:
    case EVP_CIPH_OFB_MODE:
    case EVP_CIPH_CBC_MODE:
        /* For these modes we remember the original IV for later use */
        if (!ossl_assert(EVP_CIPHER_CTX_iv_length(ctx) <= (int)sizeof(ctx->oiv))) {
            EVPerr(EVP_F_EVP_CIPHERINIT_EX, EVP_R_INITIALIZATION_ERROR);
            return 0;
        }
        if (iv != NULL)
            memcpy(ctx->oiv, iv, EVP_CIPHER_CTX_iv_length(ctx));
    }

    if (enc) {
        if (ctx->cipher->einit == NULL) {
            EVPerr(EVP_F_EVP_CIPHERINIT_EX, EVP_R_INITIALIZATION_ERROR);
            return 0;
        }

        return ctx->cipher->einit(ctx->provctx,
                                  key,
                                  key == NULL ? 0
                                              : EVP_CIPHER_CTX_key_length(ctx),
                                  iv,
                                  iv == NULL ? 0
                                             : EVP_CIPHER_CTX_iv_length(ctx));
    }

    if (ctx->cipher->dinit == NULL) {
        EVPerr(EVP_F_EVP_CIPHERINIT_EX, EVP_R_INITIALIZATION_ERROR);
        return 0;
    }

    return ctx->cipher->dinit(ctx->provctx,
                              key,
                              key == NULL ? 0
                                          : EVP_CIPHER_CTX_key_length(ctx),
                              iv,
                              iv == NULL ? 0
                                         : EVP_CIPHER_CTX_iv_length(ctx));

    /* TODO(3.0): Remove legacy code below */
 legacy:

    if (cipher != NULL) {
        /*
         * Ensure a context left lying around from last time is cleared (we
         * previously attempted to avoid this if the same ENGINE and
         * EVP_CIPHER could be used).
         */
        if (ctx->cipher) {
            unsigned long flags = ctx->flags;
            EVP_CIPHER_CTX_reset(ctx);
            /* Restore encrypt and flags */
            ctx->encrypt = enc;
            ctx->flags = flags;
        }
#ifndef OPENSSL_NO_ENGINE
        if (impl != NULL) {
            if (!ENGINE_init(impl)) {
                EVPerr(EVP_F_EVP_CIPHERINIT_EX, EVP_R_INITIALIZATION_ERROR);
                return 0;
            }
        } else {
            impl = tmpimpl;
        }
        if (impl != NULL) {
            /* There's an ENGINE for this job ... (apparently) */
            const EVP_CIPHER *c = ENGINE_get_cipher(impl, cipher->nid);

            if (c == NULL) {
                /*
                 * One positive side-effect of US's export control history,
                 * is that we should at least be able to avoid using US
                 * misspellings of "initialisation"?
                 */
                EVPerr(EVP_F_EVP_CIPHERINIT_EX, EVP_R_INITIALIZATION_ERROR);
                return 0;
            }
            /* We'll use the ENGINE's private cipher definition */
            cipher = c;
            /*
             * Store the ENGINE functional reference so we know 'cipher' came
             * from an ENGINE and we need to release it when done.
             */
            ctx->engine = impl;
        } else {
            ctx->engine = NULL;
        }
#endif

        ctx->cipher = cipher;
        if (ctx->cipher->ctx_size) {
            ctx->cipher_data = OPENSSL_zalloc(ctx->cipher->ctx_size);
            if (ctx->cipher_data == NULL) {
                ctx->cipher = NULL;
                EVPerr(EVP_F_EVP_CIPHERINIT_EX, ERR_R_MALLOC_FAILURE);
                return 0;
            }
        } else {
            ctx->cipher_data = NULL;
        }
        ctx->key_len = cipher->key_len;
        /* Preserve wrap enable flag, zero everything else */
        ctx->flags &= EVP_CIPHER_CTX_FLAG_WRAP_ALLOW;
        if (ctx->cipher->flags & EVP_CIPH_CTRL_INIT) {
            if (!EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_INIT, 0, NULL)) {
                ctx->cipher = NULL;
                EVPerr(EVP_F_EVP_CIPHERINIT_EX, EVP_R_INITIALIZATION_ERROR);
                return 0;
            }
        }
    }
#ifndef OPENSSL_NO_ENGINE
 skip_to_init:
#endif
    /* we assume block size is a power of 2 in *cryptUpdate */
    OPENSSL_assert(ctx->cipher->block_size == 1
                   || ctx->cipher->block_size == 8
                   || ctx->cipher->block_size == 16);

    if (!(ctx->flags & EVP_CIPHER_CTX_FLAG_WRAP_ALLOW)
        && EVP_CIPHER_CTX_mode(ctx) == EVP_CIPH_WRAP_MODE) {
        EVPerr(EVP_F_EVP_CIPHERINIT_EX, EVP_R_WRAP_MODE_NOT_ALLOWED);
        return 0;
    }

    if (!(EVP_CIPHER_flags(EVP_CIPHER_CTX_cipher(ctx)) & EVP_CIPH_CUSTOM_IV)) {
        switch (EVP_CIPHER_CTX_mode(ctx)) {

        case EVP_CIPH_STREAM_CIPHER:
        case EVP_CIPH_ECB_MODE:
            break;

        case EVP_CIPH_CFB_MODE:
        case EVP_CIPH_OFB_MODE:

            ctx->num = 0;
            /* fall-through */

        case EVP_CIPH_CBC_MODE:

            OPENSSL_assert(EVP_CIPHER_CTX_iv_length(ctx) <=
                           (int)sizeof(ctx->iv));
            if (iv)
                memcpy(ctx->oiv, iv, EVP_CIPHER_CTX_iv_length(ctx));
            memcpy(ctx->iv, ctx->oiv, EVP_CIPHER_CTX_iv_length(ctx));
            break;

        case EVP_CIPH_CTR_MODE:
            ctx->num = 0;
            /* Don't reuse IV for CTR mode */
            if (iv)
                memcpy(ctx->iv, iv, EVP_CIPHER_CTX_iv_length(ctx));
            break;

        default:
            return 0;
        }
    }

    if (key || (ctx->cipher->flags & EVP_CIPH_ALWAYS_CALL_INIT)) {
        if (!ctx->cipher->init(ctx, key, iv, enc))
            return 0;
    }
    ctx->buf_len = 0;
    ctx->final_used = 0;
    ctx->block_mask = ctx->cipher->block_size - 1;
    return 1;
}