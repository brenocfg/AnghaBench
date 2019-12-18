#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned char* aad_buf; size_t aad_buf_len; unsigned char* data_buf; size_t data_buf_len; int /*<<< orphan*/  key_set; } ;
typedef  TYPE_1__ PROV_AES_OCB_CTX ;
typedef  int /*<<< orphan*/  OSSL_ocb_cipher_fn ;

/* Variables and functions */
 int /*<<< orphan*/  aes_generic_ocb_cipher ; 
 int aes_ocb_block_update_internal (TYPE_1__*,unsigned char*,size_t*,unsigned char*,size_t*,size_t,unsigned char const*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cipher_updateaad ; 
 int /*<<< orphan*/  update_iv (TYPE_1__*) ; 

__attribute__((used)) static int aes_ocb_block_update(void *vctx, unsigned char *out, size_t *outl,
                                size_t outsize, const unsigned char *in,
                                size_t inl)
{
    PROV_AES_OCB_CTX *ctx = (PROV_AES_OCB_CTX *)vctx;
    unsigned char *buf;
    size_t *buflen;
    OSSL_ocb_cipher_fn fn;

    if (!ctx->key_set || !update_iv(ctx))
        return 0;

    /* Are we dealing with AAD or normal data here? */
    if (out == NULL) {
        buf = ctx->aad_buf;
        buflen = &ctx->aad_buf_len;
        fn = cipher_updateaad;
    } else {
        buf = ctx->data_buf;
        buflen = &ctx->data_buf_len;
        fn = aes_generic_ocb_cipher;
    }
    return aes_ocb_block_update_internal(ctx, buf, buflen, out, outl, outsize,
                                         in, inl, fn);
}