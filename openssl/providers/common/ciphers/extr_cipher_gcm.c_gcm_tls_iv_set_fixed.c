#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t ivlen; int iv_gen; void* iv_state; scalar_t__ iv; int /*<<< orphan*/  libctx; scalar_t__ enc; } ;
typedef  TYPE_1__ PROV_GCM_CTX ;

/* Variables and functions */
 int EVP_GCM_TLS_EXPLICIT_IV_LEN ; 
 size_t EVP_GCM_TLS_FIXED_IV_LEN ; 
 void* IV_STATE_BUFFERED ; 
 int /*<<< orphan*/  memcpy (scalar_t__,unsigned char*,size_t) ; 
 scalar_t__ rand_bytes_ex (int /*<<< orphan*/ ,scalar_t__,size_t) ; 

__attribute__((used)) static int gcm_tls_iv_set_fixed(PROV_GCM_CTX *ctx, unsigned char *iv,
                                size_t len)
{
    /* Special case: -1 length restores whole IV */
    if (len == (size_t)-1) {
        memcpy(ctx->iv, iv, ctx->ivlen);
        ctx->iv_gen = 1;
        ctx->iv_state = IV_STATE_BUFFERED;
        return 1;
    }
    /* Fixed field must be at least 4 bytes and invocation field at least 8 */
    if ((len < EVP_GCM_TLS_FIXED_IV_LEN)
        || (ctx->ivlen - (int)len) < EVP_GCM_TLS_EXPLICIT_IV_LEN)
            return 0;
    if (len > 0)
        memcpy(ctx->iv, iv, len);
    if (ctx->enc
        && rand_bytes_ex(ctx->libctx, ctx->iv + len, ctx->ivlen - len) <= 0)
            return 0;
    ctx->iv_gen = 1;
    ctx->iv_state = IV_STATE_BUFFERED;
    return 1;
}