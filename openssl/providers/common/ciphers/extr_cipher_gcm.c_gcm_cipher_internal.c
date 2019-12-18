#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ tls_aad_len; scalar_t__ iv_state; scalar_t__ taglen; int /*<<< orphan*/  buf; int /*<<< orphan*/  enc; int /*<<< orphan*/  ivlen; int /*<<< orphan*/  iv; int /*<<< orphan*/  key_set; TYPE_1__* hw; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* cipherfinal ) (TYPE_2__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* cipherupdate ) (TYPE_2__*,unsigned char const*,size_t,unsigned char*) ;int /*<<< orphan*/  (* aadupdate ) (TYPE_2__*,unsigned char const*,size_t) ;int /*<<< orphan*/  (* setiv ) (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ PROV_GCM_HW ;
typedef  TYPE_2__ PROV_GCM_CTX ;

/* Variables and functions */
 scalar_t__ IV_STATE_BUFFERED ; 
 scalar_t__ IV_STATE_COPIED ; 
 scalar_t__ IV_STATE_FINISHED ; 
 scalar_t__ IV_STATE_UNINITIALISED ; 
 scalar_t__ UNINITIALISED_SIZET ; 
 int /*<<< orphan*/  gcm_iv_generate (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int gcm_tls_cipher (TYPE_2__*,unsigned char*,size_t*,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  stub3 (TYPE_2__*,unsigned char const*,size_t,unsigned char*) ; 
 int /*<<< orphan*/  stub4 (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gcm_cipher_internal(PROV_GCM_CTX *ctx, unsigned char *out,
                               size_t *padlen, const unsigned char *in,
                               size_t len)
{
    size_t olen = 0;
    int rv = 0;
    const PROV_GCM_HW *hw = ctx->hw;

    if (ctx->tls_aad_len != UNINITIALISED_SIZET)
        return gcm_tls_cipher(ctx, out, padlen, in, len);

    if (!ctx->key_set || ctx->iv_state == IV_STATE_FINISHED)
        goto err;

    /*
     * FIPS requires generation of AES-GCM IV's inside the FIPS module.
     * The IV can still be set externally (the security policy will state that
     * this is not FIPS compliant). There are some applications
     * where setting the IV externally is the only option available.
     */
    if (ctx->iv_state == IV_STATE_UNINITIALISED) {
        if (!ctx->enc || !gcm_iv_generate(ctx, 0))
            goto err;
    }

    if (ctx->iv_state == IV_STATE_BUFFERED) {
        if (!hw->setiv(ctx, ctx->iv, ctx->ivlen))
            goto err;
        ctx->iv_state = IV_STATE_COPIED;
    }

    if (in != NULL) {
        /*  The input is AAD if out is NULL */
        if (out == NULL) {
            if (!hw->aadupdate(ctx, in, len))
                goto err;
        } else {
            /* The input is ciphertext OR plaintext */
            if (!hw->cipherupdate(ctx, in, len, out))
                goto err;
        }
    } else {
        /* The tag must be set before actually decrypting data */
        if (!ctx->enc && ctx->taglen == UNINITIALISED_SIZET)
            goto err;
        if (!hw->cipherfinal(ctx, ctx->buf))
            goto err;
        ctx->iv_state = IV_STATE_FINISHED; /* Don't reuse the IV */
        goto finish;
    }
    olen = len;
finish:
    rv = 1;
err:
    *padlen = olen;
    return rv;
}