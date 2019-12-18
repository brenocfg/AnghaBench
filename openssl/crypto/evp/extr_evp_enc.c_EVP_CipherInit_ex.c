#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {scalar_t__ nid; int (* einit ) (int /*<<< orphan*/ *,unsigned char const*,int /*<<< orphan*/ ,unsigned char const*,int) ;int (* dinit ) (int /*<<< orphan*/ *,unsigned char const*,int /*<<< orphan*/ ,unsigned char const*,int) ;int flags; int block_size; int /*<<< orphan*/  (* init ) (TYPE_1__*,unsigned char const*,unsigned char const*,int) ;int /*<<< orphan*/  key_len; scalar_t__ ctx_size; int /*<<< orphan*/ * prov; int /*<<< orphan*/ * (* newctx ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_16__ {int encrypt; unsigned long flags; unsigned char const* oiv; unsigned char const* iv; int block_mask; TYPE_2__ const* cipher; scalar_t__ final_used; scalar_t__ buf_len; int /*<<< orphan*/  num; int /*<<< orphan*/  key_len; int /*<<< orphan*/ * cipher_data; int /*<<< orphan*/ * engine; int /*<<< orphan*/ * provctx; TYPE_2__ const* fetched_cipher; } ;
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
 int /*<<< orphan*/  EVP_CIPHER_free (TYPE_2__ const*) ; 
 int EVP_CIPH_ALWAYS_CALL_INIT ; 
#define  EVP_CIPH_CBC_MODE 275 
#define  EVP_CIPH_CFB_MODE 274 
 int EVP_CIPH_CTRL_INIT ; 
#define  EVP_CIPH_CTR_MODE 273 
 int EVP_CIPH_CUSTOM_IV ; 
#define  EVP_CIPH_ECB_MODE 272 
 int EVP_CIPH_NO_PADDING ; 
#define  EVP_CIPH_OFB_MODE 271 
#define  EVP_CIPH_STREAM_CIPHER 270 
 int EVP_CIPH_WRAP_MODE ; 
 int /*<<< orphan*/  EVP_CTRL_INIT ; 
 int /*<<< orphan*/  EVP_F_EVP_CIPHERINIT_EX ; 
 int /*<<< orphan*/  EVP_R_INITIALIZATION_ERROR ; 
 int /*<<< orphan*/  EVP_R_NO_CIPHER_SET ; 
 int /*<<< orphan*/  EVP_R_WRAP_MODE_NOT_ALLOWED ; 
 int /*<<< orphan*/  EVPerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  NID_aes_128_cbc 269 
#define  NID_aes_128_ccm 268 
#define  NID_aes_128_cfb1 267 
#define  NID_aes_128_cfb128 266 
#define  NID_aes_128_cfb8 265 
#define  NID_aes_128_ctr 264 
#define  NID_aes_128_ecb 263 
#define  NID_aes_128_gcm 262 
#define  NID_aes_128_ocb 261 
#define  NID_aes_128_ofb128 260 
#define  NID_aes_128_siv 259 
#define  NID_aes_128_xts 258 
#define  NID_aes_192_cbc 257 
#define  NID_aes_192_ccm 256 
#define  NID_aes_192_cfb1 255 
#define  NID_aes_192_cfb128 254 
#define  NID_aes_192_cfb8 253 
#define  NID_aes_192_ctr 252 
#define  NID_aes_192_ecb 251 
#define  NID_aes_192_gcm 250 
#define  NID_aes_192_ocb 249 
#define  NID_aes_192_ofb128 248 
#define  NID_aes_192_siv 247 
#define  NID_aes_256_cbc 246 
#define  NID_aes_256_ccm 245 
#define  NID_aes_256_cfb1 244 
#define  NID_aes_256_cfb128 243 
#define  NID_aes_256_cfb8 242 
#define  NID_aes_256_ctr 241 
#define  NID_aes_256_ecb 240 
#define  NID_aes_256_gcm 239 
#define  NID_aes_256_ocb 238 
#define  NID_aes_256_ofb128 237 
#define  NID_aes_256_siv 236 
#define  NID_aes_256_xts 235 
#define  NID_aria_128_cbc 234 
#define  NID_aria_128_ccm 233 
#define  NID_aria_128_cfb1 232 
#define  NID_aria_128_cfb128 231 
#define  NID_aria_128_cfb8 230 
#define  NID_aria_128_ctr 229 
#define  NID_aria_128_ecb 228 
#define  NID_aria_128_gcm 227 
#define  NID_aria_128_ofb128 226 
#define  NID_aria_192_cbc 225 
#define  NID_aria_192_ccm 224 
#define  NID_aria_192_cfb1 223 
#define  NID_aria_192_cfb128 222 
#define  NID_aria_192_cfb8 221 
#define  NID_aria_192_ctr 220 
#define  NID_aria_192_ecb 219 
#define  NID_aria_192_gcm 218 
#define  NID_aria_192_ofb128 217 
#define  NID_aria_256_cbc 216 
#define  NID_aria_256_ccm 215 
#define  NID_aria_256_cfb1 214 
#define  NID_aria_256_cfb128 213 
#define  NID_aria_256_cfb8 212 
#define  NID_aria_256_ctr 211 
#define  NID_aria_256_ecb 210 
#define  NID_aria_256_gcm 209 
#define  NID_aria_256_ofb128 208 
#define  NID_bf_cbc 207 
#define  NID_bf_cfb64 206 
#define  NID_bf_ecb 205 
#define  NID_bf_ofb64 204 
#define  NID_camellia_128_cbc 203 
#define  NID_camellia_128_cfb1 202 
#define  NID_camellia_128_cfb128 201 
#define  NID_camellia_128_cfb8 200 
#define  NID_camellia_128_ctr 199 
#define  NID_camellia_128_ecb 198 
#define  NID_camellia_128_ofb128 197 
#define  NID_camellia_192_cbc 196 
#define  NID_camellia_192_cfb1 195 
#define  NID_camellia_192_cfb128 194 
#define  NID_camellia_192_cfb8 193 
#define  NID_camellia_192_ctr 192 
#define  NID_camellia_192_ecb 191 
#define  NID_camellia_192_ofb128 190 
#define  NID_camellia_256_cbc 189 
#define  NID_camellia_256_cfb1 188 
#define  NID_camellia_256_cfb128 187 
#define  NID_camellia_256_cfb8 186 
#define  NID_camellia_256_ctr 185 
#define  NID_camellia_256_ecb 184 
#define  NID_camellia_256_ofb128 183 
#define  NID_cast5_cbc 182 
#define  NID_cast5_cfb64 181 
#define  NID_cast5_ecb 180 
#define  NID_cast5_ofb64 179 
#define  NID_chacha20 178 
#define  NID_chacha20_poly1305 177 
#define  NID_des_cbc 176 
#define  NID_des_cfb1 175 
#define  NID_des_cfb64 174 
#define  NID_des_cfb8 173 
#define  NID_des_ecb 172 
#define  NID_des_ede3_cbc 171 
#define  NID_des_ede3_cfb1 170 
#define  NID_des_ede3_cfb64 169 
#define  NID_des_ede3_cfb8 168 
#define  NID_des_ede3_ecb 167 
#define  NID_des_ede3_ofb64 166 
#define  NID_des_ede_cbc 165 
#define  NID_des_ede_cfb64 164 
#define  NID_des_ede_ecb 163 
#define  NID_des_ede_ofb64 162 
#define  NID_des_ofb64 161 
#define  NID_desx_cbc 160 
#define  NID_id_aes128_wrap 159 
#define  NID_id_aes128_wrap_pad 158 
#define  NID_id_aes192_wrap 157 
#define  NID_id_aes192_wrap_pad 156 
#define  NID_id_aes256_wrap 155 
#define  NID_id_aes256_wrap_pad 154 
#define  NID_id_smime_alg_CMS3DESwrap 153 
#define  NID_idea_cbc 152 
#define  NID_idea_cfb64 151 
#define  NID_idea_ecb 150 
#define  NID_idea_ofb64 149 
#define  NID_rc2_40_cbc 148 
#define  NID_rc2_64_cbc 147 
#define  NID_rc2_cbc 146 
#define  NID_rc2_cfb64 145 
#define  NID_rc2_ofb64 144 
#define  NID_rc4 143 
#define  NID_rc4_40 142 
#define  NID_rc4_hmac_md5 141 
#define  NID_rc5_cbc 140 
#define  NID_rc5_cfb64 139 
#define  NID_rc5_ecb 138 
#define  NID_rc5_ofb64 137 
#define  NID_seed_cbc 136 
#define  NID_seed_cfb128 135 
#define  NID_seed_ecb 134 
#define  NID_seed_ofb128 133 
#define  NID_sm4_cbc 132 
#define  NID_sm4_cfb128 131 
#define  NID_sm4_ctr 130 
#define  NID_sm4_ecb 129 
#define  NID_sm4_ofb128 128 
 int /*<<< orphan*/  OBJ_nid2sn (int) ; 
 int /*<<< orphan*/  OPENSSL_assert (int) ; 
 int /*<<< orphan*/  OPENSSL_clear_free (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/ * OPENSSL_zalloc (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (unsigned char const*,unsigned char const*,int) ; 
 int /*<<< orphan*/  ossl_provider_ctx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ ) ; 
 int stub2 (int /*<<< orphan*/ *,unsigned char const*,int /*<<< orphan*/ ,unsigned char const*,int) ; 
 int stub3 (int /*<<< orphan*/ *,unsigned char const*,int /*<<< orphan*/ ,unsigned char const*,int) ; 
 int /*<<< orphan*/  stub4 (TYPE_1__*,unsigned char const*,unsigned char const*,int) ; 

int EVP_CipherInit_ex(EVP_CIPHER_CTX *ctx, const EVP_CIPHER *cipher,
                      ENGINE *impl, const unsigned char *key,
                      const unsigned char *iv, int enc)
{
#if !defined(OPENSSL_NO_ENGINE) && !defined(FIPS_MODE)
    ENGINE *tmpimpl = NULL;
#endif
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

#if !defined(OPENSSL_NO_ENGINE) && !defined(FIPS_MODE)
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
#if !defined(OPENSSL_NO_ENGINE) && !defined(FIPS_MODE)
            || tmpimpl != NULL
#endif
            || impl != NULL) {
        if (ctx->cipher == ctx->fetched_cipher)
            ctx->cipher = NULL;
        EVP_CIPHER_free(ctx->fetched_cipher);
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
        case NID_aes_128_xts:
        case NID_aes_256_xts:
        case NID_aes_256_ocb:
        case NID_aes_192_ocb:
        case NID_aes_128_ocb:
        case NID_aes_256_gcm:
        case NID_aes_192_gcm:
        case NID_aes_128_gcm:
        case NID_aes_256_siv:
        case NID_aes_192_siv:
        case NID_aes_128_siv:
        case NID_id_aes256_wrap:
        case NID_id_aes256_wrap_pad:
        case NID_id_aes192_wrap:
        case NID_id_aes192_wrap_pad:
        case NID_id_aes128_wrap:
        case NID_id_aes128_wrap_pad:
        case NID_aria_256_gcm:
        case NID_aria_192_gcm:
        case NID_aria_128_gcm:
        case NID_aes_256_ccm:
        case NID_aes_192_ccm:
        case NID_aes_128_ccm:
        case NID_aria_256_ccm:
        case NID_aria_192_ccm:
        case NID_aria_128_ccm:
        case NID_aria_256_ecb:
        case NID_aria_192_ecb:
        case NID_aria_128_ecb:
        case NID_aria_256_cbc:
        case NID_aria_192_cbc:
        case NID_aria_128_cbc:
        case NID_aria_256_ofb128:
        case NID_aria_192_ofb128:
        case NID_aria_128_ofb128:
        case NID_aria_256_cfb128:
        case NID_aria_192_cfb128:
        case NID_aria_128_cfb128:
        case NID_aria_256_cfb1:
        case NID_aria_192_cfb1:
        case NID_aria_128_cfb1:
        case NID_aria_256_cfb8:
        case NID_aria_192_cfb8:
        case NID_aria_128_cfb8:
        case NID_aria_256_ctr:
        case NID_aria_192_ctr:
        case NID_aria_128_ctr:
        case NID_camellia_256_ecb:
        case NID_camellia_192_ecb:
        case NID_camellia_128_ecb:
        case NID_camellia_256_cbc:
        case NID_camellia_192_cbc:
        case NID_camellia_128_cbc:
        case NID_camellia_256_ofb128:
        case NID_camellia_192_ofb128:
        case NID_camellia_128_ofb128:
        case NID_camellia_256_cfb128:
        case NID_camellia_192_cfb128:
        case NID_camellia_128_cfb128:
        case NID_camellia_256_cfb1:
        case NID_camellia_192_cfb1:
        case NID_camellia_128_cfb1:
        case NID_camellia_256_cfb8:
        case NID_camellia_192_cfb8:
        case NID_camellia_128_cfb8:
        case NID_camellia_256_ctr:
        case NID_camellia_192_ctr:
        case NID_camellia_128_ctr:
        case NID_des_ede3_cbc:
        case NID_des_ede3_ecb:
        case NID_des_ede3_ofb64:
        case NID_des_ede3_cfb64:
        case NID_des_ede3_cfb8:
        case NID_des_ede3_cfb1:
        case NID_des_ede_cbc:
        case NID_des_ede_ecb:
        case NID_des_ede_ofb64:
        case NID_des_ede_cfb64:
        case NID_desx_cbc:
        case NID_des_cbc:
        case NID_des_ecb:
        case NID_des_cfb1:
        case NID_des_cfb8:
        case NID_des_cfb64:
        case NID_des_ofb64:
        case NID_id_smime_alg_CMS3DESwrap:
        case NID_bf_cbc:
        case NID_bf_ecb:
        case NID_bf_cfb64:
        case NID_bf_ofb64:
        case NID_idea_cbc:
        case NID_idea_ecb:
        case NID_idea_cfb64:
        case NID_idea_ofb64:
        case NID_cast5_cbc:
        case NID_cast5_ecb:
        case NID_cast5_cfb64:
        case NID_cast5_ofb64:
        case NID_seed_cbc:
        case NID_seed_ecb:
        case NID_seed_cfb128:
        case NID_seed_ofb128:
        case NID_sm4_cbc:
        case NID_sm4_ecb:
        case NID_sm4_ctr:
        case NID_sm4_cfb128:
        case NID_sm4_ofb128:
        case NID_rc4:
        case NID_rc4_40:
        case NID_rc5_cbc:
        case NID_rc5_ecb:
        case NID_rc5_cfb64:
        case NID_rc5_ofb64:
        case NID_rc2_cbc:
        case NID_rc2_40_cbc:
        case NID_rc2_64_cbc:
        case NID_rc2_cfb64:
        case NID_rc2_ofb64:
        case NID_chacha20:
        case NID_chacha20_poly1305:
        case NID_rc4_hmac_md5:
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

    if (cipher == NULL)
        cipher = ctx->cipher;

    if (cipher->prov == NULL) {
#ifdef FIPS_MODE
        /* We only do explict fetches inside the FIPS module */
        EVPerr(EVP_F_EVP_CIPHERINIT_EX, EVP_R_INITIALIZATION_ERROR);
        return 0;
#else
        EVP_CIPHER *provciph =
            EVP_CIPHER_fetch(NULL, OBJ_nid2sn(cipher->nid), "");

        if (provciph == NULL) {
            EVPerr(EVP_F_EVP_CIPHERINIT_EX, EVP_R_INITIALIZATION_ERROR);
            return 0;
        }
        cipher = provciph;
        EVP_CIPHER_free(ctx->fetched_cipher);
        ctx->fetched_cipher = provciph;
#endif
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
#if !defined(OPENSSL_NO_ENGINE) && !defined(FIPS_MODE)
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
#if !defined(OPENSSL_NO_ENGINE) && !defined(FIPS_MODE)
 skip_to_init:
#endif
    if (ctx->cipher == NULL)
        return 0;

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