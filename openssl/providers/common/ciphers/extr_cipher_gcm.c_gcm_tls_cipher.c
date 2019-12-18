#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ tls_enc_records; scalar_t__ iv_gen; unsigned char* iv; size_t ivlen; int /*<<< orphan*/  tls_aad_len; int /*<<< orphan*/  iv_state; scalar_t__ enc; int /*<<< orphan*/  buf; TYPE_1__* hw; int /*<<< orphan*/  key_set; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* oneshot ) (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char const*,size_t,unsigned char*,unsigned char*,size_t) ;int /*<<< orphan*/  (* setiv ) (TYPE_2__*,unsigned char*,size_t) ;} ;
typedef  TYPE_2__ PROV_GCM_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_LIB_PROV ; 
 int /*<<< orphan*/  ERR_raise (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t EVP_GCM_TLS_EXPLICIT_IV_LEN ; 
 size_t EVP_GCM_TLS_TAG_LEN ; 
 int /*<<< orphan*/  EVP_R_TOO_MANY_RECORDS ; 
 int /*<<< orphan*/  IV_STATE_COPIED ; 
 int /*<<< orphan*/  IV_STATE_FINISHED ; 
 int /*<<< orphan*/  OPENSSL_cleanse (unsigned char*,size_t) ; 
 int /*<<< orphan*/  UNINITIALISED_SIZET ; 
 int /*<<< orphan*/  ctr64_inc (unsigned char*) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,size_t) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,unsigned char*,size_t) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*,unsigned char*,size_t) ; 
 int /*<<< orphan*/  stub3 (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char const*,size_t,unsigned char*,unsigned char*,size_t) ; 

__attribute__((used)) static int gcm_tls_cipher(PROV_GCM_CTX *ctx, unsigned char *out, size_t *padlen,
                          const unsigned char *in, size_t len)
{
    int rv = 0;
    size_t arg = EVP_GCM_TLS_EXPLICIT_IV_LEN;
    size_t plen = 0;
    unsigned char *tag = NULL;

    if (!ctx->key_set)
        goto err;

    /* Encrypt/decrypt must be performed in place */
    if (out != in || len < (EVP_GCM_TLS_EXPLICIT_IV_LEN + EVP_GCM_TLS_TAG_LEN))
        goto err;

    /*
     * Check for too many keys as per FIPS 140-2 IG A.5 "Key/IV Pair Uniqueness
     * Requirements from SP 800-38D".  The requirements is for one party to the
     * communication to fail after 2^64 - 1 keys.  We do this on the encrypting
     * side only.
     */
    if (ctx->enc && ++ctx->tls_enc_records == 0) {
        ERR_raise(ERR_LIB_PROV, EVP_R_TOO_MANY_RECORDS);
        goto err;
    }

    if (ctx->iv_gen == 0)
        goto err;
    /*
     * Set IV from start of buffer or generate IV and write to start of
     * buffer.
     */
    if (ctx->enc) {
        if (!ctx->hw->setiv(ctx, ctx->iv, ctx->ivlen))
            goto err;
        if (arg > ctx->ivlen)
            arg = ctx->ivlen;
        memcpy(out, ctx->iv + ctx->ivlen - arg, arg);
        /*
         * Invocation field will be at least 8 bytes in size and so no need
         * to check wrap around or increment more than last 8 bytes.
         */
        ctr64_inc(ctx->iv + ctx->ivlen - 8);
    } else {
        memcpy(ctx->iv + ctx->ivlen - arg, out, arg);
        if (!ctx->hw->setiv(ctx, ctx->iv, ctx->ivlen))
            goto err;
    }
    ctx->iv_state = IV_STATE_COPIED;

    /* Fix buffer and length to point to payload */
    in += EVP_GCM_TLS_EXPLICIT_IV_LEN;
    out += EVP_GCM_TLS_EXPLICIT_IV_LEN;
    len -= EVP_GCM_TLS_EXPLICIT_IV_LEN + EVP_GCM_TLS_TAG_LEN;

    tag = ctx->enc ? out + len : (unsigned char *)in + len;
    if (!ctx->hw->oneshot(ctx, ctx->buf, ctx->tls_aad_len, in, len, out, tag,
                          EVP_GCM_TLS_TAG_LEN)) {
        if (!ctx->enc)
            OPENSSL_cleanse(out, len);
        goto err;
    }
    if (ctx->enc)
        plen =  len + EVP_GCM_TLS_EXPLICIT_IV_LEN + EVP_GCM_TLS_TAG_LEN;
    else
        plen = len;

    rv = 1;
err:
    ctx->iv_state = IV_STATE_FINISHED;
    ctx->tls_aad_len = UNINITIALISED_SIZET;
    *padlen = plen;
    return rv;
}