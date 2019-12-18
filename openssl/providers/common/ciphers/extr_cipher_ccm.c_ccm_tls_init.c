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
struct TYPE_3__ {int* buf; size_t tls_aad_len; size_t m; int /*<<< orphan*/  enc; } ;
typedef  TYPE_1__ PROV_CCM_CTX ;

/* Variables and functions */
 size_t EVP_AEAD_TLS1_AAD_LEN ; 
 size_t EVP_CCM_TLS_EXPLICIT_IV_LEN ; 
 int /*<<< orphan*/  memcpy (int*,unsigned char*,size_t) ; 

__attribute__((used)) static int ccm_tls_init(PROV_CCM_CTX *ctx, unsigned char *aad, size_t alen)
{
    size_t len;

    if (alen != EVP_AEAD_TLS1_AAD_LEN)
        return 0;

    /* Save the aad for later use. */
    memcpy(ctx->buf, aad, alen);
    ctx->tls_aad_len = alen;

    len = ctx->buf[alen - 2] << 8 | ctx->buf[alen - 1];
    if (len < EVP_CCM_TLS_EXPLICIT_IV_LEN)
        return 0;

    /* Correct length for explicit iv. */
    len -= EVP_CCM_TLS_EXPLICIT_IV_LEN;

    if (!ctx->enc) {
        if (len < ctx->m)
            return 0;
        /* Correct length for tag. */
        len -= ctx->m;
    }
    ctx->buf[alen - 2] = (unsigned char)(len >> 8);
    ctx->buf[alen - 1] = (unsigned char)(len & 0xff);

    /* Extra padding: tag appended to record. */
    return ctx->m;
}