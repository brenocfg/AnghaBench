#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {void** counter; } ;
struct TYPE_4__ {TYPE_1__ chacha; void** nonce; } ;
typedef  int /*<<< orphan*/  PROV_CIPHER_CTX ;
typedef  TYPE_2__ PROV_CHACHA20_POLY1305_CTX ;

/* Variables and functions */
 size_t CHACHA20_POLY1305_IVLEN ; 
 void* CHACHA_U8TOU32 (unsigned char*) ; 

__attribute__((used)) static int chacha_poly1305_tls_iv_set_fixed(PROV_CIPHER_CTX *bctx,
                                            unsigned char *fixed, size_t flen)
{
    PROV_CHACHA20_POLY1305_CTX *ctx = (PROV_CHACHA20_POLY1305_CTX *)bctx;

    if (flen != CHACHA20_POLY1305_IVLEN)
        return 0;
    ctx->nonce[0] = ctx->chacha.counter[1] = CHACHA_U8TOU32(fixed);
    ctx->nonce[1] = ctx->chacha.counter[2] = CHACHA_U8TOU32(fixed + 4);
    ctx->nonce[2] = ctx->chacha.counter[3] = CHACHA_U8TOU32(fixed + 8);
    return 1;
}