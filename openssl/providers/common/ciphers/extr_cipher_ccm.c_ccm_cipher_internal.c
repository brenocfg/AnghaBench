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
struct TYPE_10__ {scalar_t__ tls_aad_len; int tag_set; scalar_t__ len_set; scalar_t__ iv_set; int /*<<< orphan*/  m; int /*<<< orphan*/  buf; scalar_t__ enc; int /*<<< orphan*/  key_set; TYPE_1__* hw; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* auth_decrypt ) (TYPE_2__*,unsigned char const*,unsigned char*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* auth_encrypt ) (TYPE_2__*,unsigned char const*,unsigned char*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* setaad ) (TYPE_2__*,unsigned char const*,size_t) ;} ;
typedef  TYPE_1__ PROV_CCM_HW ;
typedef  TYPE_2__ PROV_CCM_CTX ;

/* Variables and functions */
 scalar_t__ UNINITIALISED_SIZET ; 
 int /*<<< orphan*/  ccm_set_iv (TYPE_2__*,size_t) ; 
 int ccm_tls_cipher (TYPE_2__*,unsigned char*,size_t*,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*,unsigned char const*,unsigned char*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (TYPE_2__*,unsigned char const*,unsigned char*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ccm_cipher_internal(PROV_CCM_CTX *ctx, unsigned char *out,
                               size_t *padlen, const unsigned char *in,
                               size_t len)
{
    int rv = 0;
    size_t olen = 0;
    const PROV_CCM_HW *hw = ctx->hw;

    /* If no key set, return error */
    if (!ctx->key_set)
        return 0;

    if (ctx->tls_aad_len != UNINITIALISED_SIZET)
        return ccm_tls_cipher(ctx, out, padlen, in, len);

    /* EVP_*Final() doesn't return any data */
    if (in == NULL && out != NULL)
        goto finish;

    if (!ctx->iv_set)
        goto err;

    if (out == NULL) {
        if (in == NULL) {
            if (!ccm_set_iv(ctx, len))
                goto err;
        } else {
            /* If we have AAD, we need a message length */
            if (!ctx->len_set && len)
                goto err;
            if (!hw->setaad(ctx, in, len))
                goto err;
        }
    } else {
        /* If not set length yet do it */
        if (!ctx->len_set && !ccm_set_iv(ctx, len))
            goto err;

        if (ctx->enc) {
            if (!hw->auth_encrypt(ctx, in, out, len, NULL, 0))
                goto err;
            ctx->tag_set = 1;
        } else {
            /* The tag must be set before actually decrypting data */
            if (!ctx->tag_set)
                goto err;

            if (!hw->auth_decrypt(ctx, in, out, len, ctx->buf, ctx->m))
                goto err;
            /* Finished - reset flags so calling this method again will fail */
            ctx->iv_set = 0;
            ctx->tag_set = 0;
            ctx->len_set = 0;
        }
    }
    olen = len;
finish:
    rv = 1;
err:
    *padlen = olen;
    return rv;
}